#pragma once

// CallSiteInfo: what the backend knows about the calls and functions of a
// module it emits for a native artifact, beside the LLVM text
// (docs/spec/architecture.md, "The call path of plain code").
//
// Every call instruction of a function that has a debug subprogram carries
// a site id (the line of its DILocation in release builds, the
// discriminator of its scope in --debug builds), an index into `sites`.
// Every function with a subprogram has a function id, an index into
// `functions`. After LLVM has compiled the module, the driver reads the
// object's line table and inline tree (toolchain/call_site_table.hpp) and
// links a table that maps each machine return address to the chain of site
// ids of the calls it is suspended in; the runtime reads those sites and
// functions when a failure walks the stack.
//
// Std-only: the backend fills it, the toolchain writes it into the table
// module.

#include <cstdint>
#include <string>
#include <vector>

namespace quidra {

// What a call site calls.
enum class CallSiteCallee : std::uint8_t {
    // Site 0: a row LLVM merged from several calls (line 0).
    unknown = 0,
    // A function of the module (`callee` is its function id).
    function = 1,
    // A call through an `func` value.
    indirect = 2,
    // A runtime entry, a prelude helper, an LLVM intrinsic or a C library
    // function.
    runtime = 3,
    // An extern C function (`extern_callback` when it is given an `func`).
    extern_function = 4,
};

namespace call_site_flags {
// The site's statement is user code (docs/spec/architecture.md, "User code
// and package code").
inline constexpr std::uint8_t user = 1;
// The prologue's call depth guard (quidra_stack_enter): a failure there is
// reported at the call that entered the function.
inline constexpr std::uint8_t prologue = 2;
// A synthesized call: the C entry point's call of its exported function.
inline constexpr std::uint8_t synthesized = 4;
// An extern C function given an `func` argument, which may call user code.
inline constexpr std::uint8_t extern_callback = 8;
// A potential tail call; the subset that needs a runtime record, and a self
// call whose record's depth counts its logical repetitions.
inline constexpr std::uint8_t tail = 16;
inline constexpr std::uint8_t recorded_tail = 32;
inline constexpr std::uint8_t self_tail = 64;
// A runtime record helper; the table step detects one in a cold fragment.
inline constexpr std::uint8_t tail_record_helper = 128;
} // namespace call_site_flags

struct CallSite {
    // The user file's index in the module's source table and the position
    // (one-based line and byte column); 0 where the site has none (package
    // code, synthesized calls).
    std::uint32_t file{};
    std::uint32_t line{};
    std::uint32_t column{};
    // The function id of a CallSiteCallee::function call.
    std::uint32_t callee{};
    // The function the call is written in.
    std::uint32_t owner{};
    CallSiteCallee callee_kind{CallSiteCallee::unknown};
    std::uint8_t flags{};
};

enum class CallSiteFunctionKind : std::uint8_t {
    // A function of a user file.
    user = 0,
    // A function of package code (an installed package, the files it
    // imports, the standard library's declarations).
    package = 1,
    // A function the compiler made: the C entry point of an export.
    synthesized = 2,
    // The program's top-level code ($entry).
    entry = 3,
};

namespace call_site_function_flags {
// The function's address is taken (it can be called through an `func`).
inline constexpr std::uint8_t address_taken = 1;
// The C entry point of an exported function: the walk stops there.
inline constexpr std::uint8_t export_entry = 2;
// The function counts its self recursion in a depth parameter
// (SelfDepthGuard): its `.depth` symbol is its body.
inline constexpr std::uint8_t self_depth = 4;
// Normal returns of this function end a recorded self run.
inline constexpr std::uint8_t self_tail = 8;
// A cold fragment touched this function's log at a different CFA.
inline constexpr std::uint8_t tail_unusable = 16;
// A compiler-generated shape wrapper. Its one synthesized function call
// forwards to the checked body, even if LLVM erases the wrapper's inline
// location when it merges callers. This does not authorize user tail calls.
inline constexpr std::uint8_t transparent_forwarder = 32;
} // namespace call_site_function_flags

struct CallSiteFunction {
    // The name a trace line prints (`pick()`, `Point.norm()`, `Point()`).
    std::string display;
    // Its LLVM symbols, without '@': the definition's, and for a
    // self-depth function the public wrapper's first.
    std::vector<std::string> symbols;
    CallSiteFunctionKind kind{CallSiteFunctionKind::user};
    std::uint8_t flags{};
};

struct CallSiteInfo {
    // Index 0 is the unknown site of merged calls.
    std::vector<CallSite> sites{CallSite{}};
    std::vector<CallSiteFunction> functions;
    // A library build: the table defines the anchor the module references.
    bool library{};
    // The module was emitted with --debug metadata: site ids are the
    // discriminators of the call locations.
    bool debug{};

    bool empty() const { return functions.empty(); }
};

} // namespace quidra
