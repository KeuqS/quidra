#pragma once

// PassContext: what the passes of the optimizer read besides the module they
// rewrite: the rule registry and the function index of that module, and the
// optimizer's switches (ir::OptimizerOptions). The registry and the index
// are built before the first pass and outlive the last one. The rewrites
// change blocks and the region passes each function's regions; no pass
// changes the function list or the extensions, so both stay valid while
// the passes run.

#include "optimizer/function_index.hpp"
#include "optimizer/rule_registry.hpp"
#include "quidra/optimizer.hpp"

namespace quidra::optimizer {

struct PassContext {
    const RuleRegistry& registry;
    const FunctionIndex& functions;
    const ir::OptimizerOptions& options;
};

} // namespace quidra::optimizer
