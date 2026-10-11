#pragma once

// ExpressionLowering: the expression recursion roots and one function per
// kind of expression. Defined in expression_lowering.cpp.

#include "ir/function_builder.hpp"
#include "lowering/check_elision_facts.hpp"
#include "lowering/enclosing_class.hpp"
#include "lowering/initialization_flags.hpp"
#include "lowering/ir_names.hpp"
#include "lowering/local_scope.hpp"
#include "lowering/nesting_depth.hpp"
#include <unordered_map>

namespace quidra::lowering {

class LifetimeLowering;
class ConversionLowering;
class OperatorLowering;
class CallLowering;
class AutogradLowering;
class ErrorLowering;

class ExpressionLowering {
public:
    ExpressionLowering(
        const CheckedProgram& checked, ir::FunctionBuilder& builder,
        LocalScope& scope, CheckElisionFacts& facts,
        NestingDepth& nesting_depth, const EnclosingClass& enclosing_class,
        InitializationFlags& initialization_flags,
        LifetimeLowering& lifetime, ConversionLowering& conversions,
        OperatorLowering& operators, CallLowering& calls,
        AutogradLowering& autograd, ErrorLowering& errors)
        : checked_(checked), builder_(builder), scope_(scope), facts_(facts),
          nesting_depth_(nesting_depth), enclosing_class_(enclosing_class),
          initialization_flags_(initialization_flags),
          lifetime_(lifetime), conversions_(conversions),
          operators_(operators), calls_(calls), autograd_(autograd), errors_(errors) {}

    // the expression recursion roots
    ValueId lower_into(const Expr& expression, const Type& target);
    ValueId lower(const Expr& e);
    ValueId lower_address(const Expr& e, bool may_write = true);
    ValueId lower_at_raw_type(const Expr& e);
    // Lowers `e` now, as lower does, and lets the next lower(e) return that
    // value instead of lowering it again: a plain assignment evaluates its
    // target's subexpressions before its right-hand side and resolves the
    // target afterwards.
    void precompute(const Expr& e);
    std::optional<ValueId> try_scaled_expression(const Expr& e,const Type* cast_target=nullptr);
    void materialize_scaled_real(const std::string& name);
    void capture_loop_operand(const Expr& e) { captured_[&e]=lower_int64(e); }
    void forget_loop_operand(const Expr& e) { captured_.erase(&e); }
    // An integer of any kind as the int64 that an index, a count or another
    // runtime operand takes; an owned temporary is released.
    ValueId lower_int64(const Expr& e);
    // A slice item's operands, left to right as int64 values, with its forms
    // and the direction the checker resolved for the indexing expression e.
    SliceBounds lower_slice_bounds(const Expr& e, const IndexPart& item);
    ValueId lower_string_slice(const Expr& e, const IndexExpr& n, ValueId text, bool text_owned,
                               const Type& text_type);
    // An int64 that a runtime operation produced as a value of the bare
    // integer type `target` (int or nat), known to be inline when
    // `proven_inline` (a declared result range such as a length's).
    ValueId bare_from_int64(ValueId value, const Type& target, bool proven_inline);

private:
    // an expression at its raw type, without the initialization work around
    // it (lower_at_raw_type)
    ValueId lower_kind(const Expr& e);
    // one function per kind of expression, which lower_at_raw_type
    // dispatches to
    ValueId lower_enum_construction(
        const Expr& e, const EnumConstructionInfo& construction);
    ValueId lower_literal(const Expr& e, const IntegerExpr& n);
    ValueId lower_literal(const Expr& e, const RealLiteralExpr& n);
    ValueId lower_literal(const BoolExpr& n);
    ValueId lower_literal(const StringExpr& n);
    ValueId lower_literal_constant(const Expr& e, const LiteralConstantExpr& n);
    ValueId lower_string_template(const StringTemplateExpr& n);
    ValueId lower_name(const Expr& e, const NameExpr& n);
    ValueId lower_member(const Expr& e, const MemberExpr& n);
    ValueId lower_array_literal(const Expr& e, const ArrayExpr& n);
    ValueId lower_array_comprehension(const Expr& e, const ArrayComprehensionExpr& n);
    ValueId lower_index(const Expr& e, const IndexExpr& n);
    ValueId lower_unary(const Expr& e, const UnaryExpr& n);
    ValueId lower_try(const Expr& e, const TryExpr& n);
    ValueId lower_if_expression(const Expr& e, const IfExpr& n);

    const CheckedProgram& checked_;
    ir::FunctionBuilder& builder_;
    LocalScope& scope_;
    CheckElisionFacts& facts_;
    NestingDepth& nesting_depth_;
    const EnclosingClass& enclosing_class_;
    InitializationFlags& initialization_flags_;
    LifetimeLowering& lifetime_;
    ConversionLowering& conversions_;
    OperatorLowering& operators_;
    CallLowering& calls_;
    AutogradLowering& autograd_;
    ErrorLowering& errors_;
    // The values of precompute, each taken by its next lower.
    std::unordered_map<const Expr*, ValueId> precomputed_;
    std::unordered_map<const Expr*, ValueId> captured_;
};

} // namespace quidra::lowering
