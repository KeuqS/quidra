#pragma once

// Error values in generated code (quidra/abi/error_record.hpp).
//
// ErrorRecords: the error of a Core error site. A site whose details are
// constants has a constant record (StringPool, @.quidra.err.N): its message
// rendered at compile time by abi::render_error, its code and details, and,
// in user code, its origin (the site's line and column). A site whose
// details are constants except a reason has one constant record per reason,
// in an array indexed by the reason. An error block of user code stores the
// record's address as the error; package code copies it at run time
// (quidra_error_from_site), so that its origin is the user statement that
// led into the package.
//
// ErrorValueEmitter: the instructions of the error domain. ErrorMake of a
// user error with a constant text and no cause in user code is a constant
// record; otherwise quidra_error_new makes it; a Core code with a detail
// that is a value of the program is made by quidra_error_make from a slot
// array of the entry frame. ErrorMessage loads the record's message and
// retains it; ErrorCode loads its code (the text "ERROR" for a null one);
// ErrorCause makes an error | none of its cause; ErrorDetail makes a
// string | none (nat | none) of a detail through the runtime, which maps
// the record's schema to the detail's slot. ErrorHop takes the error out of
// the cell a call returned (the payload slot set to null) and records the
// call's site on it (quidra_error_hop, which appends in place to a record
// only this thread holds and copies any other first).
//
// Owns no state beyond the references it is given.

#include "quidra/abi/error_record.hpp"
#include "quidra/ir/module.hpp"
#include "llvm_backend/scratch_planner.hpp"
#include "llvm_backend/statement_attribution.hpp"
#include "llvm_backend/string_pool.hpp"
#include "llvm_backend/symbol_table.hpp"
#include "llvm_backend/union_box.hpp"
#include "llvm_text/llvm_builder.hpp"

#include <cstddef>
#include <cstdint>
#include <span>
#include <string>
#include <string_view>

namespace quidra::llvm_backend {

class ErrorRecords {
public:
    ErrorRecords(llvm_text::LlvmBuilder& builder, StringPool& pool, StatementAttribution& sites)
        : builder_(builder), pool_(pool), sites_(sites) {}

    // The constant record (a global's name) of an error of a Core `code`
    // whose details are `details`, in schema order, made at line:column.
    std::string record(abi::ErrorValueCode code, std::span<const abi::ErrorDetailValue> details,
                       std::uint32_t line, std::uint32_t column);
    // The constant record of a user or package error: `text` the global of
    // its text (its message), `code` its spelling (empty: ERROR).
    std::string user_record(const std::string& text, std::string_view code, std::uint32_t line,
                            std::uint32_t column);
    // The constant array of the records of a Core `code` for each value of
    // `values` in the detail `varying` (its first `count` values), the other
    // details as in `details`.
    std::string record_array(abi::ErrorValueCode code, std::span<const abi::ErrorDetailValue> details,
                             std::size_t varying, std::span<const std::string_view> values,
                             std::size_t count, std::uint32_t line, std::uint32_t column);

    // Stores the error of the site record `record` (an operand holding a
    // record's address) into `payload`: the record itself in user code, a
    // copy whose origin is the user statement in package code (named
    // `base` + ".record").
    void store(const std::string& payload, const std::string& record, const std::string& base);
    // The address of the record of `index` (an i32 operand) in the record
    // array `array` of `code`, named `base` + ".site".
    std::string element(const std::string& array, abi::ErrorValueCode code, const std::string& index,
                        const std::string& base);

    // Stores the NUMERIC_CONVERSION error of a conversion to `type` (a
    // conversion type code, abi::conversion_type_name) of `subject` into
    // `payload`: `reason` is an immediate (one record) or an i32 operand
    // indexing the first `reasons` reasons of the code's list (a record
    // array), named after `payload`.
    void store_conversion(const std::string& payload, int type, abi::ConversionSubject subject,
                          const std::string& reason, std::size_t reasons, std::uint32_t line,
                          std::uint32_t column);

    // The error's value in user code: whether the current statement is user
    // code, and its encoded position (0, 0 in package code).
    bool user_code() const { return sites_.user_code(); }
    unsigned long long line(std::uint32_t line) const { return sites_.line(line); }
    unsigned long long column(std::uint32_t column) const { return sites_.column(column); }

    // The global holding `text` among the texts of error records.
    std::string text(const std::string& text) { return pool_.intern_error_text(text); }
    // The site of a hop (a global's name): the called function's display
    // name, the call's position and the abi::ErrorHopKind.
    std::string hop_site(const std::string& name, std::uint32_t kind, std::uint32_t line,
                         std::uint32_t column) {
        return pool_.intern_hop_site(name, sites_.line(line), sites_.column(column), kind);
    }

private:
    ErrorRecordConstant constant(abi::ErrorValueCode code,
                                 std::span<const abi::ErrorDetailValue> details,
                                 std::uint32_t line, std::uint32_t column);

    llvm_text::LlvmBuilder& builder_;
    StringPool& pool_;
    StatementAttribution& sites_;
};

class ErrorValueEmitter {
public:
    ErrorValueEmitter(StringPool& pool, llvm_text::LlvmBuilder& builder, SymbolTable& symbols,
                      ScratchPlanner& scratch, UnionBox& union_box, ErrorRecords& records)
        : pool_(pool), builder_(builder), symbols_(symbols), scratch_(scratch),
          union_box_(union_box), records_(records) {}

    void reserve(const ir::ErrorMake& n, const ir::Instruction& ins);
    void reserve(const ir::ErrorDetail& n, const ir::Instruction& ins);
    void emit(const ir::ErrorMake& n, const ir::Instruction& ins);
    void emit(const ir::ErrorMessage& n, const ir::Instruction& ins);
    void emit(const ir::ErrorCode& n, const ir::Instruction& ins);
    void emit(const ir::ErrorCause& n, const ir::Instruction& ins);
    void emit(const ir::ErrorDetail& n, const ir::Instruction& ins);
    void emit(const ir::ErrorHop& n, const ir::Instruction& ins);

private:
    void emit_user(const ir::ErrorMake& n);
    void store_optional(const std::string& out, const Type& type, const Type& present_type,
                        const std::string& value, llvm_text::LlvmType value_type,
                        const std::string& absent);
    void emit_core(const ir::ErrorMake& n, const ir::Instruction& ins);

    StringPool& pool_;
    llvm_text::LlvmBuilder& builder_;
    SymbolTable& symbols_;
    ScratchPlanner& scratch_;
    UnionBox& union_box_;
    ErrorRecords& records_;
};

} // namespace quidra::llvm_backend
