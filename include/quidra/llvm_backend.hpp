#pragma once
#include "quidra/call_site_info.hpp"
#include "quidra/ir/module.hpp"
#include <string>

namespace quidra {

// The LLVM text of a module. Without call-site metadata, as the REPL and
// the tools that read the text emit it.
std::string emit_llvm(const ir::Module& module, bool debug_info = false);

// What a module is emitted for.
enum class LlvmArtifact {
    // No native artifact: no call-site metadata (an Interactive compile).
    none,
    // An executable: the call-site metadata and its table
    // (quidra/call_site_info.hpp).
    executable,
    // A library for a C host: the same, and the module references the
    // table's anchor, so a host's link of the archive takes the table.
    library,
};

struct LlvmEmitOptions {
    bool debug_info{};
    LlvmArtifact artifact{LlvmArtifact::executable};
    // Internal native-code identity gate; no public command-line switch.
    bool tail_records{true};
};

struct LlvmEmission {
    std::string text;
    // The module's call sites and functions; empty for LlvmArtifact::none.
    CallSiteInfo call_sites;
};

LlvmEmission emit_native_llvm(const ir::Module& module, const LlvmEmitOptions& options);

} // namespace quidra
