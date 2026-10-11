#pragma once

// The codes of the runtime's exact numbers (big integers and exact reals),
// which generated code passes to the runtime, and the budget of exact-real
// refinement.

#include <cstddef>

namespace quidra::abi {

// The operation of quidra_bigint_binary and quidra_bigreal_binary. Exact
// reals take add to divide; remainder is an integer operation.
namespace exact_binary_opcode {
inline constexpr int add = 1;
inline constexpr int subtract = 2;
inline constexpr int multiply = 3;
inline constexpr int divide = 4;
inline constexpr int remainder = 5;
} // namespace exact_binary_opcode

// The text of an exact real is its canonical text (quidra_bigreal_text and
// quidra_real_small_text with this many significant digits, which printing,
// string conversion and interpolation without a format pass); interpolation
// formats go through quidra_real_format.
inline constexpr int exact_real_canonical_text = 0;

// The deterministic budget of exact-real refinement: a decision (a
// comparison, a conversion, digits) refines its value with
// exact_refine_initial_bits of precision, doubling up to
// exact_refine_max_bits, and visits at most exact_refine_max_visits
// expression nodes over all of them, nested at most exact_refine_max_depth
// deep. Counts only, never time, so a decision is the same on every run and
// platform.
inline constexpr long long exact_refine_initial_bits = 64;
inline constexpr long long exact_refine_max_bits = 4096;
inline constexpr std::size_t exact_refine_max_visits = std::size_t{1} << 16;
inline constexpr std::size_t exact_refine_max_depth = 2048;

} // namespace quidra::abi
