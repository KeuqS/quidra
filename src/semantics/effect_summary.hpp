#pragma once

// Effect summaries: what every function and method of a checked program may
// read and write of its caller's storage, which shared regions and hidden
// runtime state it may change, which external resources it uses, whether it
// observes the address of a const parameter, and where its result comes
// from. One analysis for every consumer (argument isolation of const
// values, mutation markers, parallel conflicts, the loop predicates), so
// that they never disagree about what a call may touch
// (effect_summary.cpp).
//
// Owns: EffectSummary, EffectSummaries and summarize_effects, which the
// checker runs at the end of a check; the result is CheckedProgram::effects.

#include "quidra/checker.hpp"
#include "semantics/storage_path.hpp"
#include <cstddef>
#include <cstdint>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace quidra::semantics {

// Shared commutes with every other shared use of the kind; Exclusive must be
// ordered against every other use, except that accesses through distinct
// handles are never ordered.
enum class ResourceUse : std::uint8_t { Shared, Exclusive };

// Direct for path-based file operations and every other operation;
// Handle for an operation through a file.Handle value, whose storage path
// `handle` names. A handle that does not escape a callee is summarized as a
// fresh handle: a Local root no caller path overlaps.
enum class ResourceOrigin : std::uint8_t { Direct, Handle };

struct ResourceAccess {
    ResourceKind kind{ResourceKind::Stdout};
    ResourceUse use{ResourceUse::Shared};
    ResourceOrigin origin{ResourceOrigin::Direct};
    StoragePath handle;

    friend bool operator==(const ResourceAccess& left, const ResourceAccess& right);
    friend bool operator<(const ResourceAccess& left, const ResourceAccess& right);
};

// Adds `access` to `accesses`, keeping one access per kind and origin: the
// stronger use wins.
void record_resource(std::set<ResourceAccess>& accesses, ResourceAccess access);

// Where a function's result comes from: a value it created, a copy of (part
// of) parameter `parameter`, or anything else that exists already.
struct ResultProvenance {
    enum class Kind : std::uint8_t { Fresh, Parameter, Existing };
    Kind kind{Kind::Fresh};
    std::size_t parameter{};

    friend bool operator==(const ResultProvenance& left, const ResultProvenance& right);
};

// The first hidden mutation of a function, for diagnostics: where it happens
// and what it changes ("field 'value'", "shared state of c", "runtime state
// through 'f'").
struct EffectCause {
    SourceSpan span{};
    std::string description;

    friend bool operator==(const EffectCause& left, const EffectCause& right);
};

struct ReferenceLink {
    StoragePath holder, target;
    bool must{};
    SourceSpan site{};
    friend bool operator==(const ReferenceLink& a, const ReferenceLink& b) {
        return a.holder == b.holder && a.target == b.target && a.must == b.must &&
               a.site.start.offset == b.site.start.offset;
    }
};

struct EffectSummary {
    // Per parameter index, the paths the function may read and write through
    // that parameter's storage: the targets of its & parameters, and, for a
    // method, the receiver (index 0). By-value parameters are copies and
    // keep these sets empty.
    std::vector<PathSet> exposed_reads, exposed_writes;
    // A method that may write its receiver or the shared regions reachable
    // from it. A constructor's receiver is the value it creates, never
    // existing state.
    bool mutates_receiver{};
    // Per parameter, whether the shared regions reachable from it may
    // change: from a by-value parameter's value, from an & parameter's
    // target, from a method's receiver (index 0, which also sets
    // mutates_receiver).
    std::vector<bool> mutates_shared_of_parameter;
    // Runtime state that no parameter exposes: through a `.` extern, shared
    // state of unknown origin, or a callee that does.
    bool mutates_ambient{};
    // The shared regions the function may read, for read/write conflicts.
    PathSet shared_reads;
    // External I/O: never a hidden mutation, always a conflict reason.
    std::set<ResourceAccess> resources;
    // Per parameter, whether the function observes the address of a const
    // parameter or of a part of one (`&b`, `&b[0]`, `&b.f`).
    std::vector<bool> const_parameter_address_observed;
    ResultProvenance result;
    std::optional<EffectCause> first_hidden_mutation;
    std::vector<bool> reference_target_escapes;
    std::set<std::string> escaping_locals;
    std::vector<ReferenceLink> reference_links;
    std::vector<bool> reference_root_parameters;
    PathSet pinned_complete_targets;
    std::map<std::string,Type> reference_shared_reads,reference_shared_writes;
    std::map<StoragePath,Type> reference_shared_read_origins,reference_shared_write_origins;

    friend bool operator==(const EffectSummary& left, const EffectSummary& right);
};

struct ReferenceCallWrites {
    std::map<std::string,Type> shared;
    std::map<StoragePath,Type> resolved;
};

// Every function, method and constructor of a program by its internal name
// (`f`, `$method.C.m`, `$construct.C.0`), externs included. Moved, never
// copied.
struct ParallelBlockPlan;
using ParallelBlockPlans=std::map<const Stmt*,std::shared_ptr<const ParallelBlockPlan>>;

class EffectSummaries {
public:
    EffectSummaries() = default;
    EffectSummaries(const EffectSummaries&) = delete;
    EffectSummaries& operator=(const EffectSummaries&) = delete;
    EffectSummaries(EffectSummaries&&) = default;
    EffectSummaries& operator=(EffectSummaries&&) = default;

    // Null for a name the program does not define.
    const EffectSummary* find(const std::string& function) const;
    const std::map<std::string, EffectSummary>& all() const { return summaries_; }
    const ParallelBlockPlan* parallel_block(const Stmt& statement) const;
    const ParallelBlockPlans& parallel_blocks() const {return parallel_blocks_;}
    void set_parallel_blocks(ParallelBlockPlans plans) {parallel_blocks_=std::move(plans);}
    void set(std::string function, EffectSummary summary);

    // The by-value call arguments (their expressions) that name storage the
    // call may write while it runs (semantics/argument_isolation.hpp).
    bool isolated(const Expr& argument) const;
    void set_isolated(std::set<const Expr*> arguments);
    bool reference_target(const Expr& expression) const { return reference_targets_.contains(&expression); }
    void set_reference_targets(std::set<const Expr*> expressions) { reference_targets_=std::move(expressions); }
    const PathSet* reference_target_paths(const Expr& expression) const {
        const auto found=reference_target_paths_.find(&expression);return found==reference_target_paths_.end()?nullptr:&found->second;
    }
    const ReferenceCallWrites* reference_call(const Expr& expression) const {
        const auto found=reference_calls_.find(&expression);return found==reference_calls_.end()?nullptr:&found->second;
    }
    void set_reference_flow(std::map<const Expr*,PathSet> paths,std::map<const Expr*,ReferenceCallWrites> calls) {
        reference_target_paths_=std::move(paths);reference_calls_=std::move(calls);
    }

private:
    std::map<std::string, EffectSummary> summaries_;
    ParallelBlockPlans parallel_blocks_;
    // Looked up by node, never iterated.
    std::set<const Expr*> isolated_;
    std::set<const Expr*> reference_targets_;
    std::map<const Expr*,PathSet> reference_target_paths_;
    std::map<const Expr*,ReferenceCallWrites> reference_calls_;
};

// Whether values of `type` hold a shared region: a reference field or a file.Handle
// runtime state, directly or through fields, array elements and union cases.
// A Target copy owns an independent gradient destination.
// Mutating a copy of any other value is always local.
bool contains_shared_region(const CheckedProgram& checked, const Type& type);
const EffectSummary* reference_write_summary(const CheckedProgram& checked,const Expr& call);
bool reference_call_writes(const CheckedProgram& checked,const Expr& call,const Expr& target);
bool reference_target_compatible(const CheckedProgram&,const Type&,const Type&);

// Computes the summary of every function of `checked`, bottom-up over the
// strongly connected components of the call graph, iterated to a fixed point
// inside each component, and, from the summaries, the arguments every call
// of the program, top-level code included, must isolate.
EffectSummaries summarize_effects(const CheckedProgram& checked);

} // namespace quidra::semantics
