#pragma once

// ErrorResultEmitter: recoverable results of the generated program, a
// T | error union box (UnionBox). void_result builds void | error from a
// success flag, string_result string | error from a string that is null on
// failure, output_result the void | error of print and flush from the stream
// status (OUTPUT_WRITE, the site's error record). The error block of the
// first two stores the error that `store_error` makes into the payload slot
// it is given.
//
// Owns no state. Each result gives its IR value its type (SymbolTable) and
// allocates its labels and temporaries from the function's TemporaryNames,
// in an order fixed per helper.

#include "quidra/ir/module.hpp"
#include "llvm_backend/error_value_emitter.hpp"
#include "llvm_backend/symbol_table.hpp"
#include "llvm_backend/temporary_names.hpp"
#include "llvm_backend/union_box.hpp"
#include "llvm_text/llvm_builder.hpp"

#include <cstdint>
#include <functional>
#include <string>

namespace quidra::llvm_backend {

class ErrorResultEmitter {
public:
    // Stores the error of a failed operation into the payload slot it is
    // given.
    using ErrorStore=std::function<void(const std::string& payload)>;

    ErrorResultEmitter(llvm_text::LlvmBuilder& builder,TemporaryNames& names,SymbolTable& symbols,UnionBox& union_box,
                       ErrorRecords& records)
        :builder_(builder),names_(names),symbols_(symbols),union_box_(union_box),records_(records){}

    void void_result(ir::ValueId out_id, const Type& result_type,
                     const std::string& success, const std::string& prefix,
                     const ErrorStore& store_error);

    void string_result(ir::ValueId out_id, const Type& result_type,
                       const std::string& raw, const std::string& prefix,
                       const ErrorStore& store_error);

    // The void | error result of print and flush: `status` is a
    // nonzero i32 when the stream has failed; the site is line:column.
    void output_result(ir::ValueId out_id, const Type& result_type, const std::string& status,
                       std::uint32_t line, std::uint32_t column);

private:
    llvm_text::LlvmBuilder& builder_;
    TemporaryNames& names_;
    SymbolTable& symbols_;
    UnionBox& union_box_;
    ErrorRecords& records_;
};

} // namespace quidra::llvm_backend
