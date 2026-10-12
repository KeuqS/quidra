#pragma once

// Entries of runtime.cpp that other runtime sources use internally (never
// generated code): managed allocations with a drop set when they are made,
// the release that hands back an allocation instead of finalizing it (the
// iterative release of an error's cause chain, runtime_error.cpp), and the
// copy of a text into a managed string; and the error records of the
// runtime's own failures (JSON, HTTP).

#include "quidra/abi/error_record.hpp"

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace quidra::runtime {

// A managed allocation without an interior range whose drop is `drop` from
// the start: a release with a null drop argument keeps it.
void* managed_allocate_with_drop(std::size_t bytes, void (*drop)(void*));

// An allocation unregistered by managed_release_take, its drop not run.
struct TakenAllocation {
    void* base{};
    unsigned char small_pool_class{};
};

// Releases one owner of `value` like quidra_managed_release, but at zero
// owners and pins unregisters the allocation and returns true with it in
// `taken` instead of running its drop; false otherwise (owners left, or not
// a managed allocation of this thread).
bool managed_release_take(void* value, TakenAllocation& taken);
// Gives the memory of a taken allocation back.
void recycle_taken(const TakenAllocation& taken);

// Whether `value` is a managed allocation of the calling thread, and its
// owner count (0 when it is not one).
bool is_managed(const void* value);
std::size_t managed_owners(const void* value);

// A fatal exit does not unwind the active Quidra frames. Keep their allocation
// context valid through the C host's exit callbacks, until process termination.
// This does not allocate, run drops or change normal thread teardown.
void preserve_managed_state_for_exit();

// A new managed string holding `text` (valid UTF-8 without NUL).
char* managed_text_copy(std::string_view text);

// An error record of a Core code (runtime_error.cpp) with `slots` in
// schema order, its message rendered from them: text details are retained
// when `retain_texts`, else the record takes the references the caller
// holds. The origin is the site's position (0, 0: the user statement).
void* make_error_record(abi::ErrorValueCode code, const std::uint64_t* slots,
                        unsigned long long line, unsigned long long column, bool retain_texts);

} // namespace quidra::runtime
