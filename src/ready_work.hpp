#pragma once

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <mutex>

namespace quidra::runtime_parallel::detail {

struct ReadyWork {
    void (*invoke)(void*) noexcept{};
    void* context{};
    std::uint64_t helper_bound{};
    ReadyWork* previous{};
    ReadyWork* next{};
    bool queued{};
};

// Queue component of the existing process-lifetime worker pool. The pool
// supplies detached helpers; a joining thread uses the same queue to help.
class ReadyQueue {
public:
    // Installed before publishing work; the existing Pool uses its own
    // worker wake condition while this queue wakes joining threads.
    void set_worker_notify(void (*notify)(void*) noexcept, void* context) noexcept {
        worker_notify_ = notify;
        worker_context_ = context;
    }

    bool has_ready(std::uint64_t helper_id) noexcept {
        std::lock_guard<std::mutex> guard(mutex_);
        return select(helper_id, false) != nullptr;
    }

    void push(ReadyWork& work) noexcept {
        {
            std::lock_guard<std::mutex> guard(mutex_);
            work.previous = last_;
            work.next = nullptr;
            work.queued = true;
            if (last_) last_->next = &work;
            else first_ = &work;
            last_ = &work;
        }
        wake_.notify_all();
        if (worker_notify_) worker_notify_(worker_context_);
    }

    bool cancel(ReadyWork& work) noexcept {
        std::lock_guard<std::mutex> guard(mutex_);
        if (!work.queued) return false;
        unlink(work);
        return true;
    }

    bool help(std::uint64_t helper_id, bool joining) noexcept {
        void (*invoke)(void*) noexcept = nullptr;
        void* context = nullptr;
        {
            std::lock_guard<std::mutex> guard(mutex_);
            auto* work = select(helper_id, joining);
            if (!work) return false;
            invoke = work->invoke;
            context = work->context;
            unlink(*work);
        }
        // The callback may publish completion and invalidate its work entry.
        // No access to the entry is permitted after calling the copied pair.
        invoke(context);
        return true;
    }

    void join(const std::atomic<bool>& done, std::uint64_t helper_id) noexcept {
        while (!done.load(std::memory_order_acquire)) {
            if (help(helper_id, true)) continue;
            std::unique_lock<std::mutex> guard(mutex_);
            wake_.wait(guard, [&] {
                return done.load(std::memory_order_acquire) || last_;
            });
        }
    }

    void wait_for_progress(const std::atomic<bool>& done,
                           const std::atomic<bool>& local_ready) noexcept {
        std::unique_lock<std::mutex> guard(mutex_);
        wake_.wait(guard, [&] {
            return done.load(std::memory_order_acquire) || last_ ||
                   local_ready.load(std::memory_order_acquire);
        });
    }

    void changed() noexcept {
        std::lock_guard<std::mutex> guard(mutex_);
        wake_.notify_all();
    }

    void complete(std::atomic<bool>& done) noexcept {
        std::lock_guard<std::mutex> guard(mutex_);
        done.store(true, std::memory_order_release);
        // The caller may destroy its state at this point. Only this queue's
        // process-lifetime state is touched after the release publication.
        wake_.notify_all();
    }

private:
    ReadyWork* select(std::uint64_t id, bool joining) const noexcept {
        if (joining) return last_;
        auto* work = first_;
        while (work && id >= work->helper_bound) work = work->next;
        return work;
    }

    void unlink(ReadyWork& work) noexcept {
        if (work.previous) work.previous->next = work.next;
        else first_ = work.next;
        if (work.next) work.next->previous = work.previous;
        else last_ = work.previous;
        work.queued = false;
        work.previous = nullptr;
        work.next = nullptr;
    }

    void (*worker_notify_)(void*) noexcept{};
    void* worker_context_{};
    std::mutex mutex_;
    std::condition_variable wake_;
    ReadyWork* first_{};
    ReadyWork* last_{};
};

} // namespace quidra::runtime_parallel::detail
