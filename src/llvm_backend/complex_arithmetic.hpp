#pragma once

// ComplexArithmetic: the complex types in generated code.
//
// A fixed-width complex value is an LLVM structure of its two parts, the
// real part first: com16 { half, half }, com16b { i16, i16 } (bfloat16
// bits), com32 { float, float }, com64 { double, double }; the layout of a
// tensor element of its dtype. +, - and * compute each part's operations in
// the part type, rounding every operation once (* is (ac - bd) + (ad + bc)i,
// without fused operations), / is Smith's algorithm in the part type, and
// == and != compare the parts. Every operation's result, and for / each of
// its intermediate values, is tested: a value that is not finite stops the
// program at the operation through quidra_runtime_real_fail, naming the
// complex type (REAL_OVERFLOW "com32 multiplication overflow", or
// DIVISION_BY_ZERO "com32 division by zero" for a zero divisor). ^, the
// conversions, the text and parsing are runtime entries
// (src/runtime_complex.cpp) that take and give the parts widened exactly to
// binary64.
//
// An exact com value is a pointer to a managed box of two `real` values
// (abi::complex_box_layout), shared and immutable like a string's text; its
// arithmetic, equality, text and parsing are runtime entries.
//
// Owns: the emission of complex values, and the support block a module
// whose bodies name a complex runtime entry carries, which declares them.

#include "llvm_backend/statement_attribution.hpp"
#include "llvm_backend/temporary_names.hpp"
#include "llvm_text/llvm_builder.hpp"
#include "llvm_text/llvm_callee.hpp"
#include "quidra/types.hpp"

#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace quidra::llvm_backend {

// The LLVM type of a fixed-width complex type's value.
llvm_text::LlvmType fixed_complex_type(const Type& type);

// The dtype code of a fixed-width complex type, which the runtime entries
// and the failures take.
int complex_kind_code(const Type& type);

// The prefixes a module's bodies contain when they name a complex entry.
inline constexpr std::string_view complex_entry_prefix = "@quidra_complex_";
inline constexpr std::string_view com_entry_prefix = "@quidra_com_";

std::span<const llvm_text::LlvmCallee* const> complex_support_declarations();
std::string_view complex_support_text();

// A part of a fixed-width complex value widened exactly to binary64.
std::string widen_complex_part(llvm_text::LlvmBuilder& builder, TemporaryNames& names,
                               const Type& part, const std::string& value);

// Narrow exactly widened parts into their stored representation.
std::string narrow_complex_part(llvm_text::LlvmBuilder& builder, TemporaryNames& names,
                                const Type& part, const std::string& value);
void load_complex_parts(llvm_text::LlvmBuilder& builder, TemporaryNames& names,
                        const Type& type, const std::string& out, const std::string& slot);

// The scalar or array leaf converted into a complex type. An exact com target
// returns its owned box; a fixed complex target returns success and writes its
// exactly widened, rounded parts to slot ([2 x double]).
std::string emit_complex_conversion(llvm_text::LlvmBuilder& builder, TemporaryNames& names,
                                    const Type& source, const Type& target,
                                    const std::string& value, const std::string& slot);

// The text of the complex `value` of `type`, a managed string the caller
// releases: each part's text joined by the imaginary part's sign and
// followed by i; the format applies to each part (none: -1, -1, -1, false),
// and a com part without a significant-digit count prints to the display
// digits, as a `real` does.
std::string emit_complex_text(llvm_text::LlvmBuilder& builder, TemporaryNames& names,
                              const Type& type, const std::string& value, int integer_width,
                              int fractional, int significant, bool zero);

class ComplexArithmetic {
public:
    ComplexArithmetic(llvm_text::LlvmBuilder& builder, TemporaryNames& names,
                      const StatementAttribution& sites)
        : builder_(builder), names_(names), sites_(sites) {}

    // A part of the fixed-width complex `value` (0 real, 1 imaginary).
    std::string part(const Type& type, const std::string& value, unsigned index);
    // `out` = the fixed-width complex value of its parts.
    void make(const Type& type, const std::string& out, const std::string& re,
              const std::string& im);
    // A part widened exactly to binary64, and a binary64 value that a part
    // type holds narrowed to it (exact).
    std::string widen(const Type& part, const std::string& value);
    std::string narrow(const Type& part, const std::string& value);

    // `out` = left op right on fixed-width complex values (+ - * / == !=).
    void binary(const std::string& op, const Type& type, const std::string& out,
                const std::string& left, const std::string& right, std::uint32_t line,
                std::uint32_t column);
    // `out` = left ^ right through the runtime, its parts written to `slot`
    // ([2 x double]).
    void power(const Type& type, const std::string& out, const std::string& left,
               const std::string& right, const std::string& slot, std::uint32_t line,
               std::uint32_t column);
    void negate(const Type& type, const std::string& out, const std::string& value);

    // An exact com value's operations: `out` = left op right (+ - * / == !=).
    void com_binary(const std::string& op, const std::string& out, const std::string& left,
                    const std::string& right, std::uint32_t line, std::uint32_t column);
    void com_negate(const std::string& out, const std::string& value, std::uint32_t line,
                    std::uint32_t column);
    // `out` = the com value of two exact reals, and a com value's part
    // (borrowed from its box).
    void com_make(const std::string& out, const std::string& re, const std::string& im);
    void com_part(const std::string& out, const std::string& value, unsigned index);

    // `out` = the fixed-width complex value whose binary64 parts are in
    // `slot`.
    void load_parts(const Type& type, const std::string& out, const std::string& slot);

private:
    // One operation of the part type, rounded once to it.
    std::string op(llvm_text::BinaryOp operation, const Type& part, const std::string& left,
                   const std::string& right);
    // The i1 that holds when the part value is NaN or an infinity.
    std::string nonfinite(const Type& part, const std::string& value);
    std::string any(const std::vector<std::string>& conditions);
    // A part widened to a type comparisons and absolute values take
    // (float for real16b; the part type itself otherwise), and its type.
    std::string comparable(const Type& part, const std::string& value);
    llvm_text::LlvmType comparable_type(const Type& part);
    std::string magnitude(const Type& part, const std::string& value);
    // Stops the program when `bad` holds: the failure of `operation` on
    // `type` (a zero divisor when `zero_divisor` holds).
    void fail_if(const std::string& bad, const Type& type, int operation,
                 const std::string& zero_divisor, std::uint32_t line, std::uint32_t column);
    void divide(const Type& type, const std::string& out, const std::string& left,
                const std::string& right, std::uint32_t line, std::uint32_t column);

    llvm_text::LlvmBuilder& builder_;
    TemporaryNames& names_;
    const StatementAttribution& sites_;
};

} // namespace quidra::llvm_backend
