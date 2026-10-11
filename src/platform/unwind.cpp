#include "platform/unwind.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <unwind.h>
#endif

namespace quidra::platform {

#ifdef _WIN32

StackWalkEnd walk_stack(bool (*visit)(const StackFrame& frame, void* context), void* context) {
    CONTEXT state{};
    RtlCaptureContext(&state);
    bool first = true;
    for (int depth = 0; depth < 1 << 20; ++depth) {
#if defined(_M_ARM64)
        const DWORD64 ip = state.Pc;
#else
        const DWORD64 ip = state.Rip;
#endif
        if (ip == 0) return StackWalkEnd::complete;
        DWORD64 image = 0;
        const auto* function = RtlLookupFunctionEntry(ip, &image, nullptr);
        if (function) {
            void* handler_data = nullptr;
            DWORD64 establisher = 0;
            RtlVirtualUnwind(UNW_FLAG_NHANDLER, image, ip, const_cast<PRUNTIME_FUNCTION>(function),
                             &state, &handler_data, &establisher, nullptr);
        } else {
            // A leaf function: the return address is at the stack pointer.
#if defined(_M_ARM64)
            state.Pc = state.Lr;
#else
            state.Rip = *reinterpret_cast<const DWORD64*>(state.Rsp);
            state.Rsp += 8;
#endif
        }
        if (first) {
            // The frame of walk_stack itself.
            first = false;
            continue;
        }
#if defined(_M_ARM64)
        const StackFrame frame{static_cast<std::uintptr_t>(ip), static_cast<std::uintptr_t>(state.Sp),
                               false};
#else
        const StackFrame frame{static_cast<std::uintptr_t>(ip),
                               static_cast<std::uintptr_t>(state.Rsp), false};
#endif
        if (frame.ip == 0) return StackWalkEnd::complete;
        if (!visit(frame, context)) return StackWalkEnd::complete;
    }
    return StackWalkEnd::incomplete;
}

#else

namespace {

struct Walk {
    bool (*visit)(const StackFrame&, void*);
    void* context;
    bool skipped_self{};
    bool stopped{};
    StackFrame pending{};
    bool has_pending{};
};

_Unwind_Reason_Code step(struct _Unwind_Context* unwind, void* argument) {
    auto& walk = *static_cast<Walk*>(argument);
    if (!walk.skipped_self) {
        // The frame of walk_stack itself.
        walk.skipped_self = true;
        return _URC_NO_REASON;
    }
    int before = 0;
    StackFrame frame;
    frame.ip = static_cast<std::uintptr_t>(_Unwind_GetIPInfo(unwind, &before));
    frame.cfa = static_cast<std::uintptr_t>(_Unwind_GetCFA(unwind));
    frame.ip_before_instruction = before != 0;
    // The context exposes the stack pointer restored by the inner frame.
    // The next context supplies this activation's canonical entry CFA.
    if (walk.has_pending) {
        walk.pending.cfa = frame.cfa;
        if (!walk.visit(walk.pending, walk.context)) {
            walk.stopped = true;
            return _URC_END_OF_STACK;
        }
    }
    walk.pending = frame;
    walk.has_pending = frame.ip != 0;
    return frame.ip ? _URC_NO_REASON : _URC_END_OF_STACK;
}

} // namespace

StackWalkEnd walk_stack(bool (*visit)(const StackFrame& frame, void* context), void* context) {
    Walk walk{visit, context};
    const auto result = _Unwind_Backtrace(step, &walk);
    // Retain the last frame even if its caller is not unwindable.
    // The recovery layer must prove its path without a CFA.
    if (!walk.stopped && walk.has_pending) {
        walk.pending.cfa = 0;
        walk.stopped = !walk.visit(walk.pending, walk.context);
    }
    if (walk.stopped || result == _URC_END_OF_STACK || result == _URC_NO_REASON)
        return StackWalkEnd::complete;
    return walk.skipped_self ? StackWalkEnd::incomplete : StackWalkEnd::unavailable;
}

#endif

} // namespace quidra::platform
