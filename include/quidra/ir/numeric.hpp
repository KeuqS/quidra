#pragma once

// Typed-IR instructions of the numeric domain (scalar arithmetic, comparison and exact-number atoms).
//
// Owns: the domain's instruction structs and their InstructionTraits
// specializations (quidra/ir/domain.hpp). The fields, their order and their
// default member initializers are the IR data model.

#include "quidra/ir/domain.hpp"
#include "quidra/ir/value_id.hpp"
#include "quidra/types.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace quidra::ir {

struct RealLoopCount {
    ValueId out, start, end, step;
    Type type;
    bool descending{}, start_inclusive{true}, end_inclusive{};
    std::uint32_t line{}, column{};
};
struct RealLoopValue { ValueId out, multiplier, start, step; Type type; ValueId native_fma{}; };

struct ExactLoopPlan {
    ValueId out, start, end, step;
    bool descending{}, start_inclusive{true}, end_inclusive{};
    std::uint32_t line{}, column{};
};
struct ExactFromScaled { ValueId out, numerator, denominator; };
struct ExactLoopValue { ValueId out, multiplier, start, step; };
struct ExactScaledCompare { ValueId out, numerator, denominator; std::int64_t constant_n{}, constant_d{1}; std::string op; };
struct ExactScaledConvert { ValueId out, numerator, denominator; Type target; std::uint32_t line{}, column{}; Type result_type{Type::simple(TypeKind::Invalid)}; };

struct ExactAtom {
    ValueId out;
    std::string provider;
    std::uint32_t opcode{};
    Type type;
};
struct ExactUnary {
    ValueId out;
    std::string provider;
    std::uint32_t opcode{};
    ValueId input;
    Type type;
};
// real.op(provider, opcode, inputs...): a provider's operation on exact reals.
struct ExactOp {
    ValueId out;
    std::string provider;
    std::uint32_t opcode{};
    std::vector<ValueId> inputs;
    Type type;
};
// The correctly rounded value of an exact real (`value`) in a fixed-width
// real type, certified by refinement; a value refinement cannot certify
// stops with EXACT_UNPROVEN at line:column. With a slot, the value is a
// contextual constant's, which the entry computes once and stores there.
struct ExactRound {
    ValueId out;
    ValueId value;
    Type type;
    std::string slot;
    std::uint32_t line{};
    std::uint32_t column{};
};
// The value a contextual constant's slot holds.
struct ExactConstant {
    ValueId out;
    std::string slot;
    Type type;
};
// inline_proven (Unary and Binary): the operation is on arbitrary-precision
// integers whose operands and result the lowering proved to be inline words,
// so it needs no tag test and no promotion (check_elision_facts.hpp).
struct Unary {
    ValueId out;
    std::string op;
    ValueId operand;
    Type type;
    std::uint32_t line{};
    std::uint32_t column{};
    bool inline_proven{};
};
struct Binary {
    ValueId out;
    std::string op;
    ValueId left;
    ValueId right;
    Type operand_type;
    Type result_type;
    std::uint32_t line{};
    std::uint32_t column{};
    bool overflow_proven{};
    bool inline_proven{};

    Binary(ValueId out_value, std::string operation, ValueId left_value,
           ValueId right_value, Type operand, Type result,
           std::uint32_t source_line = 0,
           std::uint32_t source_column = 0,
           bool proven_no_overflow = false,
           bool proven_inline = false)
        : out(out_value), op(operation), left(left_value), right(right_value),
          operand_type(operand), result_type(result), line(source_line),
          column(source_column), overflow_proven(proven_no_overflow),
          inline_proven(proven_inline) {}
};

// A complex value of `type` from its real part `re` and imaginary part `im`,
// both of complex_part_type(type). A com value is a managed box that holds
// its own references to both parts.
struct ComplexMake {
    ValueId out;
    ValueId re;
    ValueId im;
    Type type;
};
// The real (part 0) or the imaginary (part 1) part of the complex `value` of
// `type`. A com value's part is borrowed from the box, like a field.
struct ComplexPart {
    ValueId out;
    ValueId value;
    std::uint32_t part{};
    Type type;
};

template <> struct InstructionTraits<RealLoopCount> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<RealLoopValue> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<ExactLoopPlan> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<ExactFromScaled> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<ExactLoopValue> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<ExactScaledCompare> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<ExactScaledConvert> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<ExactAtom> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<ExactUnary> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<ExactOp> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<ExactRound> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<ExactConstant> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<Unary> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<Binary> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<ComplexMake> : InDomain<Domain::numeric> {};
template <> struct InstructionTraits<ComplexPart> : InDomain<Domain::numeric> {};

} // namespace quidra::ir
