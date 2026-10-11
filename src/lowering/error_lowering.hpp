#pragma once

// ErrorLowering: error values: the constructor error(...), the message of an
// error and the reads of its members. Defined in error_lowering.cpp.

#include "ir/function_builder.hpp"
#include "lowering/ir_names.hpp"
#include "quidra/abi/error_record.hpp"

#include <optional>
#include <string>
#include <unordered_map>

namespace quidra::lowering {

class Lowerer;
class LifetimeLowering;
class LocalScope;

// Where an error leaves a call that records a hop: the called function's
// display name and the call's position, and for a call through an `func`
// value the source name of the local or reference that held it.
struct ErrorHopCall {
    std::string name;
    std::uint32_t line{};
    std::uint32_t column{};
    std::string function_value{};
};

class ErrorLowering {
public:
    ErrorLowering(Lowerer& lowerer, const CheckedProgram& checked, ir::FunctionBuilder& builder,
                  LifetimeLowering& lifetime, const LocalScope& scope)
        : lowerer_(lowerer), checked_(checked), builder_(builder), lifetime_(lifetime), scope_(scope) {}

    // The hop of `expression`, when the error of its `T | error` result
    // leaves a call that records one: a direct call of a user function,
    // method or constructor, or an indirect call, in user code. Calls of
    // package, Core and extern functions record none (their errors name the
    // user statement already).
    std::optional<ErrorHopCall> hop_call(const Expr& expression);
    // ErrorHop of the cell `container` (of `container_type`) for `call`: the
    // error, owned, taken out of the cell. A call through an `func` value
    // reads the value again, on the error path only.
    ValueId hop(ValueId container, const Type& container_type, const ErrorHopCall& call,
                abi::ErrorHopKind kind);

    // error(message): a user error made at the call (ErrorMake); its result
    // is owned.
    ValueId lower_constructor(const Expr& e, const CallExpr& n);
    // The message of the error `value` (ErrorMessage, an owned string); an
    // owned `value` is released after it.
    ValueId message_of(ValueId value, bool owned);
    // A member read of an error (e.code, e.message, e.cause, a detail): an
    // owned value of `type`.
    ValueId lower_member(const Expr& e, const MemberExpr& n, const std::string& member,
                         const Type& type);

private:
    Lowerer& lowerer_;
    const CheckedProgram& checked_;
    ir::FunctionBuilder& builder_;
    LifetimeLowering& lifetime_;
    const LocalScope& scope_;
    // The source file of every function and class, by internal name, built
    // at the first hop query.
    std::unordered_map<std::string, std::string> sources_;
    std::unordered_map<std::string, std::string> class_sources_;
    std::unordered_map<std::string, bool> user_files_;
    bool user_file(const std::string& file);
};

} // namespace quidra::lowering
