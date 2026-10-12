#pragma once

// Failure-only recovery of a logical tail path from the native graph and
// the current CFA's log. No allocation or guessed edge is permitted.
#include "quidra/abi/call_site_table.hpp"
#include "runtime_tail.hpp"

#include <cstdint>
#include <span>

namespace quidra::runtime_tail {
namespace table = abi::call_site_table;
struct Graph {
    const void* context{};
    std::uint32_t function_count{};
    std::uint32_t site_count{};
    table::SharedFunction (*function)(const void*, std::uint32_t){};
    table::SharedSite (*site)(const void*, std::uint32_t){};
    std::uint32_t (*owner)(const void*, std::uint32_t){};
};
struct CallEntry {
    std::uint32_t function{table::no_function};
    bool ambiguous{};
};
// A line-zero direct call can reach a checked body after LLVM removed its
// transparent wrapper. Resolve the physical target to the one source
// callee in `owner` that reaches it through declared forwarders. Repeated
// sites of that callee remain candidates; distinct callees, invalid
// forwarding relations and cycles are ambiguous. Another ordinary call
// that may reach the target also prevents choosing a source entry; this
// negative check never authorizes recovery of its unproved route. With no
// matching source call, retain the physical target so ordinary direct calls
// are unchanged.
CallEntry logical_call_entry(const Graph& graph, std::uint32_t owner,
                             std::uint32_t target) noexcept;
struct Hop {
    std::uint32_t site{};
    std::uint32_t callee{};
    std::uint32_t repeat{1};
    bool inlined{};
    std::uint32_t owner{table::no_function};
    bool merged{};
};
// A line-zero inline edge whose caller and callee are still proven by
// adjacent row levels. It does not authorize any other non-tail edge.
struct InlineEdge {std::uint32_t owner;std::uint32_t callee;};
struct Recovery {
    std::size_t count{};
    // Depth of the logical innermost function while suspended at its call.
    std::uint32_t depth{1};
    bool complete{};
};
// start_depth is the depth supplied by the physical caller (1 for a
// non-self call). inline_sites are in outside-to-inside order; kept_site is
// the suspended frame's actual call, whose record includes that kept call.
Recovery recover(const Graph& graph, Snapshot log, std::uintptr_t cfa,
                 std::uint32_t start, std::uint32_t target, std::uint32_t start_depth,
                 std::span<const std::uint32_t> inline_sites, std::uint32_t kept_site,
                 std::span<Hop> output, std::span<const InlineEdge> merged_inline = {}) noexcept;
} // namespace quidra::runtime_tail
