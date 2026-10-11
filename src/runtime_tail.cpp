#include "runtime_tail.hpp"
#include "quidra/abi/runtime_entry_points.hpp"

#include <algorithm>
#include <cstdlib>
#include <limits>

#if defined(QUIDRA_TAIL_TEST_ALLOCATOR)
// Test-target-only injection; native programs use malloc/realloc directly.
extern "C" void* quidra_tail_test_allocate(void* previous, std::size_t bytes);
#endif

namespace quidra::runtime_tail {
namespace {

struct Log {
    Entry inline_entries[64]{};
    Entry* entries{inline_entries};
    std::size_t size{};
    std::size_t capacity{64};
    std::size_t lost_count{};
    std::uintptr_t lost_inner_cfa{std::numeric_limits<std::uintptr_t>::max()};
    std::uintptr_t lost_outer_cfa{};
    std::uint32_t lost_first_site{std::numeric_limits<std::uint32_t>::max()};
    std::uint32_t lost_end_site{};

    void clear_loss() noexcept {
        lost_count = 0;
        lost_inner_cfa = std::numeric_limits<std::uintptr_t>::max();
        lost_outer_cfa = 0;
        lost_first_site = std::numeric_limits<std::uint32_t>::max();
        lost_end_site = 0;
    }

    ~Log() { if (entries != inline_entries) std::free(entries); }

    void erase(std::size_t index) noexcept {
        std::move(entries + index + 1, entries + size, entries + index);
        --size;
    }

    void reserve_one() noexcept {
        if (size < capacity) return;
        Entry* grown = nullptr;
        if (capacity <= std::numeric_limits<std::size_t>::max() / (2 * sizeof(Entry))) {
            const auto bytes = capacity * 2 * sizeof(Entry);
#if defined(QUIDRA_TAIL_TEST_ALLOCATOR)
            grown = static_cast<Entry*>(quidra_tail_test_allocate(entries == inline_entries ? nullptr : entries,
                                                                  bytes));
            if (grown && entries == inline_entries) std::copy_n(entries, size, grown);
#else
            if (entries == inline_entries) {
                grown = static_cast<Entry*>(std::malloc(bytes));
                if (grown) std::copy_n(entries, size, grown);
            } else {
                grown = static_cast<Entry*>(std::realloc(entries, bytes));
            }
#endif
        }
        if (grown) {
            entries = grown;
            capacity *= 2;
            return;
        }
        const auto removed = size / 2;
        for (std::size_t i = 0; i < removed; ++i) {
            lost_inner_cfa = std::min(lost_inner_cfa, entries[i].cfa);
            lost_outer_cfa = std::max(lost_outer_cfa, entries[i].cfa);
            lost_first_site = std::min(lost_first_site, entries[i].site);
            lost_end_site = std::max(lost_end_site, entries[i].site + 1);
        }
        if (lost_count <= std::numeric_limits<std::size_t>::max() - removed) lost_count += removed;
        else lost_count = std::numeric_limits<std::size_t>::max();
        std::move(entries + removed, entries + size, entries);
        size -= removed;
    }
};

thread_local Log tail_log;

} // namespace

NodeScope::NodeScope() noexcept
    : saved_entries_(tail_log.entries == tail_log.inline_entries ? saved_inline_ : tail_log.entries),
      saved_size_(tail_log.size), saved_capacity_(tail_log.capacity),
      saved_lost_count_(tail_log.lost_count), saved_lost_inner_cfa_(tail_log.lost_inner_cfa),
      saved_lost_outer_cfa_(tail_log.lost_outer_cfa), saved_lost_first_site_(tail_log.lost_first_site),
      saved_lost_end_site_(tail_log.lost_end_site) {
    if (saved_entries_ == saved_inline_) std::copy_n(tail_log.entries, saved_size_, saved_inline_);
    tail_log.entries = tail_log.inline_entries;
    tail_log.size = 0;
    tail_log.capacity = 64;
    tail_log.clear_loss();
}
NodeScope::~NodeScope() {
    if (tail_log.entries != tail_log.inline_entries) std::free(tail_log.entries);
    tail_log.entries = saved_entries_ == saved_inline_ ? tail_log.inline_entries : saved_entries_;
    if (saved_entries_ == saved_inline_) std::copy_n(saved_inline_, saved_size_, tail_log.entries);
    tail_log.size = saved_size_;
    tail_log.capacity = saved_capacity_;
    tail_log.lost_count = saved_lost_count_;
    tail_log.lost_inner_cfa = saved_lost_inner_cfa_;
    tail_log.lost_outer_cfa = saved_lost_outer_cfa_;
    tail_log.lost_first_site = saved_lost_first_site_;
    tail_log.lost_end_site = saved_lost_end_site_;
}

Snapshot snapshot() noexcept {
    return {{tail_log.entries, tail_log.size}, tail_log.lost_count,
            tail_log.lost_inner_cfa, tail_log.lost_outer_cfa,
            tail_log.lost_first_site, tail_log.lost_end_site};
}

} // namespace quidra::runtime_tail

extern "C" void quidra_tail_record(std::uint32_t site, std::uint32_t depth,
                                    void* frame, std::uint32_t self) {
    using namespace quidra::runtime_tail;
    const auto cfa = reinterpret_cast<std::uintptr_t>(frame);
    // Deeper activations above this physical frame have returned.
    while (tail_log.size && tail_log.entries[tail_log.size - 1].cfa < cfa) --tail_log.size;
    if (tail_log.lost_count && tail_log.lost_outer_cfa < cfa) tail_log.clear_loss();
    for (std::size_t i = tail_log.size; i > 0; --i) {
        const auto& previous = tail_log.entries[i - 1];
        if (previous.cfa != cfa) break;
        if (previous.site != site) continue;
        if (self && previous.depth + 1 == depth) tail_log.size = i - 1;
        else tail_log.erase(i - 1);
        break;
    }
    tail_log.reserve_one();
    tail_log.entries[tail_log.size++] = {site, depth, cfa};
}

extern "C" void quidra_tail_return(std::uint32_t first, std::uint32_t end,
                                    void* frame) {
    using namespace quidra::runtime_tail;
    const auto cfa = reinterpret_cast<std::uintptr_t>(frame);
    if (tail_log.lost_count && tail_log.lost_inner_cfa == cfa && tail_log.lost_outer_cfa == cfa &&
        tail_log.lost_first_site >= first && tail_log.lost_end_site <= end) tail_log.clear_loss();
    for (std::size_t i = tail_log.size; i > 0; --i) {
        const auto& entry = tail_log.entries[i - 1];
        if (entry.cfa > cfa) break;
        if (entry.cfa == cfa && entry.site >= first && entry.site < end) tail_log.erase(i - 1);
    }
}
