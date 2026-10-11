#pragma once
#include "runtime_counters.hpp"
#include "runtime_location.hpp"
#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <utility>
#include <tuple>
#include <vector>

namespace quidra::runtime {class OwnedNodeReport;}
namespace quidra::runtime_parallel::detail {
struct DeferredFailure {
    std::string message;
    counters::SourceSite site{};
    bool has_site{};
    std::shared_ptr<runtime::OwnedNodeReport> report;
    std::optional<int> exit_status;
    std::optional<runtime::ReportSite> raw_site{};
};
struct DeferredOutcome {
    std::tuple<int,std::uint64_t,bool> key{};
    std::uint64_t sequence{};
    DeferredFailure failure;
    std::unique_ptr<DeferredOutcome> next;
};
inline const DeferredFailure& empty_deferred_failure() noexcept {
    static const DeferredFailure empty;
    return empty;
}
class DeferredNode;
class DeferredTicket {
public:
    DeferredTicket() = default;
    DeferredTicket(const DeferredTicket&) = delete;
    DeferredTicket& operator=(const DeferredTicket&) = delete;
    DeferredTicket(DeferredTicket&& other) noexcept
        : owner_(std::move(other.owner_)), outcome_(std::move(other.outcome_)), completed_owner_(std::move(other.completed_owner_)) {}
    DeferredTicket& operator=(DeferredTicket&& other) noexcept {
        if(this != &other) {
            complete(); owner_=std::move(other.owner_);
            outcome_=std::move(other.outcome_);completed_owner_=std::move(other.completed_owner_);
        }
        return *this;
    }
    ~DeferredTicket() {complete();}
    void complete(std::string failure = {});
    void complete(DeferredFailure failure);
    const DeferredFailure& complete_view(DeferredFailure failure);
    explicit operator bool() const noexcept {return owner_ != nullptr;}
    std::shared_ptr<DeferredNode> owner() const noexcept {return owner_;}
private:
    friend class DeferredNode;
    DeferredTicket(std::shared_ptr<DeferredNode> owner,std::unique_ptr<DeferredOutcome> outcome)
        : owner_(std::move(owner)),outcome_(std::move(outcome)) {}
    std::shared_ptr<DeferredNode> owner_;
    std::unique_ptr<DeferredOutcome> outcome_;
    std::shared_ptr<DeferredNode> completed_owner_;
};
class DeferredNode : public std::enable_shared_from_this<DeferredNode> {
public:
    using CallbackRunner=DeferredFailure(*)(void(*)(void*),void*,const std::shared_ptr<void>&);
    std::shared_ptr<void> (*capture_callback_context)(){};
    CallbackRunner run_callback{};
    void (*raise_failure)(const DeferredFailure&){};
    void add_exceptions(int flags) noexcept {raised_flags_.fetch_or(flags,std::memory_order_relaxed);}
    int exceptions() const noexcept {return raised_flags_.load(std::memory_order_relaxed);}
    ~DeferredNode() {
        while(failures_) {auto first=std::move(failures_);failures_=std::move(first->next);}
    }
    DeferredTicket enqueue(int device, std::uint64_t serial,bool callback=false) {
        const std::tuple<int,std::uint64_t,bool> key{device,serial,callback};
        auto owner=shared_from_this();
        // Every ticket owns its future outcome before any asynchronous work.
        auto outcome=std::make_unique<DeferredOutcome>();outcome->key=key;
        std::lock_guard guard(mutex_);
        ++pending_[key]; ++count_;
        outcome->sequence=next_sequence_++;
        return DeferredTicket(std::move(owner),std::move(outcome));
    }
    void wait_covered(int device,std::uint64_t serial,bool skip_callbacks=false) {
        std::unique_lock guard(mutex_);
        wake_.wait(guard,[&] {
            for(const auto& [key,count] : pending_)
                if(std::get<0>(key)==device && std::get<1>(key)<=serial && count &&
                   !(skip_callbacks && std::get<2>(key))) return false;
            return true;
        });
    }
    bool idle() {
        std::lock_guard guard(mutex_);return count_==0;
    }
    std::optional<std::string> failure() {
        const auto outcome=first_failure();
        if (!outcome) return std::nullopt;
        return outcome->message;
    }
    std::optional<DeferredFailure> first_failure() {
        std::lock_guard guard(mutex_);
        if (!failures_) return std::nullopt;
        return failures_->failure;
    }
    std::optional<DeferredFailure> covered_failure(int device,std::uint64_t serial) {
        std::lock_guard guard(mutex_);
        for (auto* outcome=failures_.get();outcome;outcome=outcome->next.get())
            if (std::get<0>(outcome->key)==device && std::get<1>(outcome->key)<=serial)
                return outcome->failure;
        return std::nullopt;
    }
    // Failure cells are stable until this owner is destroyed. No completion
    // erases/recycles them, so callback views remain valid under their owner.
    const DeferredFailure* first_failure_view() {
        std::lock_guard guard(mutex_);return failures_?&failures_->failure:nullptr;
    }
    std::optional<int> next_pending_device(std::optional<int> after={}) {
        std::lock_guard guard(mutex_);
        for(const auto& [key,count]:pending_)
            if(count && (!after || std::get<0>(key)>*after))return std::get<0>(key);
        return {};
    }
    bool has_pending_device(int device) {
        std::lock_guard guard(mutex_);
        for(const auto& [key,count]:pending_)
            if(count && std::get<0>(key)==device)return true;
        return false;
    }
    std::vector<int> devices() {
        std::lock_guard guard(mutex_);
        std::vector<int> result;
        for (const auto& [key,count] : pending_) {
            (void)count;
            if (result.empty() || result.back()!=std::get<0>(key)) result.push_back(std::get<0>(key));
        }
        return result;
    }
    void wait_idle() {
        std::unique_lock guard(mutex_);
        wake_.wait(guard,[&] {return count_==0;});
    }
private:
    friend class DeferredTicket;
    const DeferredFailure& finish(std::unique_ptr<DeferredOutcome>& cell,DeferredFailure failure) {
        std::lock_guard guard(mutex_);
        const auto key=cell->key;
        const DeferredFailure* result=&empty_deferred_failure();
        if(!failure.message.empty() || failure.report || failure.exit_status) {
            cell->failure=std::move(failure);
            // Intrusive insertion uses the reservation itself and preserves
            // deterministic enqueue sequence without allocating a map node.
            auto* link=&failures_;
            while(*link && (*link)->sequence<cell->sequence)link=&(*link)->next;
            cell->next=std::move(*link);result=&cell->failure;*link=std::move(cell);
        }else cell.reset();
        const auto found=pending_.find(key);
        if(--found->second==0) pending_.erase(found);
        --count_;wake_.notify_all();return *result;
    }
    std::atomic<int> raised_flags_{};
    std::mutex mutex_;
    std::condition_variable wake_;
    std::map<std::tuple<int,std::uint64_t,bool>,std::size_t> pending_;
    std::size_t count_{};
    std::uint64_t next_sequence_{};
    std::unique_ptr<DeferredOutcome> failures_;
};
inline void DeferredTicket::complete(std::string failure) {
    complete(DeferredFailure{std::move(failure),{},false,{},{}});
}
inline void DeferredTicket::complete(DeferredFailure failure) {
    (void)complete_view(std::move(failure));
}
inline const DeferredFailure& DeferredTicket::complete_view(DeferredFailure failure) {
    if(!owner_)return empty_deferred_failure();
    const auto* result=&owner_->finish(outcome_,std::move(failure));
    completed_owner_=std::move(owner_);return *result;
}
inline thread_local std::shared_ptr<DeferredNode> current_deferred_node;
using DeferredFactory=std::shared_ptr<DeferredNode>(*)();
inline thread_local DeferredFactory current_deferred_factory{};
inline std::shared_ptr<DeferredNode> deferred_node() {
    if(!current_deferred_node && current_deferred_factory)
        current_deferred_node=current_deferred_factory();
    return current_deferred_node;
}
class DeferredFactoryScope {
public:
    explicit DeferredFactoryScope(DeferredFactory factory)
        : previous_node_(std::move(current_deferred_node)),previous_factory_(current_deferred_factory) {
        current_deferred_node.reset();current_deferred_factory=factory;
    }
    ~DeferredFactoryScope() {
        current_deferred_node=std::move(previous_node_);current_deferred_factory=previous_factory_;
    }
private:
    std::shared_ptr<DeferredNode> previous_node_;
    DeferredFactory previous_factory_{};
};

inline thread_local int current_callback_device=-1;
class DeferredNodeScope {
public:
    explicit DeferredNodeScope(std::shared_ptr<DeferredNode> node)
        : previous_(std::move(current_deferred_node)) {current_deferred_node=std::move(node);}
    ~DeferredNodeScope() {current_deferred_node=std::move(previous_);}
private:
    std::shared_ptr<DeferredNode> previous_;
};
struct DeferredCallback {
    void (*function)(void*){};
    void* context{};
    DeferredTicket ticket;
    std::shared_ptr<void> runtime_context;
    DeferredCallback(void(*body)(void*),void* frame,int device,std::uint64_t serial)
        : function(body),context(frame) {
        if(auto owner=deferred_node()) {
            if(owner->capture_callback_context) runtime_context=owner->capture_callback_context();
            ticket=owner->enqueue(device,serial,true);
        }
    }
    DeferredCallback(DeferredCallback&&)=default;
    DeferredCallback& operator=(DeferredCallback&&)=default;
    std::shared_ptr<DeferredNode> completed_owner;
    const DeferredFailure* completed_result{};
    const DeferredFailure& invoke(int device,void(*after_return)()=nullptr) {
        if(completed_result)return *completed_result;
        auto owner=ticket.owner();
        completed_owner=owner;
        DeferredNodeScope scope(owner);
        struct CallbackScope {
            int previous{current_callback_device};
            explicit CallbackScope(int device) {current_callback_device=device;}
            ~CallbackScope() {current_callback_device=previous;}
        } callback_scope(device);
        DeferredFailure outcome;
        if(owner && owner->run_callback) {
            struct Invocation {DeferredCallback* callback;void(*after_return)();} invocation{this,after_return};
            outcome=owner->run_callback([](void* raw) {
                const auto& invocation=*static_cast<Invocation*>(raw);
                invocation.callback->function(invocation.callback->context);
                if(invocation.after_return) invocation.after_return();
            },&invocation,runtime_context);
        } else {
            function(context);
            if(after_return) after_return();
        }
        completed_result=&ticket.complete_view(std::move(outcome));
        return *completed_result;
    }
};
} // namespace quidra::runtime_parallel::detail
