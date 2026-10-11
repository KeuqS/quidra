#pragma once

// The user call path of a runtime failure (docs/spec/diagnostics.md, "The
// walked path"): the reporter walks the failing thread's stack
// (platform/unwind.hpp) and maps each return address through the image's
// call-site table (quidra/abi/call_site_table.hpp) to the chain of calls it
// is suspended in, inlined calls included. Only user frames print: a frame
// of package code or synthesized code is transparent, and the line of a
// user function called from package code names the user statement that
// called into the package.
//
// - The first frame found in the table is the failing frame: its own site
//   is the failure's statement and prints nothing; a failure raised by the
//   prologue's depth guard skips that frame, so the report names the call.
// - Each later frame prints "F() at <site>" for the function left before
//   it, then a line per user inline level.
// - A call LLVM merged from several calls (an unknown site) names every
//   candidate call of the function that was entered, joined by " or ";
//   with none, or where the walk cannot prove the path (a frame the
//   unwinder cannot step through, a call whose callee is not the function
//   entered, an outlined function), the path carries the marker
//   "… call path incomplete …".
// - The walk ends at the top level, at the C entry point of an export, or
//   at a parallel node trampoline. The captured report adds its node
//   boundary and joining caller path.
//
// The REPL has no table: its failures walk no frame. Nothing here runs
// before a failure, and nothing allocates.

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace quidra::runtime {

enum class PathItemKind : std::uint8_t {
    // "F() at <site>"
    call,
    // "F() at <site> or <site> ...": a merged call's candidates.
    merged,
    // "… call path incomplete …"
    marker,
};

// How a frame was reached (the JSON report's "via").
enum class PathVia : std::uint8_t { call, inline_call };

struct PathItem {
    PathItemKind kind{PathItemKind::call};
    PathVia via{PathVia::call};
    // The function's display name.
    std::string_view function;
    // call: the site's position (the line encoded with its file index);
    unsigned long long line{};
    unsigned long long column{};
    // merged: the candidates, [first, first + count) of path_candidates().
    std::uint32_t first_candidate{};
    std::uint32_t candidate_count{};
    // How many times in a row the walk found the item.
    std::uint64_t repeat{1};
};

struct PathCandidate {
    unsigned long long line{};
    unsigned long long column{};
};

struct CallPath {
    const PathItem* items{};
    std::size_t count{};
    const PathCandidate* candidates{};
    // False where the path carries the marker.
    bool complete{true};
};

// Walks the calling thread's stack once and returns its path (thread-local
// storage, valid until this thread's next walk).
CallPath walk_call_path();

// A node walk ends at this generated body's frame. Only the pointer is
// recorded on entry; its table identity is resolved on the cold walk.
const void* set_node_trace_body(const void* address) noexcept;
class NodeTraceScope {
public:
    explicit NodeTraceScope(const void* address) noexcept : previous_(set_node_trace_body(address)) {}
    ~NodeTraceScope(){set_node_trace_body(previous_);}
    NodeTraceScope(const NodeTraceScope&) = delete;
    NodeTraceScope& operator=(const NodeTraceScope&) = delete;
private:
    const void* previous_{};
};


// The display name of the function whose code starts at `address` (an `func`
// value), from the call-site table; empty when the image has no table or
// the table no such function.
std::string_view function_at(const void* address);

} // namespace quidra::runtime
