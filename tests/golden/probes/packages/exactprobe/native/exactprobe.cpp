// The exact-real providers of the exactprobe probe package, so that Core's
// probes and tests never depend on Math.
//
// "exactprobe" (version 2 of the provider interface):
//   atom 1, σ: the square root of two, from its decimal expansion;
//   atom 2, π: pi, from its decimal expansion;
//   atom 3, ω: a value between 1 and 2 whose enclosure never narrows, so
//              nothing that needs more than that can be decided about it;
//   operation 101, flip (one argument): negation, its own inverse, so
//              flip(flip(x)) is canonicalized to x;
//   operation 102, first (two arguments): its first argument.
// "exactprobe_v1" (version 1): atom 1 is the square root of two and unary
// operation 1 is negation.
#include <quidra/native_extension.h>

#include <cmath>
#include <cstdint>
#include <string>

namespace {

const char* const root2_digits =
    "1.41421356237309504880168872420969807856967187537694807317667973799073247846210703885038753432764157273501384623091229702492483605585073721264412149709993583141322266592750559275579995050115278206057147";
const char* const pi_digits =
    "3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975";

// The enclosures of a decimal expansion are as tight as its digits allow.
constexpr std::uint32_t decimal_precision_limit = 660;

// Decimal integer text arithmetic, enough for the enclosures below.
std::string twice(const std::string& digits) {
    std::string out(digits.size(), '0');
    int carry = 0;
    for (std::size_t i = digits.size(); i > 0; --i) {
        const int value = (digits[i - 1] - '0') * 2 + carry;
        out[i - 1] = static_cast<char>('0' + value % 10);
        carry = value / 10;
    }
    if (carry) out.insert(out.begin(), static_cast<char>('0' + carry));
    return out;
}
std::string plus_one(std::string digits) {
    for (std::size_t i = digits.size(); i > 0; --i) {
        if (digits[i - 1] != '9') {
            ++digits[i - 1];
            return digits;
        }
        digits[i - 1] = '0';
    }
    return "1" + digits;
}
// digits / 10^k, rounded down or up.
std::string divide_pow10(const std::string& digits, std::size_t k, bool up) {
    std::string quotient = digits.size() > k ? digits.substr(0, digits.size() - k) : "0";
    bool remainder = false;
    for (std::size_t i = digits.size() > k ? digits.size() - k : 0; i < digits.size(); ++i)
        remainder = remainder || digits[i] != '0';
    if (up && remainder) quotient = plus_one(quotient);
    const auto first = quotient.find_first_not_of('0');
    return first == std::string::npos ? "0" : quotient.substr(first);
}
std::string negated(const char* text) {
    const std::string value(text);
    if (value == "0") return value;
    return value[0] == '-' ? value.substr(1) : "-" + value;
}

thread_local std::string interval_low;
thread_local std::string interval_high;

void set_interval(qcore_exact_interval* out, std::string low, std::string high,
                  std::int64_t exponent) {
    interval_low = std::move(low);
    interval_high = std::move(high);
    out->low = interval_low.c_str();
    out->high = interval_high.c_str();
    out->exponent = exponent;
}

// [D / 10^k, (D + 1) / 10^k] for the k fractional digits D of an expansion,
// with dyadic bounds at `precision` fractional bits.
void decimal_enclosure(const char* expansion, std::uint32_t precision, qcore_exact_interval* out) {
    std::string digits(expansion);
    const auto dot = digits.find('.');
    const std::size_t fraction = digits.size() - dot - 1;
    digits.erase(dot, 1);
    if (precision > decimal_precision_limit) precision = decimal_precision_limit;
    std::string low = digits;
    std::string high = plus_one(digits);
    for (std::uint32_t i = 0; i < precision; ++i) {
        low = twice(low);
        high = twice(high);
    }
    set_interval(out, divide_pow10(low, fraction, false), divide_pow10(high, fraction, true),
                 -static_cast<std::int64_t>(precision));
}

const char* exactprobe_spelling(std::uint32_t opcode) {
    switch (opcode) {
        case 1: return "σ";
        case 2: return "π";
        case 3: return "ω";
        case 101: return "flip";
        case 102: return "first";
        default: return nullptr;
    }
}
std::uint32_t exactprobe_arity(std::uint32_t opcode) {
    switch (opcode) {
        case 101: return 1;
        case 102: return 2;
        default: return 0;
    }
}
std::uint32_t exactprobe_flags(std::uint32_t opcode) {
    switch (opcode) {
        case 1:
        case 2:
        case 3: return QCORE_EXACT_UNARY_TOTAL | QCORE_EXACT_UNARY_RESULT_POSITIVE;
        case 101:
        case 102: return QCORE_EXACT_UNARY_TOTAL;
        default: return 0;
    }
}
void* exactprobe_canonicalize(std::uint32_t opcode, const void* const* args, std::uint32_t n) {
    if (opcode == 101 && n == 1 && qcore_exact_real_is_node(args[0], "exactprobe", 101))
        return qcore_exact_real_argument(args[0], 0);
    return nullptr;
}
int exactprobe_prove(std::uint32_t opcode, const void* const*, std::uint32_t n, std::uint32_t query) {
    if (opcode == 3 && n == 0) {
        if (query == QCORE_EXACT_QUERY_ZERO || query == QCORE_EXACT_QUERY_NEGATIVE)
            return QCORE_EXACT_NO;
        if (query == QCORE_EXACT_QUERY_POSITIVE) return QCORE_EXACT_YES;
    }
    return QCORE_EXACT_UNKNOWN;
}
int exactprobe_refine(std::uint32_t opcode, const qcore_exact_interval* args, std::uint32_t n,
                      std::uint32_t precision, qcore_exact_interval* out) {
    switch (opcode) {
        case 1:
            decimal_enclosure(root2_digits, precision, out);
            return 1;
        case 2:
            decimal_enclosure(pi_digits, precision, out);
            return 1;
        case 3:
            set_interval(out, "1", "2", 0);
            return 1;
        case 101:
            if (n != 1) return 0;
            set_interval(out, negated(args[0].high), negated(args[0].low), args[0].exponent);
            return 1;
        case 102:
            if (n != 2) return 0;
            set_interval(out, args[0].low, args[0].high, args[0].exponent);
            return 1;
        default:
            return 0;
    }
}

const char* exactprobe_v1_atom_decimal(std::uint32_t opcode) {
    return opcode == 1 ? root2_digits : nullptr;
}
int exactprobe_v1_unary_evaluate(std::uint32_t opcode, double input, double* output) {
    if (!output || !std::isfinite(input)) return 0;
    switch (opcode) {
        case 1: *output = -input; return 1;
        default: return 0;
    }
}
std::uint32_t exactprobe_v1_unary_flags(std::uint32_t opcode) {
    return opcode == 1 ? QCORE_EXACT_UNARY_TOTAL : 0;
}

struct ExactprobeProviderRegistration {
    ExactprobeProviderRegistration() {
        qcore_exact_provider_v2 provider{};
        provider.struct_size = sizeof(provider);
        provider.name = "exactprobe";
        provider.spelling = exactprobe_spelling;
        provider.arity = exactprobe_arity;
        provider.flags = exactprobe_flags;
        provider.canonicalize = exactprobe_canonicalize;
        provider.prove = exactprobe_prove;
        provider.refine = exactprobe_refine;
        (void)qcore_exact_real_provider_register_v2(&provider);
        (void)qcore_exact_real_provider_register("exactprobe_v1", exactprobe_v1_atom_decimal);
        (void)qcore_exact_real_provider_register_unary(
            "exactprobe_v1", exactprobe_v1_unary_evaluate, exactprobe_v1_unary_flags);
    }
};

const ExactprobeProviderRegistration exactprobe_provider_registration{};

} // namespace
