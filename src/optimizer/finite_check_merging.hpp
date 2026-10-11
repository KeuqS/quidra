#pragma once

// FiniteCheckMerging: fewer finite checks of real arithmetic, with the same
// failure reported (docs/spec/architecture.md, the optimizer contract).
//
// The lowering follows every real operation that can produce a non-finite
// value with the FiniteCheck of its result (lowering/finite_checks.hpp).
//
// - Merging, within a block: the check of a value v is removed, and v added
//   to the covered values of a later check, when every use of v is an
//   operand position of one real operation that keeps a non-finite operand
//   non-finite (either operand of +, - and *, the dividend of /) and that
//   operation's result is checked or covered by that later check. Between
//   the first merged check and the check that takes them, only operations
//   that neither fail nor have an effect may stand (constants, local
//   loads, real arithmetic other than ^, widening real conversions, the
//   merged checks), so the first non-finite value in program order, which
//   the check's cold block reports, is the failure the separate checks
//   would have reported first.
// - Loop sinking: a range loop (the for.cond / for.body / for.step /
//   for.end blocks the lowering writes for range(...)) whose blocks hold
//   nothing that fails or has an effect besides one check, of one
//   addition, subtraction or multiplication, and one statement, gets a
//   branch-free flag (FiniteFlagUpdate) in place of that check and one test
//   of the flag at its exit (FiniteFlagCheck), which reports the same
//   operation at the same location. The loop keeps no branch out of its
//   body, so it stays vectorizable. Other loops keep their checks.
//
// OptimizerOptions::keep_every_finite_check turns the pass off
// (tests/lowering_switch_tests.sh compares both builds).

#include "optimizer/pass_context.hpp"

#include "quidra/ir/module.hpp"

namespace quidra::optimizer {

class FiniteCheckMerging {
public:
    static bool enabled(const PassContext& context);
    // True when it removed or moved a check.
    static bool run(ir::Module& module, const PassContext& context);
};

} // namespace quidra::optimizer
