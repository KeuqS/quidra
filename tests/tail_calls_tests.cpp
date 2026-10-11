#include "ir/analysis/tail_calls.hpp"
#include "quidra/ir/module.hpp"
#include "llvm_backend/tail_continuations.hpp"

#include <cstdlib>
#include <iostream>

using namespace quidra;
using namespace quidra::ir;
using namespace quidra::ir::analysis;

namespace {
const Type scalar = Type::simple(TypeKind::Int64);

void expect(bool value, const char* message) {
    if (!value) { std::cerr << message << '\n'; std::exit(1); }
}

Function returning_call(const std::string& owner, const std::string& callee) {
    Function function;
    function.name = owner;
    function.source_file = "tail.qui";
    function.result = scalar;
    function.blocks.push_back({"entry", {Call{1, callee, {}, scalar}, Return{1, scalar}}});
    return function;
}

TailCalls analyze(const Module& module, const std::unordered_set<std::string>& guarded = {}) {
    return tail_calls(module, guarded, {}, {"tail.qui"});
}

void unique_paths_need_no_record() {
    Module module;
    module.functions.push_back(returning_call("outer", "middle"));
    module.functions.push_back(returning_call("middle", "inner"));
    auto terminal = returning_call("inner", "outside");
    module.functions.push_back(std::move(terminal));
    const auto result = analyze(module);
    expect(result.sites.size() == 2, "only calls of user functions are tail edges");
    for (const auto& [_, site] : result.sites)
        expect(!site.recorded, "a unique acyclic path has no normal-path record");
}

void distinct_sites_to_one_callee_are_recorded() {
    Module module;
    auto branch = returning_call("branch", "inner");
    branch.blocks.push_back({"other", {Call{2, "inner", {}, scalar}, Return{2, scalar}}});
    module.functions.push_back(std::move(branch));
    module.functions.push_back(returning_call("inner", "outside"));
    const auto result = analyze(module);
    expect(result.sites.size() == 2, "both branch sites remain in the graph");
    for (const auto& [_, site] : result.sites)
        expect(site.recorded, "two tail paths record which source site ran");
}

void self_runs_record_their_tail_exit() {
    Module module;
    auto self = returning_call("count", "count");
    self.blocks.push_back({"exit", {Call{2, "inner", {}, scalar}, Return{2, scalar}}});
    module.functions.push_back(std::move(self));
    module.functions.push_back(returning_call("inner", "outside"));
    const auto result = analyze(module);
    expect(result.self_sites.contains("count"), "self-tail functions need return cleanup");
    expect(result.sites.size() == 2, "self call and tail exit remain distinct");
    for (const auto& [_, site] : result.sites)
        expect(site.recorded, "a self run records its exit as well as its self call");
}

void work_after_a_call_prevents_a_tail_edge() {
    Module module;
    auto function = returning_call("outer", "inner");
    function.blocks[0].instructions.insert(function.blocks[0].instructions.begin() + 1,
        Call{2, "side_effect", {}, Type::simple(TypeKind::Void)});
    module.functions.push_back(std::move(function));
    module.functions.push_back(returning_call("inner", "outside"));
    expect(analyze(module).sites.empty(), "observable work after a call prevents a tail edge");
    module.functions[0] = returning_call("outer", "inner");
    expect(analyze(module, {"outer"}).sites.empty(), "a stack-leave guard prevents tail edges");
}

void checked_failure_does_not_prevent_a_tail_edge() {
    Module module;
    auto caller = returning_call("outer", "inner");
    caller.blocks[0].instructions[1] = Branch{1, "failure", "return"};
    caller.blocks.push_back({"failure", {FailError{1}}});
    caller.blocks.push_back({"return", {Return{1, scalar}}});
    module.functions.push_back(std::move(caller));
    module.functions.push_back(returning_call("inner", "outside"));
    const auto result = analyze(module);
    expect(result.sites.size() == 1, "a checked call's unreachable failure arm preserves its tail edge");
    module.functions[0].blocks[1].instructions = {Return{1, scalar}};
    expect(analyze(module).sites.empty(), "two returning branch arms are not a checked failure");
}

void a_shared_normal_return_keeps_its_cleanup() {
    Module module;
    auto self = returning_call("count", "count");
    self.blocks[0].instructions = {Call{1, "count", {}, scalar},
                                  StoreLocal{"result", 1, scalar}, Jump{"return"}};
    self.blocks.push_back({"normal", {StoreLocal{"result", 2, scalar}, Jump{"return"}}});
    self.blocks.push_back({"return", {LoadLocal{3, "result", scalar}, Return{3, scalar}}});
    module.functions.push_back(std::move(self));
    const auto result = analyze(module);
    const auto& function = module.functions[0];
    const auto* shared_return = &function.blocks[2].instructions[1];
    expect(!result.tail_returns.contains(shared_return), "a shared return still cleans a normal self run");
    quidra::llvm_backend::TemporaryNames names;
    const auto clones = quidra::llvm_backend::tail_continuations(function, result, names);
    expect(clones.blocks.size() == 1 && clones.edges.size() == 1,
           "only the tail call's pure return suffix is duplicated");
    const auto& tail_edge = std::get<Jump>(clones.edges.at(&function.blocks[0].instructions[2]));
    expect(tail_edge.target == clones.blocks[0].label, "the tail edge uses its own return suffix");
    expect(std::get<Jump>(function.blocks[1].instructions[1]).target == "return",
           "the normal path retains the original return");
    const auto& load = std::get<LoadLocal>(clones.blocks[0].instructions[0]);
    const auto& returned = std::get<Return>(clones.blocks[0].instructions[1]);
    expect(load.out > 3 && returned.value == load.out, "cloned SSA definitions and uses have fresh identifiers");
}
} // namespace

int main() {
    unique_paths_need_no_record();
    distinct_sites_to_one_callee_are_recorded();
    self_runs_record_their_tail_exit();
    work_after_a_call_prevents_a_tail_edge();
    checked_failure_does_not_prevent_a_tail_edge();
    a_shared_normal_return_keeps_its_cleanup();
}
