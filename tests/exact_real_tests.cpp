#include "quidra/abi/exact_codes.hpp"
#include "quidra/abi/layout.hpp"
#include "quidra/abi/runtime_entry_points.hpp"
#include "quidra/native_extension.h"

#include <array>
#include <bit>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <limits>
#include <string>
#include <vector>

// The small form of the exact type `real` (abi::ExactRealValue with a
// nonzero denominator) and its general form, a managed runtime node, give
// the same values. Every small operation is checked against the node
// operation on the same operands: a small result must equal the node
// result demoted, and the node result of an operation the small path
// declines (an overflow of the 64-bit words, a division by zero) is the
// general path's. Demotion keeps the canonical invariant: a value with a
// small form is stored in it, in lowest terms.

namespace {

using quidra::abi::ExactRealValue;
namespace opcode = quidra::abi::exact_binary_opcode;

int failures = 0;

void expect(bool condition, const std::string& what) {
    if (!condition) {
        std::fprintf(stderr, "exact real test failed: %s\n", what.c_str());
        ++failures;
    }
}

constexpr long long max64 = std::numeric_limits<long long>::max();

std::string text_of(void* node) {
    char* text = quidra_bigreal_text(node, quidra::abi::exact_real_canonical_text);
    std::string out = text ? text : "";
    quidra_managed_release(text, nullptr);
    return out;
}

std::string small_text(const ExactRealValue& value) {
    char* text = quidra_real_small_text(value.numerator, value.denominator,
                                        quidra::abi::exact_real_canonical_text);
    std::string out = text ? text : "";
    quidra_managed_release(text, nullptr);
    return out;
}

void release_node(void* node) {
    quidra_managed_release(node, reinterpret_cast<void*>(&quidra_bigreal_drop));
}

std::string describe(const ExactRealValue& value) {
    return std::to_string(value.numerator) + "/" + std::to_string(value.denominator);
}

bool canonical(const ExactRealValue& value) {
    if (value.denominator <= 0) return false;
    if (value.numerator == std::numeric_limits<long long>::min()) return false;
    if (value.numerator == 0) return value.denominator == 1;
    auto a = static_cast<unsigned long long>(value.numerator < 0 ? -value.numerator : value.numerator);
    auto b = static_cast<unsigned long long>(value.denominator);
    while (b) {
        const auto t = a % b;
        a = b;
        b = t;
    }
    return a == 1;
}

// The node result of left OP right, demoted: the general path.
ExactRealValue node_binary(const ExactRealValue& left, const ExactRealValue& right, int operation,
                           std::string& text) {
    void* a = quidra_real_promote(left.numerator, left.denominator);
    void* b = quidra_real_promote(right.numerator, right.denominator);
    void* result = quidra_bigreal_binary(a, b, operation, 0, 0);
    text = text_of(result);
    release_node(a);
    release_node(b);
    ExactRealValue out{};
    quidra_real_demote(result, &out);
    return out;
}

const char* operation_name(int operation) {
    switch (operation) {
        case opcode::add: return "+";
        case opcode::subtract: return "-";
        case opcode::multiply: return "*";
        default: return "/";
    }
}

void differential(const std::vector<ExactRealValue>& values) {
    for (const auto& left : values) {
        expect(canonical(left), "operand " + describe(left) + " is canonical");
        for (const auto& right : values) {
            for (const int operation : {opcode::add, opcode::subtract, opcode::multiply, opcode::divide}) {
                if (operation == opcode::divide && right.numerator == 0) continue;
                const auto what = describe(left) + " " + operation_name(operation) + " " + describe(right);
                std::string node_text;
                const auto general = node_binary(left, right, operation, node_text);
                ExactRealValue small{};
                if (quidra_real_small_binary(left.numerator, left.denominator, right.numerator,
                                             right.denominator, operation, &small)) {
                    expect(canonical(small), what + ": small result is canonical");
                    expect(general.denominator != 0 && general.numerator == small.numerator &&
                               general.denominator == small.denominator,
                           what + ": small result " + describe(small) + " equals the node result");
                    expect(small_text(small) == node_text, what + ": text " + node_text);
                } else if (general.denominator != 0) {
                    // Declined by the small path, small after reduction.
                    expect(canonical(general), what + ": demoted result is canonical");
                    expect(small_text(general) == node_text, what + ": demoted text " + node_text);
                } else {
                    release_node(reinterpret_cast<void*>(static_cast<std::uintptr_t>(general.numerator)));
                }
            }
        }
    }
}

void boundaries() {
    ExactRealValue out{};
    // INT64_MAX + 1 leaves the small form; the node keeps the exact value.
    expect(!quidra_real_small_binary(max64, 1, 1, 1, opcode::add, &out), "INT64_MAX + 1 is not small");
    std::string text;
    auto general = node_binary({max64, 1}, {1, 1}, opcode::add, text);
    expect(general.denominator == 0, "INT64_MAX + 1 stays a node");
    expect(text == "9223372036854775808.0", "INT64_MAX + 1 prints exactly, got " + text);
    // ... and comes back to the small form when it fits again.
    void* node = reinterpret_cast<void*>(static_cast<std::uintptr_t>(general.numerator));
    void* one = quidra_real_promote(1, 1);
    void* back = quidra_bigreal_binary(node, one, opcode::subtract, 0, 0);
    release_node(node);
    release_node(one);
    ExactRealValue demoted{};
    quidra_real_demote(back, &demoted);
    expect(demoted.numerator == max64 && demoted.denominator == 1, "INT64_MAX + 1 - 1 demotes to INT64_MAX");
    // -INT64_MAX - 1 is INT64_MIN, which the small form excludes.
    expect(!quidra_real_small_binary(-max64, 1, 1, 1, opcode::subtract, &out), "INT64_MIN is not small");
    general = node_binary({-max64, 1}, {1, 1}, opcode::subtract, text);
    expect(general.denominator == 0, "INT64_MIN stays a node");
    if (general.denominator == 0)
        release_node(reinterpret_cast<void*>(static_cast<std::uintptr_t>(general.numerator)));
    // A product beyond 64 bits whose quotient is small again.
    expect(!quidra_real_small_binary(max64, 1, 2, 1, opcode::multiply, &out), "INT64_MAX * 2 is not small");
    // Cross reduction keeps products small: (2^62/3) * (3/2^61) = 2.
    expect(quidra_real_small_binary(1LL << 62, 3, 3, 1LL << 61, opcode::multiply, &out) &&
               out.numerator == 2 && out.denominator == 1,
           "cross-reduced product is 2");
    // Division by zero is left to the general path, which reports it.
    expect(!quidra_real_small_binary(1, 1, 0, 1, opcode::divide, &out), "division by zero is not small");
}

void conversions() {
    double d = 0.0;
    expect(quidra_real_small_try_float64(1, 3, &d) && d == 1.0 / 3.0, "1/3 as real64");
    float f = 0.0F;
    expect(quidra_real_small_try_float32(1, 10, &f) && f == 0.1F, "1/10 as real32");
    long long i = 0;
    expect(quidra_real_small_try_i64(-7, 1, 8, &i) && i == -7, "-7 as int8");
    expect(!quidra_real_small_try_i64(300, 1, 8, &i), "300 is no int8");
    expect(!quidra_real_small_try_i64(1, 2, 64, &i), "1/2 is no integer");
    unsigned long long u = 0;
    expect(quidra_real_small_try_u64(255, 1, 8, &u) && u == 255, "255 as nat8");
    expect(!quidra_real_small_try_u64(-1, 1, 64, &u), "-1 is no nat64");
    expect(quidra_real_small_cast_fits(5, 1, 3, 8), "5 fits int8");
    expect(!quidra_real_small_cast_fits(5, 2, 1, 0), "5/2 is no bigint");
    // The small path and the node path observe the same value.
    for (const auto& [n, den] : std::vector<std::pair<long long, long long>>{
             {1, 3}, {-22, 7}, {max64, 1}, {1, max64}, {123456789, 1000}}) {
        void* node = quidra_real_promote(n, den);
        double from_node = 0.0, from_small = 0.0;
        expect(quidra_bigreal_try_float64(node, &from_node) &&
                   quidra_real_small_try_float64(n, den, &from_small) && from_node == from_small,
               "real64 of " + std::to_string(n) + "/" + std::to_string(den));
        expect(text_of(node) == small_text({n, den}),
               "text of " + std::to_string(n) + "/" + std::to_string(den));
        release_node(node);
    }
}

// Exact rationals round to the nearest real64 or real32, ties to even,
// subnormals included, and a value beyond the finite range is declined.
void* rational(const char* numerator, const char* denominator) {
    return qcore_exact_real_rational(numerator, denominator);
}
void rational_inspection() {
    for (const auto& entry : std::vector<std::array<const char*, 4>>{
             {"6", "-8", "-3", "4"}, {"0", "-99", "0", "1"},
             {"340282366920938463463374607431768211456", "3",
              "340282366920938463463374607431768211456", "3"}}) {
        void* node = rational(entry[0], entry[1]);
        const char* numerator = nullptr;
        const char* denominator = nullptr;
        expect(qcore_exact_real_rational_parts(node, &numerator, &denominator) == 1,
               "rational inspection succeeds");
        release_node(node);
        expect(numerator && denominator && std::strcmp(numerator, entry[2]) == 0 &&
                   std::strcmp(denominator, entry[3]) == 0,
               "reduced decimal parts survive source release");
    }
    const char* numerator = "old numerator";
    const char* denominator = "old denominator";
    expect(qcore_exact_real_rational_parts(nullptr, &numerator, &denominator) == 0 &&
               !numerator && !denominator, "null input clears both outputs");
    void* two = rational("2", "1");
    void* half = rational("1", "2");
    void* root = qcore_exact_real_pow(two, half);
    expect(qcore_exact_real_rational_parts(root, &numerator, &denominator) == 0 &&
               !numerator && !denominator, "irrational value is not approximated");
    expect(qcore_exact_real_rational_parts(two, &numerator, &numerator) == 0 && !numerator,
           "aliased outputs are refused");
    expect(qcore_exact_real_rational_parts(two, nullptr, &denominator) == 0 && !denominator,
           "missing output is refused");
    release_node(root);
    release_node(half);
    release_node(two);
}
void* power_of_two(long long exponent) {
    void* two = rational("2", "1");
    void* e = rational(std::to_string(exponent).c_str(), "1");
    void* out = qcore_exact_real_pow(two, e);
    release_node(two);
    release_node(e);
    return out;
}
void expect_real64(void* node, double expected, const std::string& what) {
    double out = 0.0;
    const bool ok = quidra_bigreal_try_float64(node, &out);
    expect(ok && std::bit_cast<std::uint64_t>(out) == std::bit_cast<std::uint64_t>(expected),
           what + " (got " + std::to_string(out) + ")");
    release_node(node);
}
void rounding() {
    // 2^53 + 1 lies halfway between 2^53 and 2^53 + 2: the even one.
    expect_real64(rational("9007199254740993", "1"), 9007199254740992.0, "2^53+1 ties to even");
    expect_real64(rational("9007199254740995", "1"), 9007199254740996.0, "2^53+3 ties to even");
    // 1 + 2^-53 and 1 + 3 * 2^-53, through the general rounding.
    expect_real64(rational("9007199254740993", "9007199254740992"), 1.0, "1 + 2^-53 ties to 1");
    expect_real64(rational("9007199254740995", "9007199254740992"), 1.0000000000000004,
                  "1 + 3 * 2^-53 ties to even");
    expect_real64(rational("9007199254740997", "9007199254740992"), 1.0000000000000004,
                  "1 + 5 * 2^-53 ties to even");
    // The smallest subnormal, and 1.5 of it, which ties to 2 of it.
    expect_real64(power_of_two(-1074), std::ldexp(1.0, -1074), "2^-1074");
    {
        void* three = rational("3", "1");
        void* half = power_of_two(-1075);
        expect_real64(qcore_exact_real_mul(three, half), std::ldexp(1.0, -1073),
                      "1.5 * 2^-1074 ties to even");
        release_node(three);
        release_node(half);
    }
    // Half of the smallest subnormal ties to zero; a bit more rounds up.
    expect_real64(power_of_two(-1075), 0.0, "2^-1075 ties to 0");
    // The largest finite value, and the midpoint above it, which overflows.
    {
        void* top = power_of_two(1024);
        void* gap = power_of_two(970);
        void* below = qcore_exact_real_sub(top, gap);
        double out = 0.0;
        expect(!quidra_bigreal_try_float64(below, &out), "2^1024 - 2^970 rounds beyond the range");
        void* max_gap = power_of_two(971);
        void* maximum = qcore_exact_real_sub(top, max_gap);
        expect_real64(maximum, std::numeric_limits<double>::max(), "the largest real64");
        release_node(top);
        release_node(gap);
        release_node(below);
        release_node(max_gap);
    }
    // real32: 2^24 + 1 ties to 2^24.
    {
        void* node = rational("16777217", "1");
        float f = 0.0F;
        expect(quidra_bigreal_try_float32(node, &f) && f == 16777216.0F, "2^24+1 as real32");
        release_node(node);
    }
    // The fast path of small rationals agrees with the general rounding.
    unsigned long long state = 88172645463325252ULL;
    for (int i = 0; i < 2000; ++i) {
        state ^= state << 13;
        state ^= state >> 7;
        state ^= state << 17;
        const long long n = static_cast<long long>(state % 2000000001ULL) - 1000000000LL;
        const long long d = static_cast<long long>((state >> 32) % 999999937ULL) + 1;
        void* node = quidra_real_promote(n, 1);
        void* denominator = quidra_real_promote(d, 1);
        void* quotient = qcore_exact_real_div(node, denominator);
        double general = 0.0, fast = 0.0;
        const auto reduced = [&] {
            ExactRealValue v{};
            quidra_real_demote(qcore_exact_real_retain(quotient), &v);
            return v;
        }();
        expect(quidra_bigreal_try_float64(quotient, &general) &&
                   quidra_real_small_try_float64(reduced.numerator, reduced.denominator, &fast) &&
                   std::bit_cast<std::uint64_t>(general) == std::bit_cast<std::uint64_t>(fast),
               "real64 of " + std::to_string(n) + "/" + std::to_string(d));
        release_node(node);
        release_node(denominator);
        release_node(quotient);
    }
}

// A symbolic value is converted only when refinement certifies the
// rounding: an atom whose enclosures shrink converts, one whose enclosure
// never narrows does not, the same way every time.
thread_local std::string probe_low, probe_high;
const char* probe_spelling(std::uint32_t opcode) {
    return opcode == 1 ? "third" : opcode == 2 ? "wide" :
           opcode == 3 ? "one" : opcode == 4 ? "power" : opcode == 5 ? "other_power" : nullptr;
}
std::uint32_t probe_arity(std::uint32_t opcode) { return opcode == 4 || opcode == 5 ? 2 : 0; }
// Opcode 1 is 1/3: [floor(2^p / 3), ceil(2^p / 3)] * 2^-p for p up to 62.
// Opcode 2 lies in [1, 2].
int probe_refine(std::uint32_t opcode, const qcore_exact_interval* args, std::uint32_t count,
                 std::uint32_t precision, qcore_exact_interval* out) {
    if (opcode == 1) {
        const unsigned p = precision > 62 ? 62 : precision;
        const unsigned long long scaled = 1ULL << p;
        probe_low = std::to_string(scaled / 3);
        probe_high = std::to_string(scaled / 3 + 1);
        out->low = probe_low.c_str();
        out->high = probe_high.c_str();
        out->exponent = -static_cast<std::int64_t>(p);
        return 1;
    }
    if (opcode == 2) {
        out->low = "1";
        out->high = "2";
        out->exponent = 0;
        return 1;
    }
    if (opcode == 3) {
        out->low = out->high = "1";
        out->exponent = 0;
        return 1;
    }
    if (opcode == 4 && count == 2 && args) {
        // A narrow certified probe: only 2^1 is supported. Compare the
        // dyadic text exactly; a floating approximation is not a proof.
        const auto exactly = [](const qcore_exact_interval& value, unsigned expected) {
            if (value.exponent > 1 || value.exponent < -4096) return false;
            std::string mantissa = std::to_string(expected);
            if (value.exponent == 1) {
                if (expected % 2) return false;
                mantissa = std::to_string(expected / 2);
            }
            for (std::int64_t e = value.exponent; e < 0; ++e) {
                unsigned carry = 0;
                for (auto it = mantissa.rbegin(); it != mantissa.rend(); ++it) {
                    const unsigned digit = static_cast<unsigned>(*it - '0') * 2 + carry;
                    *it = static_cast<char>('0' + digit % 10);
                    carry = digit / 10;
                }
                if (carry) mantissa.insert(mantissa.begin(), static_cast<char>('0' + carry));
            }
            return value.low && value.high && mantissa == value.low && mantissa == value.high;
        };
        if (!exactly(args[0], 2) || !exactly(args[1], 1)) return 0;
        out->low = out->high = "2";
        out->exponent = 0;
        return 1;
    }
    return 0;
}
unsigned power_canonical_calls=0;
void* probe_canonicalize(std::uint32_t opcode,const void* const* args,std::uint32_t count){
    if(opcode!=4||count!=2||!args)return nullptr;
    ++power_canonical_calls;
    const char *num=nullptr,*den=nullptr;
    if(!qcore_exact_real_rational_parts(args[0],&num,&den)||
       std::string(num)!="8"||std::string(den)!="1")return nullptr;
    if(!qcore_exact_real_rational_parts(args[1],&num,&den)||
       std::string(num)!="1"||std::string(den)!="2")return nullptr;
    void* two=qcore_exact_real_rational("2","1");
    void* root=qcore_exact_real_pow(two,args[1]);
    void* result=qcore_exact_real_mul(two,root);
    release_node(two);
    release_node(root);
    return result;
}
void refinement() {
    qcore_exact_provider_v2 provider{};
    provider.struct_size = sizeof(provider);
    provider.name = "unitprobe";
    provider.spelling = probe_spelling;
    provider.arity = probe_arity;
    provider.refine = probe_refine;
    provider.canonicalize = probe_canonicalize;
    expect(qcore_exact_real_provider_register_v2(&provider) == 1, "provider registers");
    expect(qcore_exact_real_provider_register_v2(&provider) == 1, "provider registers again");
    void* third = qcore_exact_real_node("unitprobe", 1, nullptr, 0);
    double d = 0.0;
    expect(quidra_bigreal_try_float64(third, &d) && d == 1.0 / 3.0, "third as real64");
    float f = 0.0F;
    expect(quidra_bigreal_try_float32(third, &f) && f == 1.0F / 3.0F, "third as real32");
    long long i = 0;
    expect(!quidra_bigreal_try_i64(third, 64, &i), "third is no integer");
    void* wide = qcore_exact_real_node("unitprobe", 2, nullptr, 0);
    for (int run = 0; run < 2; ++run)
        expect(!quidra_bigreal_try_float64(wide, &d), "wide is undecided as real64");
    expect(!quidra_bigreal_try_i64(wide, 64, &i), "wide is undecided as an integer");
    release_node(third);
    release_node(wide);
    void* two = qcore_exact_real_rational("2", "1");
    void* one_atom = qcore_exact_real_node("unitprobe", 3, nullptr, 0);
    void* power = qcore_exact_real_pow(two, one_atom);
    expect(!quidra_bigreal_try_float64(power, &d), "generic power is unproven without hook");
    void* eight=qcore_exact_real_rational("8","1");
    void* half=qcore_exact_real_rational("1","2");
    void* generic_root=qcore_exact_real_pow(eight,half);
    expect(text_of(generic_root)=="√8", "radical keeps generic form without hook");
    release_node(generic_root);
    expect(qcore_exact_real_power_provider_register_v2(nullptr, 4) == 0, "power hook rejects null name");
    expect(qcore_exact_real_power_provider_register_v2("missing", 4) == 0, "power hook rejects unknown provider");
    expect(qcore_exact_real_power_provider_register_v2("unitprobe", 1) == 0, "power hook rejects atom opcode");
    expect(qcore_exact_real_power_provider_register_v2("unitprobe", 4) == 1, "power hook registers");
    expect(qcore_exact_real_power_provider_register_v2("unitprobe", 4) == 1, "power hook registers again");
    expect(qcore_exact_real_power_provider_register_v2("unitprobe", 5) == 0, "power hook rejects conflicting opcode");
    expect(quidra_bigreal_try_float64(power, &d) && d == 2.0, "generic power uses certified hook");
    void* canonical_root=qcore_exact_real_pow(eight,half);
    expect(text_of(canonical_root)=="2√2", "rational radical uses selected canonicalize hook");
    expect(power_canonical_calls==1, "nested power constructor does not re-enter hook");
    release_node(canonical_root);
    void* declined_root=qcore_exact_real_pow(two,half);
    expect(text_of(declined_root)=="√2", "declined canonicalize keeps generic radical");
    release_node(declined_root);
    release_node(eight);
    release_node(half);
    release_node(power);
    release_node(one_atom);
    release_node(two);
}

} // namespace

int main() {
    std::vector<ExactRealValue> values{
        {0, 1}, {1, 1}, {-1, 1}, {2, 1}, {1, 2}, {-1, 2}, {1, 3}, {2, 3}, {-5, 7},
        {22, 7}, {1, 10}, {3, 10}, {1, 1000000007}, {1LL << 31, 1}, {(1LL << 31) + 2, 3},
        {1LL << 62, 1}, {-(1LL << 62), 1}, {(1LL << 62) - 1, 1LL << 61}, {max64, 1},
        {-max64, 1}, {1, max64}, {max64 - 1, max64}, {999999999999999999LL, 1000000000000000000LL}};
    differential(values);
    boundaries();
    conversions();
    rational_inspection();
    rounding();
    refinement();
    if (failures) {
        std::fprintf(stderr, "exact real tests: %d failure(s)\n", failures);
        return 1;
    }
    std::printf("exact real tests passed\n");
    return 0;
}
