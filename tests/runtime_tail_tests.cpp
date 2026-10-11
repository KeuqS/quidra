#ifdef NDEBUG
#undef NDEBUG
#endif
#include "runtime_tail.hpp"
#include "platform/unwind.hpp"
#include "quidra/abi/runtime_entry_points.hpp"
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <thread>

namespace {
bool fail_allocation = false;
#ifndef _WIN32
struct ExpectedFrame {
    std::uintptr_t ip;
    std::uintptr_t cfa;
    bool found{};
    bool matched{};
};
bool check_frame(const quidra::platform::StackFrame& frame, void* context) {
    auto& expected = *static_cast<ExpectedFrame*>(context);
    if (frame.ip != expected.ip) return true;
    expected.found = true;
    expected.matched = frame.cfa == expected.cfa;
    return false;
}
[[gnu::noinline]] bool scan_caller(std::uintptr_t cfa) {
    ExpectedFrame expected{reinterpret_cast<std::uintptr_t>(
        __builtin_extract_return_addr(__builtin_return_address(0))), cfa};
    const auto end = quidra::platform::walk_stack(check_frame, &expected);
    return end == quidra::platform::StackWalkEnd::complete && expected.found && expected.matched;
}
[[gnu::noinline]] bool find_caller(std::uintptr_t cfa) {
    volatile unsigned char active = 3;
    const bool matched = scan_caller(cfa);
    return matched && active == 3;
}
[[gnu::noinline]] bool caller_cfa_matches() {
    volatile unsigned char storage[1024];
    storage[0] = 7;
    // The pre-call stack pointer is the child's CFA on both native ABIs.
    std::uintptr_t entry;
#if defined(__aarch64__)
    __asm__ volatile("mov %0, sp" : "=r"(entry));
#elif defined(__x86_64__)
    __asm__ volatile("mov %%rsp, %0" : "=r"(entry));
#else
#error Unsupported native stack pointer
#endif
    const bool matched = find_caller(entry);
    return matched && storage[0] == 7;
}
#endif
}
extern "C" void* quidra_tail_test_allocate(void* previous, std::size_t bytes) {
    if (fail_allocation) return nullptr;
    return previous ? std::realloc(previous, bytes) : std::malloc(bytes);
}
int main() {
#ifndef _WIN32
    assert(caller_cfa_matches());
#endif
    auto frame = reinterpret_cast<void*>(std::uintptr_t{1000});
    quidra_tail_record(1, 1, frame, 1);
    quidra_tail_record(2, 0, frame, 0);
    quidra_tail_record(1, 2, frame, 1);
    auto s = quidra::runtime_tail::snapshot();
    assert(s.entries.size() == 1 && s.entries[0].depth == 2);
    quidra_tail_record(3, 0, reinterpret_cast<void*>(std::uintptr_t{900}), 0);
    quidra_tail_record(4, 0, frame, 0);
    s = quidra::runtime_tail::snapshot();
    assert(s.entries.size() == 2 && s.entries[1].site == 4);
    quidra_tail_return(1, 2, frame);
    s = quidra::runtime_tail::snapshot();
    assert(s.entries.size() == 1 && s.entries[0].site == 4);
    for (unsigned i = 5; i < 140; ++i) quidra_tail_record(i, 0, frame, 0);
    s = quidra::runtime_tail::snapshot();
    assert(s.entries.size() == 136 && !s.lost_count);
    quidra_tail_record(4, 0, frame, 0);
    s = quidra::runtime_tail::snapshot();
    assert(s.entries.size() == 136 && s.entries.back().site == 4);
    quidra_tail_return(1, 140, frame);
    assert(quidra::runtime_tail::snapshot().entries.empty());
    fail_allocation = true;
    std::thread worker([] {
        // More than the inline capacity at successively deeper CFAs.
        for (unsigned i = 0; i < 65; ++i)
            quidra_tail_record(i + 1, 0, reinterpret_cast<void*>(std::uintptr_t{1000 - i * 4}), 0);
        const auto lost = quidra::runtime_tail::snapshot();
        assert(lost.entries.size() == 33 && lost.lost_count == 32);
        assert(lost.lost_at(1000) && !lost.lost_at(744));
        assert(lost.entries.front().site == 33 && lost.entries.back().site == 65);
        // Every old physical frame has returned: no stale loss marker.
        quidra_tail_record(66, 0, reinterpret_cast<void*>(std::uintptr_t{1100}), 0);
        const auto fresh = quidra::runtime_tail::snapshot();
        assert(fresh.entries.size() == 1 && !fresh.lost_count);
    });
    worker.join();
    fail_allocation = false;
    assert(quidra::runtime_tail::snapshot().entries.empty());
}
