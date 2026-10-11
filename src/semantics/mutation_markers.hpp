#pragma once

// Mutation markers (L1, L7): every change of existing state is visible at
// the call site, as a `&` argument or as the marker `.` (mutation_markers.cpp).
//
// The rules, over the effect summaries of a checked program:
//   - a function, method or constructor whose summary changes existing state
//     that no `&` parameter exposes (receiver fields, shared state reachable
//     from its receiver or a by-value parameter, runtime state) is declared
//     with the marker, `void .update()`, `.construct(...)`; a declaration
//     that changes nothing may still carry it, as a promise; an extern's
//     marker is its declaration, which the compiler trusts;
//   - a call of a `.` callee (a function, method or constructor declared
//     with the marker, or a method of a built-in type that changes existing
//     state) is written with the marker before its postfix chain, and a
//     marker covers the calls of its chain only, never a chain without a `.`
//     callee;
//   - a `.` function never becomes an fn value;
//   - a field default and a parameter default change no existing state.
//
// Owns: check_mutation_markers, which the checker runs after the effect
// summaries.

#include "quidra/checker.hpp"
#include "quidra/diagnostic.hpp"

#include <vector>

namespace quidra::semantics {

// The MUTATION_MARKER and FUNCTION_REFERENCE_SIGNATURE diagnostics of
// `checked`, in source order, each once. `checked.effects` must be set.
std::vector<Diagnostic> check_mutation_markers(const CheckedProgram& checked);

} // namespace quidra::semantics
