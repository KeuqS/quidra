#pragma once

// Emits the checked parallel node table, captured storage and joined result.

#include "llvm_backend/statement_attribution.hpp"
#include "llvm_backend/scratch_planner.hpp"
#include "llvm_backend/union_box.hpp"
#include "quidra/ir/module.hpp"
#include "llvm_backend/symbol_table.hpp"
#include "llvm_backend/temporary_names.hpp"
#include "llvm_text/llvm_builder.hpp"

namespace quidra::llvm_backend {

class ConcurrencyEmitter {
public:
    ConcurrencyEmitter(llvm_text::LlvmBuilder& builder,SymbolTable& symbols,TemporaryNames& names,const StatementAttribution& sites,ScratchPlanner& scratch,UnionBox& boxes)
        :builder_(builder),symbols_(symbols),names_(names),sites_(sites),scratch_(scratch),boxes_(boxes){}

    void reserve(const ir::ParallelBlock& n,const ir::Instruction& ins);
    void emit(const ir::ParallelBlock& n,const ir::Instruction& ins);

private:
    llvm_text::LlvmBuilder& builder_;
    SymbolTable& symbols_;
    TemporaryNames& names_;
    const StatementAttribution& sites_;
    ScratchPlanner& scratch_;
    UnionBox& boxes_;
};

} // namespace quidra::llvm_backend
