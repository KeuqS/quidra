#pragma once

// Complex literals in the lowering. A literal the checker typed as a
// complex type is a value of that type: a real (or, in an explicit
// conversion, integer) literal is its real part, an imaginary literal its
// imaginary part, the other part zero. A real and an imaginary literal
// joined by + or - (either may be negated) are one constant value, its parts
// taken from the literals with their signs, so `1.0 - 0.0i` keeps the -0.0 an
// operation 0.0 - 0.0 would lose. Any other complex literal expression is
// computed by complex arithmetic from such values.

#include "ir/function_builder.hpp"
#include "quidra/ast.hpp"
#include "quidra/ir/constant.hpp"
#include "quidra/ir/lifetime.hpp"
#include "quidra/ir/numeric.hpp"
#include "quidra/types.hpp"

#include <cstdlib>
#include <optional>
#include <string>

namespace quidra::lowering {

// One part of a complex literal: the literal (null for zero) and its sign.
struct ComplexLiteralPart {
    const Expr* literal{};
    bool negative{};
};

struct ComplexLiteralParts {
    ComplexLiteralPart re;
    ComplexLiteralPart im;
};

namespace complex_literals_detail {

// A literal term: a real, integer or imaginary literal, or one negated. Sets
// `imaginary` for an imaginary literal.
inline std::optional<ComplexLiteralPart> term(const Expr& e, bool& imaginary) {
    bool negative = false;
    const Expr* current = &e;
    if (const auto* unary = std::get_if<UnaryExpr>(&current->data); unary && unary->op == "-") {
        negative = true;
        current = unary->operand.get();
    }
    if (std::holds_alternative<ImaginaryLiteralExpr>(current->data)) {
        imaginary = true;
        return ComplexLiteralPart{current, negative};
    }
    if (std::holds_alternative<RealLiteralExpr>(current->data) ||
        std::holds_alternative<IntegerExpr>(current->data)) {
        imaginary = false;
        return ComplexLiteralPart{current, negative};
    }
    return std::nullopt;
}

} // namespace complex_literals_detail

// The parts of `e` when it is a literal term or a real and an imaginary term
// joined by + or -; nothing otherwise.
inline std::optional<ComplexLiteralParts> complex_literal_parts(const Expr& e) {
    using complex_literals_detail::term;
    bool imaginary = false;
    if (const auto single = term(e, imaginary)) {
        ComplexLiteralParts parts;
        (imaginary ? parts.im : parts.re) = *single;
        return parts;
    }
    const auto* binary = std::get_if<BinaryExpr>(&e.data);
    if (!binary || (binary->op != "+" && binary->op != "-")) return std::nullopt;
    bool left_imaginary = false;
    bool right_imaginary = false;
    const auto left = term(*binary->left, left_imaginary);
    auto right = term(*binary->right, right_imaginary);
    if (!left || !right || left_imaginary == right_imaginary) return std::nullopt;
    if (binary->op == "-") right->negative = !right->negative;
    ComplexLiteralParts parts;
    (left_imaginary ? parts.im : parts.re) = *left;
    (right_imaginary ? parts.im : parts.re) = *right;
    return parts;
}

namespace complex_literals_detail {

inline std::string spelling_of(const Expr& literal) {
    if (const auto* real = std::get_if<RealLiteralExpr>(&literal.data)) return real->spelling;
    if (const auto* integer = std::get_if<IntegerExpr>(&literal.data))
        return integer->spelling.empty() ? std::to_string(integer->value) : integer->spelling;
    return std::get<ImaginaryLiteralExpr>(literal.data).spelling;
}

// The value of one part, of the real type `part`.
inline ir::ValueId part_value(ir::FunctionBuilder& builder, const ComplexLiteralPart& literal,
                              const Type& part) {
    const auto out = builder.fresh();
    const std::string spelling = literal.literal ? spelling_of(*literal.literal) : "0.0";
    // The literal's value, then its negation as a negated literal computes
    // it (so -0.0 keeps its sign).
    if (part.kind == TypeKind::Real)
        builder.emit(ir::ConstantExact{out, spelling, part});
    else
        builder.emit(ir::ConstantFloat{out, std::strtod(spelling.c_str(), nullptr), part, spelling});
    if (!literal.negative) return out;
    const auto negated = builder.fresh();
    builder.emit(ir::Unary{negated, "-", out, part});
    if (part.kind == TypeKind::Real) builder.emit(ir::Release{out, part});
    return negated;
}

} // namespace complex_literals_detail

// The constant complex value of `parts`, of type `complex`.
inline ir::ValueId emit_complex_literal(ir::FunctionBuilder& builder,
                                        const ComplexLiteralParts& parts, const Type& complex) {
    using complex_literals_detail::part_value;
    const auto part = complex_part_type(complex);
    const auto re = part_value(builder, parts.re, part);
    const auto im = part_value(builder, parts.im, part);
    const auto out = builder.fresh();
    builder.emit(ir::ComplexMake{out, re, im, complex});
    if (part.kind == TypeKind::Real) {
        // The box holds its own references to the parts.
        builder.emit(ir::Release{re, part});
        builder.emit(ir::Release{im, part});
    }
    return out;
}

} // namespace quidra::lowering
