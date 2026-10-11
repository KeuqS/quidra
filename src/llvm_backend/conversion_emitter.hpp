#pragma once

// ConversionEmitter: the instructions that convert a value to another type.
// NumericConvert casts between scalar types, with a range check that fails
// fast when the conversion is checked; FallibleNumericConvert gives a
// T | error union box instead, also from big integers and big reals;
// ArrayNumericCast converts an array element by element through the
// module's array cast helpers; ParseNumber, ParseNumberDirect and ParseBin
// parse text; BinConvert converts a bin; ToString and FormatNumber produce
// text.
//
// Both numeric conversions check their range with the same two functions
// (add_integer_range_checks, float32_range_check): an integer converted
// to a narrower or differently signed integer type, and a float narrowed
// to float32, are checked by i1 conditions, which FallibleNumericConvert
// turns into its error case and a checked NumericConvert into a
// fail-fast guard (FailFastEmitter), each through their disjunction
// (any_check). A failure names its destination type, its subject (a value,
// an array element) and its reason (abi::ConversionReason): an immediate
// where one cause is possible; for a real narrowed to real32, ±infinity
// (NON_FINITE) told from a finite value (OUT_OF_RANGE) inside the failure
// block; for an exact real, the reason the runtime's declined
// try-conversion recorded. The failure blocks name their values after a
// name or label allocated before, so the function's other names keep their
// numbers.
//
// Owns no state. The parse results and the exact-number conversions write
// through the entry-frame scratch slots the function's pre-pass reserved:
// one per parse instruction, and the slots shared by every fallible
// conversion from an exact number, which the first one that needs them
// reserved. Their labels and temporaries come from TemporaryNames in a
// fixed order per conversion.

#include "llvm_backend/statement_attribution.hpp"
#include "quidra/ir/module.hpp"
#include "llvm_backend/error_value_emitter.hpp"
#include "llvm_backend/fail_fast_emitter.hpp"
#include "llvm_backend/scratch_planner.hpp"
#include "llvm_backend/symbol_table.hpp"
#include "llvm_backend/temporary_names.hpp"
#include "llvm_backend/union_box.hpp"
#include "llvm_text/llvm_builder.hpp"

#include <string>
#include <vector>

namespace quidra::llvm_backend {

class ConversionEmitter {
public:
    ConversionEmitter(llvm_text::LlvmBuilder& builder,SymbolTable& symbols,ScratchPlanner& scratch,TemporaryNames& names,
                      UnionBox& union_box,FailFastEmitter& fail_fast,const StatementAttribution& sites,
                      ErrorRecords& records)
        :builder_(builder),symbols_(symbols),scratch_(scratch),names_(names),union_box_(union_box),
         fail_fast_(fail_fast),sites_(sites),records_(records){}

    // Before any text of the function is written (FunctionPrepass): what
    // the instruction needs reserved.
    void reserve(const ir::NumericConvert& n,const ir::Instruction& ins);
    void reserve(const ir::FallibleNumericConvert& n,const ir::Instruction& ins);
    void reserve(const ir::ParseNumber& n,const ir::Instruction& ins);
    void reserve(const ir::ParseNumberDirect& n,const ir::Instruction& ins);

    void emit(const ir::ArrayNumericCast& n,const ir::Instruction& ins);
    void emit(const ir::FallibleNumericConvert& n,const ir::Instruction& ins);
    void emit(const ir::NumericConvert& n,const ir::Instruction& ins);
    void emit(const ir::ParseBin& n,const ir::Instruction& ins);
    void emit(const ir::BinConvert& n,const ir::Instruction& ins);
    void emit(const ir::ParseNumber& n,const ir::Instruction& ins);
    void emit(const ir::ParseNumberDirect& n,const ir::Instruction& ins);
    void emit(const ir::ToString& n,const ir::Instruction& ins);
    void emit(const ir::FormatNumber& n,const ir::Instruction& ins);

private:
    // Appends the conditions under which value (of the integer type source)
    // is outside the range of the integer type target: negative for an
    // unsigned target, above its maximum, below its minimum.
    void add_integer_range_checks(std::vector<std::string>& checks,const Type& source,const Type& target,
                                  const std::string& value);
    // The condition under which the float value is finite and outside the
    // range of float32.
    std::string float32_range_check(const std::string& value);
    // The 16-bit reals' conversions go through binary64, which holds every
    // value of every fixed-width real exactly: the source widened
    // exactly (an integer to binary64: exact up to 2^53, and a 64-bit
    // integer into real16b is rounded by the runtime from the integer),
    // range-checked against the destination where the policy asks, then
    // rounded once to the destination.
    std::string widen_to_double(const std::string& value,const Type& type);
    std::string narrow_from_double(const std::string& value,const Type& type);
    // The i1 that holds when binary64 `value` rounds beyond the finite range
    // of the fixed-width real `type`.
    std::string real_range_check(const std::string& value,const Type& type);
    // The 16-bit conversion of `n` into `out` (its checks in `checks`, or
    // through a fail-fast guard when `fail_fast`); `exact_ok` receives the i1
    // of an exact source's try-conversion, when there is one.
    void emit_half_conversion(const Type& source,const Type& target,const std::string& value,
                              const std::string& out,bool checked,std::vector<std::string>& checks,
                              std::string& exact_ok,bool fallible);
    // The conversion of `value` (of `source`) into the complex `target`:
    // for a com target the converted value; otherwise the i1 of the
    // runtime's success, the parts written to `slot` ([2 x double]).
    std::string emit_complex_conversion(const Type& source,const Type& target,const std::string& value,
                                        const std::string& slot);
    // The disjunction of one or more checks, joined left to right by or.
    std::string any_check(const std::vector<std::string>& checks);
    // In a failure block: the reason (an i32 operand) a real64 value fails
    // its narrowing to real32, NON_FINITE for ±infinity, else OUT_OF_RANGE;
    // its values are named after `base`.
    std::string float32_failure_reason(const std::string& value,const std::string& base);
    // In an error block: the reason the runtime recorded for the declined
    // try-conversion, named after `base`.
    std::string recorded_failure_reason(const std::string& base);
    // In the error block of an exact real converted to bigint: NOT_INTEGRAL
    // for a small rational (which the conversion declines inline), else the
    // recorded reason; named after `base`.
    std::string fraction_or_recorded_reason(const std::string& value,const std::string& base);
    // In an error block: stores the NUMERIC_PARSE error of a parse of `target`
    // for `reason` (an immediate, or an i32 operand among the first `reasons`
    // reasons) into `payload`, at line:column.
    void store_parse_error(const std::string& payload,const Type& target,const std::string& reason,
                           std::size_t reasons,std::uint32_t line,std::uint32_t column);
    // In an error block: stores the error of a conversion to `target` (a
    // conversion type code) of `subject` for `reason` (an immediate, or an
    // operand among the first `reasons` reasons) into `payload`, the error
    // payload slot (ErrorRecords::store_conversion), at line:column.
    void store_conversion_error(const std::string& payload,int target,abi::ConversionSubject subject,
                                const std::string& reason,std::size_t reasons,std::uint32_t line,
                                std::uint32_t column);

    llvm_text::LlvmBuilder& builder_;
    SymbolTable& symbols_;
    ScratchPlanner& scratch_;
    TemporaryNames& names_;
    UnionBox& union_box_;
    FailFastEmitter& fail_fast_;
    const StatementAttribution& sites_;
    ErrorRecords& records_;
};

} // namespace quidra::llvm_backend
