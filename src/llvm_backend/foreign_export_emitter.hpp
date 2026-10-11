#pragma once

// ForeignExportEmitter: the C entry point of an exported function
// (export "C").
//
// The entry point is a definition under the function's C symbol, its bare
// declared name, with the C signature of its fixed-width scalar parameters
// and result (foreign_abi.hpp: the result carries the callee's extension of
// 8- and 16-bit integers, the parameters none). It registers the module's
// source table, so that a failure inside the function names its file and
// line, calls the function's own symbol (callee_symbol: the user symbol, the
// depth wrapper of a self-depth recursive function), and, when the function
// may leave device work behind (ir/analysis/device_reach.hpp), calls
// quidra_runtime_export_leave before it returns to C. Before the call it
// tests every real32 and real64 argument: a NaN or an infinity from C stops
// the program with NUMERIC_CONVERSION (NON_FINITE, a value), reported at the
// function's declaration (`line`, the line encoded with its file's index in
// the source table, as failure immediates are; 0 for package code). Quidra callers keep
// calling the function's own symbol, so the entry point costs them nothing;
// LLVM inlines the body into it.
//
// In a release build of a native artifact the entry point has an
// artificial subprogram, and its calls are sites of the call-site table
// (call_site_metadata.hpp): its call of the function is a synthesized site,
// so that the walk of a failure inside the inlined body keeps its hops and
// stops at the entry point.
//
// Owns no state. The module writes the entry points after every function
// body, in the module's order, so a module without exports is unchanged.

#include "quidra/ir/module.hpp"
#include "llvm_backend/call_site_metadata.hpp"
#include "llvm_backend/module_context.hpp"

#include <cstdint>
#include <optional>
#include <string>

namespace quidra::llvm_backend {

std::string emit_foreign_export(const ir::Function& function, const std::string& callee_symbol,
                                bool device_reaching, const ModuleContext& context,
                                CallSiteMetadata* call_sites = nullptr,
                                std::optional<std::uint32_t> entry_id = std::nullopt);

} // namespace quidra::llvm_backend
