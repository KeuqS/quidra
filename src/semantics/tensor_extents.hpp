#pragma once

#include "quidra/checker.hpp"

namespace quidra::semantics {

// Enrich checked tensor values with function-local symbolic extent facts
// and summarize each result in terms of the callee's parameter axes.
void summarize_tensor_extents(CheckedProgram& checked);

} // namespace quidra::semantics
