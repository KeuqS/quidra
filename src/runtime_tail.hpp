#pragma once

// The exceptional tail-call sites of the current thread. Ordinary unique
// acyclic tail paths are recovered from the native call-site table alone.
// Every entry belongs to the physical frame's canonical frame address;
// depth distinguishes activations that LLVM's self-tail transform folds.

#include <cstddef>
#include <cstdint>
#include <span>

namespace quidra::runtime_tail {

struct Entry {
    std::uint32_t site;
    std::uint32_t depth;
    std::uintptr_t cfa;
};
static_assert(sizeof(Entry) == 16);

struct Snapshot {
    std::span<const Entry> entries;
    // The discarded outer part is never mistaken for a complete path.
    std::size_t lost_count{};
    std::uintptr_t lost_inner_cfa{};
    std::uintptr_t lost_outer_cfa{};
    std::uint32_t lost_first_site{};
    std::uint32_t lost_end_site{};

    bool lost_at(std::uintptr_t cfa) const noexcept {
        return lost_count && cfa >= lost_inner_cfa && cfa <= lost_outer_cfa;
    }
};

Snapshot snapshot() noexcept;

// Parallel nodes isolate their ephemeral records while preserving a suspended
// joining path. Storage is inline except for an already-grown ancestor log.
class NodeScope {
public:
    NodeScope() noexcept;
    ~NodeScope();
    NodeScope(const NodeScope&) = delete;
    NodeScope& operator=(const NodeScope&) = delete;
private:
    Entry saved_inline_[64]{};
    Entry* saved_entries_{};
    std::size_t saved_size_{}, saved_capacity_{};
    std::size_t saved_lost_count_{};
    std::uintptr_t saved_lost_inner_cfa_{}, saved_lost_outer_cfa_{};
    std::uint32_t saved_lost_first_site_{}, saved_lost_end_site_{};
};

} // namespace quidra::runtime_tail
