#pragma once

// Defined in concurrency_lowering.cpp.

#include "ir/function_builder.hpp"
#include "lowering/ir_names.hpp"
#include <optional>

namespace quidra::lowering {

class Lowerer;
class LifetimeLowering;

class ConcurrencyLowering {
public:
    ConcurrencyLowering(
        Lowerer& lowerer, const CheckedProgram& checked,
        ir::FunctionBuilder& builder, LifetimeLowering& lifetime)
        : lowerer_(lowerer), checked_(checked), builder_(builder),
          lifetime_(lifetime) {}

    void lower_parallel(const Stmt& statement,const ParallelStmt& block);
    void lower_parallel_for(const ForStmt& loop);

private:
    Lowerer& lowerer_;
    const CheckedProgram& checked_;
    ir::FunctionBuilder& builder_;
    LifetimeLowering& lifetime_;
};

} // namespace quidra::lowering
