#pragma once

// CheckEmitter: the run-time checks of a function: the rank and the known
// extents of a shaped tensor (through the runtime), the equality of two
// extents and the nonzero step of a range (failing fast with the shape or
// range-step diagnostic), the array of a reference loop over a reference
// binding (failing fast with FOR_ITERATION, its code and message interned
// from quidra/abi/runtime_failure.hpp where the check occurs), the flag of a
// read that may be uninitialized (failing fast with UNINITIALIZED, its
// message naming the storage, from the same table), the finite checks of
// real arithmetic (one test per primary value on the hot path; the cold
// block finds the first non-finite value in program order and reports it
// through quidra_runtime_real_fail, finite_check_support.hpp), and the
// user's test assertions.
//
// Owns no state. The extent and iteration checks allocate their labels
// through FailFastEmitter; the range-step check names its labels after the
// step's IR value, so it allocates no name.

#include "llvm_backend/statement_attribution.hpp"
#include "quidra/ir/module.hpp"
#include "llvm_backend/fail_fast_emitter.hpp"
#include "llvm_backend/string_pool.hpp"
#include "llvm_backend/symbol_table.hpp"
#include "llvm_backend/temporary_names.hpp"
#include "llvm_text/llvm_builder.hpp"

namespace quidra::llvm_backend {

class CheckEmitter {
public:
    CheckEmitter(StringPool& pool,llvm_text::LlvmBuilder& builder,const SymbolTable& symbols,
                 TemporaryNames& names,FailFastEmitter& fail_fast,const StatementAttribution& sites)
        :pool_(pool),builder_(builder),symbols_(symbols),names_(names),fail_fast_(fail_fast),sites_(sites){}

    void emit(const ir::ShapedConstraintCheck& n,const ir::Instruction& ins);
    void emit(const ir::ExtentEqualCheck& n,const ir::Instruction& ins);
    void emit(const ir::TestAssert& n,const ir::Instruction& ins);
    void emit(const ir::ForStepCheck& n,const ir::Instruction& ins);
    void emit(const ir::IterationShapeCheck& n,const ir::Instruction& ins);
    void emit(const ir::TraversalSiteCheck& n,const ir::Instruction& ins);
    void emit(const ir::InitializedCheck& n,const ir::Instruction& ins);
    void emit(const ir::ReferenceBoundCheck& n,const ir::Instruction& ins);
    void emit(const ir::SelfReferenceCheck& n,const ir::Instruction& ins);
    void emit(const ir::StoredTargetsCheck& n,const ir::Instruction& ins);
    void emit(const ir::FiniteCheck& n,const ir::Instruction& ins);
    void emit(const ir::FiniteFlagUpdate& n,const ir::Instruction& ins);
    void emit(const ir::FiniteFlagCheck& n,const ir::Instruction& ins);

private:
    // The i1 that is true when `value` (of real type `type`) is NaN or an
    // infinity.
    std::string non_finite(const ir::CheckedReal& value);
    // Reports `value`'s failure (REAL_OVERFLOW, or DIVISION_BY_ZERO for a
    // division by zero, decided from its divisor) and ends the block.
    void report(const ir::CheckedReal& value);

    StringPool& pool_;
    llvm_text::LlvmBuilder& builder_;
    const SymbolTable& symbols_;
    TemporaryNames& names_;
    FailFastEmitter& fail_fast_;
    const StatementAttribution& sites_;
};

} // namespace quidra::llvm_backend
