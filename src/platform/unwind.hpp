#pragma once

// The frames of the calling thread's stack, walked with the unwind tables
// the compiler emits (no frame pointers needed): _Unwind_Backtrace with
// _Unwind_GetCFA on macOS and Linux (libunwind, libgcc), and a loop of
// RtlLookupFunctionEntry and RtlVirtualUnwind from RtlCaptureContext on
// Windows. Each frame gives the address it continues at and its canonical
// frame address (the stack pointer before the call that entered it).
//
// Only the failure path walks: nothing is recorded while the program runs.
// The walk pops nothing and runs no cleanup; it allocates nothing.

#include <cstdint>

namespace quidra::platform {

struct StackFrame {
    // The address the frame continues at (a return address, except where
    // `ip_before_instruction`: an interrupted frame's own instruction).
    std::uintptr_t ip{};
    // Zero when the final context cannot establish its entry stack pointer.
    std::uintptr_t cfa{};
    bool ip_before_instruction{};
};

enum class StackWalkEnd {
    // The walk reached the end of the stack, or `visit` stopped it.
    complete,
    // The unwinder could not step through a frame (no unwind information).
    incomplete,
    // The walk could not start.
    unavailable,
};

// Calls `visit` with every frame from the caller of walk_stack outward,
// until it returns false.
StackWalkEnd walk_stack(bool (*visit)(const StackFrame& frame, void* context), void* context);

} // namespace quidra::platform
