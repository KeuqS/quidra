#include "llvm_backend/shape_variable_check.hpp"

#include "llvm_backend/runtime_abi.hpp"
#include "llvm_text/llvm_callee.hpp"

#include <array>
#include <string>

namespace quidra::llvm_backend {

namespace {

constexpr std::array<const llvm_text::LlvmCallee*, 1> declarations{{
    &runtime_abi::shape_variable_support::check,
}};

std::string support_text() {
    std::string out = "\n";
    for (const auto* callee : declarations) llvm_text::append_declaration(out, *callee);
    return out;
}

} // namespace

std::string_view shape_variable_support_text() {
    static const std::string text = support_text();
    return text;
}

std::span<const llvm_text::LlvmCallee* const> shape_variable_support_declarations() {
    return declarations;
}

} // namespace quidra::llvm_backend
