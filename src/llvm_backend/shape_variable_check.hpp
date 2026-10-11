#pragma once

// ShapeVariableCheck: the run-time check of a tensor axis that a shape
// variable fixes (L17), `quidra_tensor_shape_variable_check`, which reports
// SHAPE_MISMATCH naming the variable and the binding.
//
// Owns: the support block that declares its entry point. Only a module that
// calls it carries the block, so the LLVM text of every other module is
// unchanged.

#include "llvm_text/llvm_callee.hpp"

#include <span>
#include <string_view>

namespace quidra::llvm_backend {

// The call target every check names; a module whose bodies contain it needs
// the support block.
inline constexpr std::string_view shape_variable_check_symbol =
    "@quidra_tensor_shape_variable_check";

// The support block: the declaration of the entry point.
std::string_view shape_variable_support_text();

// The runtime entry points the support block declares.
std::span<const llvm_text::LlvmCallee* const> shape_variable_support_declarations();

} // namespace quidra::llvm_backend
