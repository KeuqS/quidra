// The runtime's error records (src/runtime_error.cpp): the constructors, the
// drop and the iterative release of a cause chain, and the internal entries
// of runtime.cpp they use.
#include "runtime_internal.hpp"
#include "quidra/abi/error_record.hpp"
#include "quidra/abi/runtime_entry_points.hpp"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string_view>

// Keep the checks and their observable calls active under NDEBUG.
#define CHECK(condition) do { \
    if (!(condition)) { \
        std::fprintf(stderr, "runtime error check failed at line %d: %s\n", __LINE__, #condition); \
        std::abort(); \
    } \
} while (false)

namespace abi = quidra::abi;
namespace runtime = quidra::runtime;

namespace {

int drops = 0;
void counting_drop(void*) { ++drops; }

const abi::ErrorRecord* record(const void* value) { return static_cast<const abi::ErrorRecord*>(value); }

std::uint64_t slot(const void* value, std::size_t index) {
    return reinterpret_cast<const std::uint64_t*>(static_cast<const unsigned char*>(value) +
                                                  abi::error_slot_offset(index))[0];
}

} // namespace

int main() {
    // A drop set when the allocation is made survives a release with a null
    // drop argument and runs at zero owners.
    void* with_drop = runtime::managed_allocate_with_drop(24, counting_drop);
    CHECK(runtime::is_managed(with_drop) && runtime::managed_owners(with_drop) == 1);
    quidra_managed_retain(with_drop);
    quidra_managed_release(with_drop, nullptr);
    CHECK(drops == 0);
    quidra_managed_release(with_drop, nullptr);
    CHECK(drops == 1);

    // managed_release_take unregisters at zero without running the drop.
    void* taken_value = runtime::managed_allocate_with_drop(24, counting_drop);
    quidra_managed_retain(taken_value);
    runtime::TakenAllocation taken;
    CHECK(!runtime::managed_release_take(taken_value, taken));
    CHECK(runtime::managed_owners(taken_value) == 1);
    CHECK(runtime::managed_release_take(taken_value, taken));
    CHECK(!runtime::is_managed(taken_value) && drops == 1 && taken.base == taken_value);
    runtime::recycle_taken(taken);
    int on_stack = 0;
    CHECK(!runtime::managed_release_take(&on_stack, taken));

    // A user error retains its text (never copies it) and its cause; the
    // drop releases both.
    char* text = runtime::managed_text_copy("dataset loading failed");
    char* cause_text = runtime::managed_text_copy("cannot read");
    void* cause = quidra_error_new(cause_text, nullptr, nullptr, 3, 7);
    CHECK(runtime::managed_owners(cause_text) == 2);
    void* error = quidra_error_new(text, "DATASET_LOAD", cause, 13, 20);
    CHECK(record(error)->message == text && runtime::managed_owners(text) == 2);
    CHECK(std::string_view(record(error)->code) == "DATASET_LOAD");
    CHECK(record(error)->schema == 0 && record(error)->line == 13 && record(error)->column == 20);
    CHECK(record(error)->cause == cause && runtime::managed_owners(cause) == 2);
    CHECK(record(cause)->code == nullptr);
    quidra_managed_release(cause, nullptr);
    quidra_managed_release(error, nullptr);
    CHECK(!runtime::is_managed(error) && !runtime::is_managed(cause));
    CHECK(runtime::managed_owners(text) == 1 && runtime::managed_owners(cause_text) == 1);
    quidra_managed_release(text, nullptr);
    quidra_managed_release(cause_text, nullptr);

    // A Core error from its details: the message rendered by the shared
    // renderer, text details retained.
    char* input = runtime::managed_text_copy("abc");
    const std::uint64_t slots[] = {
        reinterpret_cast<std::uintptr_t>("UNREADABLE_FIELD"), 0,
        reinterpret_cast<std::uintptr_t>("int"), reinterpret_cast<std::uintptr_t>(input)};
    void* format_error = quidra_error_make(static_cast<int>(abi::ErrorValueCode::input_format),
                                           slots, 4, 1);
    CHECK(std::string_view(record(format_error)->message) == "scan could not read int from \"abc\"");
    CHECK(std::string_view(record(format_error)->code) == "INPUT_FORMAT");
    CHECK(slot(format_error, 3) == reinterpret_cast<std::uintptr_t>(input));
    CHECK(runtime::managed_owners(input) == 2);
    quidra_managed_release(format_error, nullptr);
    CHECK(runtime::managed_owners(input) == 1);
    quidra_managed_release(input, nullptr);

    // A chain of 100 000 causes is freed without stack growth: the drop
    // takes each cause in a loop.
    void* chain = nullptr;
    for (int i = 0; i < 100000; ++i) {
        void* next = quidra_error_new("retry", nullptr, chain, 1, 1);
        quidra_managed_release(chain, nullptr);
        chain = next;
    }
    quidra_managed_release(chain, nullptr);
    CHECK(!runtime::is_managed(chain));

    std::puts("runtime error tests passed");
    return 0;
}
