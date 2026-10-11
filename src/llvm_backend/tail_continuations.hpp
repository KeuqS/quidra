#pragma once

// A return shared with a normal path must retain self-run cleanup. Duplicate
// only a tail call's pure return suffix so its tail path skips that cleanup.
// This adds no entry flag or store and leaves the typed IR untouched.
#include "ir/analysis/tail_calls.hpp"
#include "llvm_backend/temporary_names.hpp"

#include <unordered_map>
#include <vector>

namespace quidra::llvm_backend {
struct TailContinuations {
    std::unordered_map<const ir::Instruction*, ir::Instruction> edges;
    std::vector<ir::Block> blocks;
};
TailContinuations tail_continuations(const ir::Function& function,
                                    const ir::analysis::TailCalls& calls,
                                    TemporaryNames& names);
} // namespace quidra::llvm_backend
