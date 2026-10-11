#include "ir/analysis/tail_calls.hpp"

#include <algorithm>
#include <functional>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace quidra::ir::analysis {
namespace {

// Return cleanup must emit no call. Borrowed parameters and borrowed
// locals do not own their values; references still require unpinning.
bool has_return_cleanup(const Function& function) {
    std::unordered_set<std::string> borrowed;
    for (const auto& p : function.parameters) {
        if (p.writable || p.borrowed) borrowed.insert(p.name);
        else if (requires_lifetime_management(p.type)) return true;
    }
    for (const auto& block : function.blocks)
        for (const auto& instruction : block.instructions)
            if (const auto* store = std::get_if<StoreLocal>(&instruction); store && store->borrowed)
                borrowed.insert(store->name);
    for (const auto& block : function.blocks)
        for (const auto& instruction : block.instructions) {
            if (std::holds_alternative<DeclareReference>(instruction)) return true;
            if (const auto* local = std::get_if<DeclareLocal>(&instruction);
                local && requires_lifetime_management(local->type) && !borrowed.contains(local->name))
                return true;
        }
    return false;
}

struct Continuation {
    const Function& function;
    std::unordered_map<std::string, const Block*> blocks;
    std::unordered_set<const Instruction*> visited;
    std::unordered_set<ValueId> aliases;
    std::unordered_set<std::string> locals;
    const Instruction* returned{};
    bool void_result{};
    const Block* returned_block{};
    const Instruction* first_edge{};
    std::vector<const Block*> suffix;

    bool fails(const Block& block, std::unordered_set<const Block*>& active) const {
        if (!active.insert(&block).second) return false;
        // The backend inserts unreachable in an empty block.
        if (block.instructions.empty()) return true;
        const auto& last = block.instructions.back();
        if (std::holds_alternative<Exit>(last) || std::holds_alternative<FailError>(last)) return true;
        if (const auto* call = std::get_if<Call>(&last))
            return call->result.kind == TypeKind::Never || call->no_normal_return;
        if (const auto* call = std::get_if<IndirectCall>(&last)) return call->result.kind == TypeKind::Never;
        const auto target_fails = [&](const std::string& name) {
            const auto next = blocks.find(name);
            auto path = active;
            return next != blocks.end() && fails(*next->second, path);
        };
        if (const auto* jump = std::get_if<Jump>(&last)) return target_fails(jump->target);
        if (const auto* branch = std::get_if<Branch>(&last))
            return target_fails(branch->if_true) && target_fails(branch->if_false);
        return false;
    }

    bool follow_edge(const std::string& target, const Instruction& edge) {
        const auto next = blocks.find(target);
        if (next == blocks.end()) return false;
        if (!first_edge) first_edge = &edge;
        suffix.push_back(next->second);
        return follow(*next->second, 0);
    }


    bool follow(const Block& block, std::size_t first) {
        for (std::size_t i = first; i < block.instructions.size(); ++i) {
            const auto& instruction = block.instructions[i];
            if (!visited.insert(&instruction).second) return false;
            if (const auto* result = std::get_if<Return>(&instruction)) {
                if (void_result ? result->type.kind != TypeKind::Void : !aliases.contains(result->value))
                    return false;
                returned = &instruction;
                returned_block = &block;
                return true;
            }
            if (std::holds_alternative<ReturnVoid>(instruction)) {
                if (!void_result) return false;
                returned = &instruction;
                returned_block = &block;
                return true;
            }
            if (const auto* jump = std::get_if<Jump>(&instruction)) {
                return follow_edge(jump->target, instruction);
            }
            if (const auto* branch = std::get_if<Branch>(&instruction)) {
                const auto yes = blocks.find(branch->if_true);
                const auto no = blocks.find(branch->if_false);
                if (yes == blocks.end() || no == blocks.end()) return false;
                std::unordered_set<const Block*> active;
                const bool yes_fails = fails(*yes->second, active);
                active.clear();
                const bool no_fails = fails(*no->second, active);
                // A checked result may return on exactly one arm; its other
                // arm ends in a failure and cannot resume the caller.
                if (yes_fails == no_fails) return false;
                return follow_edge(yes_fails ? branch->if_false : branch->if_true, instruction);
            }
            // Loads and stores of a direct scalar result may disappear into
            // SSA without work. Managed stores could release an old value.
            if (const auto* store = std::get_if<StoreLocal>(&instruction)) {
                if (requires_lifetime_management(store->type) || !aliases.contains(store->value))
                    return false;
                locals.insert(store->name);
                continue;
            }
            if (const auto* load = std::get_if<LoadLocal>(&instruction)) {
                if (!locals.contains(load->name) || requires_lifetime_management(load->type)) return false;
                aliases.insert(load->out);
                continue;
            }
            // A location starts a new statement and may restore its
            // provenance with a runtime call. Every other instruction can
            // either change the result or emit observable work.
            return false;
        }
        return false;
    }
};

} // namespace

TailCalls tail_calls(const Module& module,
                     const std::unordered_set<std::string>& guarded,
                     const std::unordered_set<std::string>& address_taken,
                     const std::unordered_set<std::string>& user_sources) {
    TailCalls result;
    std::unordered_map<std::string, const Function*> users;
    for (const auto& function : module.functions)
        if (!function.entrypoint && !function.external_symbol && user_sources.contains(function.source_file))
            users.emplace(function.name, &function);
    std::unordered_map<std::string, std::vector<const Instruction*>> edges;
    for (const auto& function : module.functions) {
        if (!users.contains(function.name) || guarded.contains(function.name) || has_return_cleanup(function))
            continue;
        for (const auto& block : function.blocks)
            for (std::size_t i = 0; i < block.instructions.size(); ++i) {
                const auto& instruction = block.instructions[i];
                const auto* direct = std::get_if<Call>(&instruction);
                const auto* indirect = std::get_if<IndirectCall>(&instruction);
                if (!direct && !indirect) continue;
                if (direct && (!users.contains(direct->callee) || direct->no_normal_return)) continue;
                const Type& type = direct ? direct->result : indirect->result;
                if (type.kind == TypeKind::Never || owns_managed(type) || (type.kind==TypeKind::Tuple && runtime_storage_bytes(type)>16)) continue;
                Continuation continuation{function, {}, {}, {}, {}, nullptr, type.kind == TypeKind::Void, nullptr, nullptr, {}};
                for (const auto& b : function.blocks) continuation.blocks.emplace(b.label, &b);
                if (type.kind != TypeKind::Void) continuation.aliases.insert(direct ? direct->out : indirect->out);
                if (!continuation.follow(block, i + 1)) continue;
                const bool self = direct && direct->callee == function.name;
                result.sites.emplace(&instruction, TailCallSite{function.name, direct ? direct->callee : "",
                    self || indirect || address_taken.contains(function.name), self,
                    continuation.first_edge, std::move(continuation.suffix)});
                // Only a return in this call's own block is exclusive to it.
                // Shared suffixes retain normal-return cleanup until the
                // backend duplicates the tail path's pure continuation.
                if (continuation.returned_block == &block) result.tail_returns.insert(continuation.returned);
                if (self) result.self_sites.insert(function.name);
                else if (direct) edges[function.name].push_back(&instruction);
            }
    }
    // Every exit of a self-tail function must follow its self run in the
    // log, so a later activation cannot mistake that run for its own.
    for (auto& [_, site] : result.sites)
        if (result.self_sites.contains(site.owner)) site.recorded = true;

    // Count distinct acyclic paths, saturating at two at each function.
    // When paths converge, mark the edges of both (and any later prefix).
    // The ordinary recursion guard removes mutual cycles; self edges were
    // recorded above and are absent from this graph.
    for (const auto& [origin, _] : users) {
        std::unordered_map<std::string, std::vector<const Instruction*>> first_path;
        std::unordered_map<std::string, unsigned> count;
        std::vector<const Instruction*> path;
        std::unordered_set<std::string> active;
        const auto mark = [&](const std::vector<const Instruction*>& p) {
            for (const auto* instruction : p) result.sites.at(instruction).recorded = true;
        };
        const auto visit = [&](auto&& recurse, const std::string& function) -> void {
            if (!active.insert(function).second) { mark(path); return; }
            if (function != origin) {
                const auto n = ++count[function];
                if (n == 1) first_path[function] = path;
                else { mark(first_path.at(function)); mark(path); }
                if (n > 2) { active.erase(function); return; }
            }
            const auto found = edges.find(function);
            if (found != edges.end())
                for (const auto* instruction : found->second) {
                    path.push_back(instruction);
                    recurse(recurse, result.sites.at(instruction).callee);
                    path.pop_back();
                }
            active.erase(function);
        };
        visit(visit, origin);
    }
    return result;
}

} // namespace quidra::ir::analysis
