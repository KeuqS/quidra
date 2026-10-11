#pragma once

// RandomEmitter: random generators of a function: a generator
// ($std.random.Generator) is an 8-byte state holding its seed; integers in
// a range (which fails fast unless start < end), floats and bools are drawn
// through the runtime.
//
// Owns no state.

#include "quidra/ir/module.hpp"
#include "llvm_backend/symbol_table.hpp"
#include "llvm_text/llvm_builder.hpp"

namespace quidra::llvm_backend {

class RandomEmitter {
public:
    RandomEmitter(llvm_text::LlvmBuilder& builder,SymbolTable& symbols)
        :builder_(builder),symbols_(symbols){}

    void emit(const ir::RandomGenerator& n,const ir::Instruction& ins);
    void emit(const ir::RandomInt& n,const ir::Instruction& ins);
    void emit(const ir::RandomFloat& n,const ir::Instruction& ins);
    void emit(const ir::RandomBool& n,const ir::Instruction& ins);

private:
    llvm_text::LlvmBuilder& builder_;
    SymbolTable& symbols_;
};

} // namespace quidra::llvm_backend
