#pragma once

// ir::optimize: the optimizer's pass pipeline over a module (src/optimizer).

#include "quidra/ir/module.hpp"

namespace quidra::ir {

// Internal optimizer switches for tests (tests/lowering_switch_tests.sh).
struct OptimizerOptions {
    // Every finite check of real arithmetic stays where the lowering wrote
    // it: none is merged with another or sunk out of a loop.
    bool keep_every_finite_check{};
};

Module optimize(Module module, OptimizerOptions options = {});

} // namespace quidra::ir
