#pragma once

// Potential user tail calls and the subset whose logical paths cannot be
// recovered uniquely from the call graph. This analysis never changes IR:
// the native backend uses it to describe edges in its call-site table and
// to record only ambiguous, indirect and self-tail sites.

#include "quidra/ir/module.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace quidra::ir::analysis {

struct TailCallSite {
    std::string owner;
    std::string callee; // empty for an indirect call
    bool recorded{};
    bool self{};
    // The first edge after the call and its pure return suffix. A backend
    // may duplicate this suffix when a normal path shares its return.
    const Instruction* continuation_edge{};
    std::vector<const Block*> continuation_blocks;

};

struct TailCalls {
    std::unordered_map<const Instruction*, TailCallSite> sites;
    std::unordered_set<const Instruction*> tail_returns;
    std::unordered_set<std::string> self_sites;
};

TailCalls tail_calls(const Module& module,
                     const std::unordered_set<std::string>& guarded,
                     const std::unordered_set<std::string>& address_taken,
                     const std::unordered_set<std::string>& user_sources);

} // namespace quidra::ir::analysis
