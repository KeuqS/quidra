#pragma once

// The support block of a module with finite checks: the declarations of
// quidra_runtime_real_fail, which the cold blocks of the checks of real
// arithmetic call (CheckEmitter), and of quidra_runtime_extern_nonfinite,
// which the check of an extern function's real result calls (CallEmitter).
// Only such a module carries it, so the LLVM text of a program without
// fixed-width real arithmetic or real extern results does not change.

#include "llvm_text/llvm_callee.hpp"

#include <span>
#include <string_view>

namespace quidra::llvm_backend {

// The callees the cold blocks call, as they appear in a module's bodies.
inline constexpr std::string_view finite_check_callee = "@quidra_runtime_real_fail(";
inline constexpr std::string_view extern_check_callee = "@quidra_runtime_extern_nonfinite(";
inline constexpr std::string_view package_check_callee = "@quidra_tensor_validate_package(";

// The declarations of the support block.
std::span<const llvm_text::LlvmCallee* const> finite_check_support_declarations();

// The support block's text.
std::string_view finite_check_support_text();

} // namespace quidra::llvm_backend
