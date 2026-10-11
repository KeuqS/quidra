#pragma once

// SmallRationalArithmetic: the exact type `real` in generated code.
//
// Owns: the LLVM type of a `real` value, { i64, i64 } (abi::ExactRealValue:
// a small rational numerator/denominator, or the general form, a managed
// runtime node, when the denominator is 0), and the support block that a
// module using `real` carries: the declarations of the small-rational
// runtime entry points and the helpers @quidra.real.* written in LLVM IR.
// The helpers take the small-rational fast paths inline (integer +, - and *
// with overflow checks, comparisons by cross multiplication in i128,
// negation, conversions from fixed-width integers), the other small cases
// through the non-allocating quidra_real_small_* entry points, and the
// general form through the runtime's managed nodes: an operand is promoted
// to a node, the node operation of the runtime prelude runs, and its result
// is demoted to the small form when it has one.
//
// Every operation keeps the values and errors of the node operations: a
// small rational is the canonical form of the same rational value.

#include "llvm_text/llvm_callee.hpp"
#include "llvm_text/llvm_type.hpp"

#include <span>
#include <string>
#include <string_view>

namespace quidra::llvm_backend {

// The LLVM type of a value of type `real`.
inline constexpr llvm_text::LlvmType exact_real_type =
    llvm_text::LlvmType::structure(llvm_text::types::i64, llvm_text::types::i64);

// The `real` value 0/0, which no value takes: the contents of a slot that
// holds no value, and the result of a failed parse.
inline constexpr std::string_view exact_real_none = "zeroinitializer";

// The names of the helpers, as call targets (without the leading '@').
namespace real_helper {
inline constexpr std::string_view retain = "quidra.real.retain";
inline constexpr std::string_view release = "quidra.real.release";
inline constexpr std::string_view literal = "quidra.real.literal";
inline constexpr std::string_view parse = "quidra.real.parse";
inline constexpr std::string_view is_none = "quidra.real.is_none";
inline constexpr std::string_view adopt_node = "quidra.real.adopt_node";
inline constexpr std::string_view unary = "quidra.real.unary";
inline constexpr std::string_view text = "quidra.real.text";
inline constexpr std::string_view neg = "quidra.real.neg";
inline constexpr std::string_view binary = "quidra.real.binary";
inline constexpr std::string_view compare = "quidra.real.compare";
inline constexpr std::string_view pow = "quidra.real.pow";
inline constexpr std::string_view from_i64 = "quidra.real.from_i64";
inline constexpr std::string_view from_u64 = "quidra.real.from_u64";
inline constexpr std::string_view from_float64 = "quidra.real.from_float64";
inline constexpr std::string_view from_bigint = "quidra.real.from_bigint";
inline constexpr std::string_view to_bigint = "quidra.real.to_bigint";
inline constexpr std::string_view try_bigint = "quidra.real.try_bigint";
inline constexpr std::string_view try_i64 = "quidra.real.try_i64";
inline constexpr std::string_view try_u64 = "quidra.real.try_u64";
inline constexpr std::string_view try_float64 = "quidra.real.try_float64";
inline constexpr std::string_view try_float32 = "quidra.real.try_float32";
inline constexpr std::string_view to_float64 = "quidra.real.to_float64";
inline constexpr std::string_view to_float32 = "quidra.real.to_float32";
inline constexpr std::string_view cast_fits = "quidra.real.cast_fits";
} // namespace real_helper

// The prefix every helper call names; a module whose bodies or helpers
// contain it needs the support block.
inline constexpr std::string_view exact_real_helper_prefix = "@quidra.real.";

// The support block: the declarations of the small-rational runtime entry
// points, then the helpers. The node entry points it calls are declared by
// the runtime prelude.
std::string_view exact_real_support_text();

// The runtime entry points the support block declares.
std::span<const llvm_text::LlvmCallee* const> exact_real_support_declarations();

// The exact-real intrinsics that only some modules use (real.op and the
// interpolation formats of real) have a support block of their own: the
// declarations of their runtime entry points and the helpers
// @quidra.exact.*, which a module gets when it names one of them. The
// helpers return `real` values through the support block above.
namespace exact_helper {
// push(list, value): the argument list with value appended (null starts one).
inline constexpr std::string_view push = "quidra.exact.push";
// apply(provider, opcode, list): the operation's value; consumes the list.
inline constexpr std::string_view apply = "quidra.exact.apply";
// format(value, integer width, fractional, significant, zero): the text of
// an interpolation format.
inline constexpr std::string_view format = "quidra.exact.format";
// round(value, single, line, column): the certified rounding, as double.
inline constexpr std::string_view round = "quidra.exact.round";
} // namespace exact_helper
inline constexpr std::string_view exact_extension_helper_prefix = "@quidra.exact.";
std::string_view exact_extension_support_text();
std::span<const llvm_text::LlvmCallee* const> exact_extension_support_declarations();

// The small form of a real literal's decimal spelling (digits, an optional
// fraction and an optional exponent, as quidra_bigreal_literal reads it),
// when it has one: its numerator and denominator in lowest terms.
struct SmallRational {
    long long numerator;
    long long denominator;
};
bool small_rational_literal(std::string_view spelling, SmallRational& out);

} // namespace quidra::llvm_backend
