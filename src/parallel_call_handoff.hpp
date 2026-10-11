#pragma once
#include "node_failure.hpp"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>

namespace quidra::runtime {
// A clear callback only stores the type's empty representation into its
// stable owning mirror. It allocates, releases and reports nothing.
struct PendingArgumentOwner {
    void* slot{};
    void (*clear)(void*) noexcept{};
};
struct PendingCallAcceptance {
    PendingCallAcceptance* previous{};
    NodeFailureScope* owner{};
    const void* target{};
    std::uint32_t count{};
    bool accepted{};
};
inline thread_local PendingCallAcceptance* pending_call_acceptance{};
inline PendingArgumentOwner* pending_arguments(PendingCallAcceptance* call) noexcept {
    return reinterpret_cast<PendingArgumentOwner*>(call+1);
}
inline void unlink_pending_call(PendingCallAcceptance* call) noexcept {
    auto** link=&pending_call_acceptance;
    while(*link && *link!=call)link=&(*link)->previous;
    if(*link==call)*link=call->previous;
}
inline void abandon_pending_call(void* raw) noexcept {
    // The original caller mirrors still own unaccepted arguments; their
    // ordinary node cleanup frames perform the typed drops. This callback
    // removes only the acceptance marker, so it cannot duplicate ownership.
    unlink_pending_call(static_cast<PendingCallAcceptance*>(raw));
}
inline void* begin_pending_call(const void* target,const PendingArgumentOwner* arguments,
                               std::uint32_t count) {
    if(!current_node_failure || !count)return nullptr;
    if(!target || !arguments || static_cast<std::size_t>(count)>(std::numeric_limits<std::size_t>::max()-sizeof(PendingCallAcceptance))/sizeof(PendingArgumentOwner))
        report_uncoded("invalid parallel argument ownership handoff");
    for(std::uint32_t i=0;i<count;++i)if(!arguments[i].slot || !arguments[i].clear)
        report_uncoded("invalid parallel argument ownership mirror");
    const auto bytes=sizeof(PendingCallAcceptance)+sizeof(PendingArgumentOwner)*count;
    auto* call=static_cast<PendingCallAcceptance*>(create_node_frame(bytes,alignof(PendingCallAcceptance),abandon_pending_call));
    call->previous=pending_call_acceptance;call->owner=current_node_failure;
    call->target=target;call->count=count;
    std::memcpy(pending_arguments(call),arguments,sizeof(PendingArgumentOwner)*count);
    pending_call_acceptance=call;
    return call;
}
inline bool accept_pending_call(const void* target) noexcept {
    auto* call=pending_call_acceptance;
    if(!call || call->target!=target || call->owner!=current_node_failure)return false;
    // Callee stable slots have already accepted the values through stores
    // with no intervening fallible operation. Clear caller obligations in a
    // no-fail transaction before stack checks or any next allocation.
    auto* arguments=pending_arguments(call);
    for(std::uint32_t i=0;i<call->count;++i)arguments[i].clear(arguments[i].slot);
    call->accepted=true;unlink_pending_call(call);
    return true;
}
inline bool end_pending_call(void* raw) noexcept {
    if(!raw)return true;
    auto* call=static_cast<PendingCallAcceptance*>(raw);
    const bool accepted=call->accepted;
    unlink_pending_call(call);leave_node_frame(call);
    // The compiler must treat false for a defined consuming callee as a
    // broken ownership contract; continuing normal typed cleanup is unsafe.
    return accepted;
}
}
