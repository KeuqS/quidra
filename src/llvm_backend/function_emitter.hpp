#pragma once

// emit_function: the LLVM text of one typed-IR function, written by
// FunctionEmitter (function_emitter.cpp). The arguments are the module state
// the emitter shares (the ModuleContext, the string pool, the debug metadata:
// null without debug info), its call-depth guard flags, its debug
// subprogram and file ids, and the call-site metadata of a native artifact
// with the function's id in it (null and none otherwise).
//
// FunctionEmitter is local to function_emitter.cpp: with internal linkage,
// the compiler can inline each member function that has a single caller into
// that caller. The module emitter reaches it through this function.

#include "quidra/ir/module.hpp"
#include "llvm_backend/call_site_metadata.hpp"
#include "llvm_backend/debug_module.hpp"
#include "llvm_backend/module_context.hpp"
#include "llvm_backend/string_pool.hpp"

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>

namespace quidra::llvm_backend {

std::string emit_function(const ir::Function& function,
                          const ModuleContext& context,
                          StringPool& pool,
                          bool guard_stack_depth,
                          bool self_depth_recursive,
                          DebugModule* debug_module,
                          std::optional<std::size_t> debug_subprogram,
                          std::size_t debug_file,
                          CallSiteMetadata* call_sites = nullptr,
                          std::optional<std::uint32_t> call_site_function = std::nullopt);

} // namespace quidra::llvm_backend
