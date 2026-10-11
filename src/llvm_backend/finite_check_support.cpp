#include "llvm_backend/finite_check_support.hpp"

#include "llvm_backend/runtime_abi.hpp"
#include "llvm_text/llvm_callee.hpp"

#include <array>
#include <string>

namespace quidra::llvm_backend {

namespace {

constexpr std::array<const llvm_text::LlvmCallee*, 3> declarations{{
    &runtime_abi::finite_support::real_fail,
    &runtime_abi::finite_support::extern_nonfinite,
    &runtime_abi::finite_support::validate_package,
}};

std::string support_text() {
    std::string out = "\n";
    for (const auto* callee : declarations) llvm_text::append_declaration(out, *callee);
    return out;
}

} // namespace

std::span<const llvm_text::LlvmCallee* const> finite_check_support_declarations() {
    return declarations;
}

std::string_view finite_check_support_text() {
    static const std::string text = support_text();
    return text;
}

} // namespace quidra::llvm_backend
