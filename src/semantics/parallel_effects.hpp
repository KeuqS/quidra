#pragma once
#include "semantics/effect_summary.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>
namespace quidra::semantics {
struct ParallelSharedAccess {
    StoragePath path;
    bool writes{};
    // Zero is unknown/existing; each proven fresh region has one stable id.
    // Copies of that region retain its id.
    std::uint64_t fresh_region{};
};
struct ParallelNodeEffects {
    PathSet reads,writes;
    std::vector<ParallelSharedAccess> shared;
    std::vector<ResourceAccess> resources;
    bool mutates_ambient{};
    bool fallible{};
    bool requires_managed_storage{};
    bool unproven_call{};
    // Unknown targets of stored references may overlap marked direct
    // storage of compatible types. These are conflict facts only: they
    // must never manufacture a producer/consumer dependency.
    std::map<std::string,Type> reference_shared_reads,reference_shared_writes;
    std::map<StoragePath,Type> reference_target_reads,reference_target_writes;
    // Proven holder provenance preserves precise targets and fresh-region
    // independence without promoting aliases into RAW producer edges.
    std::map<StoragePath,Type> reference_resolved_reads,reference_resolved_writes;
    // Taking an address needs storage in the outlined frame, but does not
    // read its value or create a producer/consumer dependency.
    PathSet address_roots;
};
struct ParallelCapture {
    std::string name;
    bool writable{};
    const Stmt* binding{};
    bool source_reference{};
    bool shape_variable{};
};
struct ParallelBlockPlan {
    std::vector<ParallelNodeEffects> nodes;
    std::vector<std::vector<std::uint32_t>> predecessors;
    std::vector<std::vector<ParallelCapture>> captures;
    std::vector<bool> worker_safe;
    std::vector<bool> fallible;
};
enum class ParallelConflictKind : std::uint8_t { WriteWrite,ReadWrite,Resource,Ambient };
struct ParallelConflict {
    std::uint32_t first{},second{};
    std::string storage;
    ParallelConflictKind kind{ParallelConflictKind::WriteWrite};
    ResourceKind resource{};
    bool handle{};
};
struct ParallelDependencies {
    std::vector<std::vector<std::uint32_t>> predecessors;
    std::optional<ParallelConflict> conflict;
};
ParallelDependencies parallel_dependencies(const std::vector<ParallelNodeEffects>& nodes,
    const std::vector<std::string>& parameter_names={},const CheckedProgram* checked=nullptr);
} // namespace quidra::semantics
