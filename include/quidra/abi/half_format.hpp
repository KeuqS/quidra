#pragma once

// The 16-bit real formats: real16 (IEEE 754 binary16) and real16b
// (bfloat16), as values the compiler and the runtime compute with.
//
// Owns: the rounding of a binary64 or binary32 value to either format (once,
// to the nearest value, ties to even, subnormals included), the exact
// widening of their values to binary32 and binary64, and Real16 and
// Real16b, value types whose arithmetic is the per-operation reference of
// both types (docs/spec/numeric-and-bin.md): the operation computed in
// binary32 and rounded once to the format. Binary32 holds every value of
// both formats, and its +, -, * and / results round correctly to them
// (24 >= 2 * 11 + 2 bits), so the reference is correctly rounded.
//
// Standard library only (an abi header), so that the compiler, the runtime
// and device code can include it.

#include <bit>
#include <cmath>
#include <cstdint>
#include <limits>

namespace quidra::abi::half {

// One of the two formats: its significand precision (the implicit bit
// included), the exponent of its smallest normal value and of its largest
// finite value.
struct HalfFormat {
    int precision;
    int min_exponent;
    int max_exponent;
};

inline constexpr HalfFormat binary16{11, -14, 15};
inline constexpr HalfFormat bfloat16{8, -126, 127};

// `value` rounded to `format`, ties to even, as the format's 16 bits; an
// infinity of its sign when the rounded magnitude is beyond the largest
// finite value, and the quiet NaN for a NaN.
inline std::uint16_t round_to(double value, const HalfFormat& format) {
    const auto nearest_even = [](double units) {
        const double lower = std::floor(units);
        const auto whole = static_cast<std::uint32_t>(lower);
        const double remainder = units - lower;
        return static_cast<double>(whole +
            (remainder > 0.5 || (remainder == 0.5 && (whole & 1U))));
    };
    const int fraction_bits = format.precision - 1;
    const int exponent_bits = 15 - fraction_bits;
    const std::uint16_t exponent_all = static_cast<std::uint16_t>((1U << exponent_bits) - 1U);
    const std::uint16_t sign = std::signbit(value) ? 0x8000U : 0U;
    if (std::isnan(value))
        return static_cast<std::uint16_t>((exponent_all << fraction_bits) |
                                          (1U << (fraction_bits - 1)));
    const double magnitude = std::fabs(value);
    const auto infinity = static_cast<std::uint16_t>(sign | (exponent_all << fraction_bits));
    if (std::isinf(magnitude)) return infinity;
    if (magnitude == 0.0) return sign;
    int exponent = 0;
    std::frexp(magnitude, &exponent);  // magnitude in [2^(exponent-1), 2^exponent)
    const int leading = exponent - 1;
    const int bias = format.max_exponent;
    if (leading < format.min_exponent) {
        // Subnormal: units of the smallest subnormal, 2^(min - fraction_bits).
        const double units =
            nearest_even(std::ldexp(magnitude, fraction_bits - format.min_exponent));
        const auto bits = static_cast<std::uint32_t>(units);
        // 2^fraction_bits units is the smallest normal value, whose encoding
        // follows the subnormals'.
        return static_cast<std::uint16_t>(sign | bits);
    }
    double significand = nearest_even(std::ldexp(magnitude, fraction_bits - leading));
    int biased = leading + bias;
    if (significand == std::ldexp(1.0, format.precision)) {
        significand = std::ldexp(1.0, fraction_bits);
        ++biased;
    }
    if (biased >= static_cast<int>(exponent_all)) return infinity;
    const auto fraction =
        static_cast<std::uint32_t>(significand) & ((1U << fraction_bits) - 1U);
    return static_cast<std::uint16_t>(sign | (static_cast<std::uint32_t>(biased) << fraction_bits) |
                                      fraction);
}

// The value of `bits` of `format`, exactly.
inline double value_of(std::uint16_t bits, const HalfFormat& format) {
    const int fraction_bits = format.precision - 1;
    const int exponent_bits = 15 - fraction_bits;
    const auto exponent_all = (1U << exponent_bits) - 1U;
    const bool negative = (bits & 0x8000U) != 0;
    const auto biased = (bits >> fraction_bits) & exponent_all;
    const auto fraction = bits & ((1U << fraction_bits) - 1U);
    double magnitude = 0.0;
    if (biased == exponent_all) {
        magnitude = fraction != 0 ? std::numeric_limits<double>::quiet_NaN()
                                  : std::numeric_limits<double>::infinity();
    } else if (biased == 0) {
        magnitude = std::ldexp(static_cast<double>(fraction), format.min_exponent - fraction_bits);
    } else {
        magnitude = std::ldexp(static_cast<double>(fraction | (1U << fraction_bits)),
                               static_cast<int>(biased) - format.max_exponent - fraction_bits);
    }
    return negative ? -magnitude : magnitude;
}

inline bool is_finite(std::uint16_t bits, const HalfFormat& format) {
    const int fraction_bits = format.precision - 1;
    const auto exponent_all = (1U << (15 - fraction_bits)) - 1U;
    return ((bits >> fraction_bits) & exponent_all) != exponent_all;
}

// Round a whole integer directly, retaining the discarded bits until the
// target precision is known. This also handles the full unsigned 64-bit range.
inline std::uint16_t round_integer(std::uint64_t magnitude,bool negative,const HalfFormat& format) {
    const auto sign=negative?0x8000u:0u;
    if(magnitude==0)return static_cast<std::uint16_t>(sign);
    int bits=0;for(auto rest=magnitude;rest!=0;rest>>=1)++bits;
    const int precision=format.precision;
    const int shift=bits-precision;
    auto kept=shift>0?magnitude>>shift:magnitude<<(-shift);
    if(shift>0){
        const auto rest=magnitude&((std::uint64_t{1}<<shift)-1);
        const auto midpoint=std::uint64_t{1}<<(shift-1);
        if(rest>midpoint||(rest==midpoint&&(kept&1)!=0))++kept;
    }
    int exponent=bits-1;
    if(kept==(std::uint64_t{1}<<precision)){kept>>=1;++exponent;}
    if(exponent>format.max_exponent)return static_cast<std::uint16_t>(sign|(format.precision==11?0x7c00u:0x7f80u));
    return static_cast<std::uint16_t>(sign|((exponent+(1-format.min_exponent))<<(format.precision-1))|
        (kept&((std::uint64_t{1}<<(format.precision-1))-1)));
}

// A value of one of the formats. Arithmetic computes in binary32 and rounds
// once to the format.
template <const HalfFormat& F>
struct Half {
    std::uint16_t bits{};

    Half() = default;
    static Half from_bits(std::uint16_t value) {
        Half result;
        result.bits = value;
        return result;
    }
    explicit Half(double value) : bits(round_to(value, F)) {}
    explicit Half(float value) : bits(round_to(static_cast<double>(value), F)) {}
    explicit Half(int value) : bits(round_to(static_cast<double>(value), F)) {}
    explicit operator double() const { return value_of(bits, F); }
    explicit operator float() const { return static_cast<float>(value_of(bits, F)); }

    friend Half operator+(Half a, Half b) { return Half(static_cast<float>(a) + static_cast<float>(b)); }
    friend Half operator-(Half a, Half b) { return Half(static_cast<float>(a) - static_cast<float>(b)); }
    friend Half operator*(Half a, Half b) { return Half(static_cast<float>(a) * static_cast<float>(b)); }
    friend Half operator/(Half a, Half b) { return Half(static_cast<float>(a) / static_cast<float>(b)); }
    friend Half operator-(Half a) { return from_bits(static_cast<std::uint16_t>(a.bits ^ 0x8000U)); }
    friend bool operator==(Half a, Half b) { return static_cast<float>(a) == static_cast<float>(b); }
    friend bool operator!=(Half a, Half b) { return !(a == b); }
    friend bool operator<(Half a, Half b) { return static_cast<float>(a) < static_cast<float>(b); }
    friend bool operator<=(Half a, Half b) { return static_cast<float>(a) <= static_cast<float>(b); }
    friend bool operator>(Half a, Half b) { return static_cast<float>(a) > static_cast<float>(b); }
    friend bool operator>=(Half a, Half b) { return static_cast<float>(a) >= static_cast<float>(b); }
};

using Real16 = Half<binary16>;
using Real16b = Half<bfloat16>;

template <const HalfFormat& F>
inline Half<F> pow(Half<F> base, Half<F> exponent) {
    return Half<F>(std::pow(static_cast<float>(base), static_cast<float>(exponent)));
}

template <const HalfFormat& F>
inline bool isfinite(Half<F> value) {
    return is_finite(value.bits, F);
}

} // namespace quidra::abi::half
