#include "llvm_backend/tail_continuations.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <variant>

namespace quidra::llvm_backend {

TailContinuations tail_continuations(const ir::Function& function,
                                    const ir::analysis::TailCalls& calls,
                                    TemporaryNames& names) {
    TailContinuations result;
    if (!calls.self_sites.contains(function.name)) return result;
    ir::ValueId next_value = 0;
    std::unordered_set<std::string> labels;
    for (const auto& block : function.blocks) {
        labels.insert(block.label);
        for (const auto& instruction : block.instructions)
            std::visit([&](const auto& node) {
                if constexpr (requires { node.out; }) next_value = std::max(next_value, node.out);
            }, instruction);
    }
    const auto fresh_value = [&] {
        if (next_value == std::numeric_limits<ir::ValueId>::max())
            throw std::overflow_error("tail return suffix exhausted IR value identifiers");
        return ++next_value;
    };
    // IR order makes fresh names deterministic, independent of hash order.
    for (const auto& block : function.blocks)
        for (const auto& instruction : block.instructions) {
            const auto found = calls.sites.find(&instruction);
            if (found == calls.sites.end()) continue;
            const auto& site = found->second;
            if (!site.continuation_edge || site.continuation_blocks.empty()) continue;
            std::unordered_map<std::string, std::string> cloned_labels;
            std::unordered_map<ir::ValueId, ir::ValueId> cloned_values;
            for (const auto* suffix : site.continuation_blocks) {
                auto label = names.label("quidra.tail.return");
                while (!labels.insert(label).second) label = names.label("quidra.tail.return");
                cloned_labels.emplace(suffix->label, std::move(label));
                for (const auto& step : suffix->instructions)
                    if (const auto* load = std::get_if<ir::LoadLocal>(&step))
                        cloned_values.emplace(load->out, fresh_value());
            }
            const auto value = [&](ir::ValueId old) {
                const auto it = cloned_values.find(old);
                return it == cloned_values.end() ? old : it->second;
            };
            const auto label = [&](const std::string& old) {
                const auto it = cloned_labels.find(old);
                return it == cloned_labels.end() ? old : it->second;
            };
            const auto remap = [&](ir::Instruction& step) {
                std::visit([&](auto& node) {
                    using T = std::decay_t<decltype(node)>;
                    if constexpr (std::is_same_v<T, ir::LoadLocal>) node.out = value(node.out);
                    else if constexpr (std::is_same_v<T, ir::StoreLocal> || std::is_same_v<T, ir::Return>)
                        node.value = value(node.value);
                    else if constexpr (std::is_same_v<T, ir::Jump>) node.target = label(node.target);
                    else if constexpr (std::is_same_v<T, ir::Branch>) {
                        node.condition = value(node.condition);
                        node.if_true = label(node.if_true);
                        node.if_false = label(node.if_false);
                    }
                }, step);
            };
            auto edge = *site.continuation_edge;
            remap(edge);
            result.edges.emplace(site.continuation_edge, std::move(edge));
            for (const auto* suffix : site.continuation_blocks) {
                auto clone = *suffix;
                clone.label = cloned_labels.at(suffix->label);
                for (auto& step : clone.instructions) remap(step);
                result.blocks.push_back(std::move(clone));
            }
        }
    return result;
}
} // namespace quidra::llvm_backend
