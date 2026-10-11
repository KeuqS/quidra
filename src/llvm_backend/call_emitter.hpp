#pragma once

// CallEmitter: function references and calls of a function. A direct call
// names its callee through SymbolResolver (the C symbol of an extern, the
// user symbol, or the .depth body of a self-depth recursive function calling
// itself), passes writable arguments by address and the strings, bins and
// tensors of an extern as borrowed buffers with their lengths (ForeignAbi
// attributes), counts the depth of a self-depth recursive call (failing fast
// beyond the limit) or records the source position before a call into a
// recursive function, tests the real result of an extern function (a value
// C code made: NaN or an infinity stops the program with NONFINITE_RESULT,
// naming the function), and ends in unreachable when the call never
// returns.
// An indirect call goes through a function value; FunctionRef makes one.
//
// Owns no state. The callable functions (a callee's parameters), the extern
// symbols and the recursive functions come from the module's context.

#include "llvm_backend/statement_attribution.hpp"
#include "llvm_backend/call_acceptance_emitter.hpp"
#include "llvm_backend/node_value_ownership.hpp"
#include "quidra/ir/module.hpp"
#include "llvm_backend/string_pool.hpp"
#include "llvm_backend/scratch_planner.hpp"
#include "llvm_backend/symbol_resolver.hpp"
#include "llvm_backend/symbol_table.hpp"
#include "llvm_backend/temporary_names.hpp"
#include "llvm_text/llvm_builder.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace quidra::llvm_backend {

class CallEmitter {
public:
    void node_ownership(NodeValueOwnership* values,CallAcceptanceEmitter* acceptance) {
        node_values_=values;acceptance_=acceptance;
    }
    CallEmitter(const ir::Function& fn,
                const std::unordered_map<std::string,const ir::Function*>& callable_functions,
                const std::unordered_map<std::string,std::string>& external_symbols,
                const std::unordered_set<std::string>& recursive_callees,bool self_depth_recursive,
                llvm_text::LlvmBuilder& builder,SymbolTable& symbols,TemporaryNames& names,
                const SymbolResolver& resolver,const StatementAttribution& sites,StringPool& pool,ScratchPlanner& scratch)
        :fn_(fn),callable_functions_(callable_functions),external_symbols_(external_symbols),
         recursive_callees_(recursive_callees),self_depth_recursive_(self_depth_recursive),builder_(builder),
         symbols_(symbols),names_(names),resolver_(resolver),sites_(sites),pool_(pool),scratch_(scratch){}

    void reserve(const ir::Call& n,const ir::Instruction& ins);
    void reserve(const ir::IndirectCall& n,const ir::Instruction& ins);
    void emit(const ir::FunctionRef& n,const ir::Instruction& ins);
    void emit(const ir::IndirectCall& n,const ir::Instruction& ins);
    void emit(const ir::Call& n,const ir::Instruction& ins);

private:
    NodeValueOwnership* node_values_{};
    CallAcceptanceEmitter* acceptance_{};
    // Fails with NONFINITE_RESULT when `result`, the real result of the
    // extern call `n`, is NaN or an infinity.
    void check_foreign_real(const ir::Call& n,const std::string& result);

    const ir::Function& fn_;
    const std::unordered_map<std::string,const ir::Function*>& callable_functions_;
    const std::unordered_map<std::string,std::string>& external_symbols_;
    const std::unordered_set<std::string>& recursive_callees_;
    bool self_depth_recursive_{};
    llvm_text::LlvmBuilder& builder_;
    SymbolTable& symbols_;
    TemporaryNames& names_;
    const SymbolResolver& resolver_;
    const StatementAttribution& sites_;
    StringPool& pool_;
    ScratchPlanner& scratch_;
};

} // namespace quidra::llvm_backend
