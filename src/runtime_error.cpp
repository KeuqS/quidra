// Error values (quidra/abi/error_record.hpp): the records the runtime makes,
// their drop, and the runtime's entries that make them.
//
// A record made here is a managed allocation whose drop is set when it is
// made, so generated code releases it like a string (with a null drop
// argument). The drop releases what the record holds: its message, its text
// details, its hops and its cause; a chain of causes is released in a loop,
// never by recursion, so any length of chain is freed in constant stack.
// Records are made only on the error path; the message is rendered once,
// here, by abi::render_error, the renderer the backend uses for the constant
// records of the program's sites.

#include "runtime_internal.hpp"
#include "runtime_report.hpp"
#include "node_runtime_owner.hpp"
#include "quidra/abi/error_record.hpp"
#include "quidra/abi/runtime_entry_points.hpp"

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

namespace abi = quidra::abi;

namespace {

std::uint64_t* slots_of(abi::ErrorRecord* record) {
    return reinterpret_cast<std::uint64_t*>(reinterpret_cast<unsigned char*>(record) +
                                            sizeof(abi::ErrorRecord));
}

std::size_t slot_count(const abi::ErrorRecord* record) {
    const auto* schema = abi::error_value_schema(record->schema);
    return schema ? schema->details.size() : 0;
}

void release_text(const void* text) {
    if (text) quidra_managed_release(const_cast<void*>(text), nullptr);
}

void retain_text(const void* text) {
    if (text) quidra_managed_retain(const_cast<void*>(text));
}

void free_hops(abi::ErrorHopList* hops) {
    if (!hops) return;
    std::free(hops->entries);
    std::free(hops);
}

// Releases what a record holds besides its cause and its memory: the
// message, the text details and the hop list.
void release_parts(abi::ErrorRecord* record) {
    free_hops(record->hops);
    record->hops = nullptr;
    release_text(record->message);
    const auto* schema = abi::error_value_schema(record->schema);
    if (!schema) return;
    const auto* slots = slots_of(record);
    for (std::size_t i = 0; i < schema->details.size(); ++i)
        if (schema->details[i].kind == abi::ErrorDetailKind::text)
            release_text(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(slots[i])));
}

// The drop of a record: its parts, then its causes, each taken from the
// managed allocations (its own drop not run) while this record held its
// last owner.
void record_drop(void* value) {
    auto* record = static_cast<abi::ErrorRecord*>(value);
    release_parts(record);
    auto* cause = const_cast<abi::ErrorRecord*>(record->cause);
    quidra::runtime::TakenAllocation taken;
    while (cause && quidra::runtime::managed_release_take(cause, taken)) {
        release_parts(cause);
        auto* next = const_cast<abi::ErrorRecord*>(cause->cause);
        quidra::runtime::recycle_taken(taken);
        cause = next;
    }
}

abi::ErrorRecord* allocate_record(std::size_t slots) {
    const auto bytes = abi::error_record_size(slots);
    auto* record = static_cast<abi::ErrorRecord*>(
        quidra::runtime::managed_allocate_with_drop(bytes, record_drop));
    std::memset(static_cast<void*>(record), 0, bytes);
    return record;
}

// The origin: a site of user code passes its position; package code passes
// 0, 0, and the error is made at the user statement that led into it.
void set_origin(abi::ErrorRecord* record, unsigned long long line, unsigned long long column) {
    record->line = line;
    record->column = static_cast<std::uint32_t>(column);
    if (line == 0) record->statement = quidra::runtime::current_user_statement();
}

} // namespace

namespace quidra::runtime {

void* make_error_record(abi::ErrorValueCode code, const std::uint64_t* slots,
                        unsigned long long line, unsigned long long column, bool retain_texts) {
    const auto& schema = abi::error_value_schema(code);
    std::array<abi::ErrorDetailValue, abi::max_error_details> details{};
    for (std::size_t i = 0; i < schema.details.size(); ++i) {
        const auto kind = schema.details[i].kind;
        if (kind == abi::ErrorDetailKind::integer) {
            details[i] = abi::ErrorDetailValue::integer_value(static_cast<std::int64_t>(slots[i]));
            continue;
        }
        const auto* text = reinterpret_cast<const char*>(static_cast<std::uintptr_t>(slots[i]));
        details[i] = text ? abi::ErrorDetailValue{true, kind, std::string_view(text), 0}
                          : abi::ErrorDetailValue::absent(kind);
    }
    std::string message;
    if (!abi::render_error(schema, std::span(details.data(), schema.details.size()), message))
        message = schema.spelling;
    auto* record = allocate_record(schema.details.size());
    quidra::runtime::NodeRuntimeOwner partial(record);
    record->message = managed_text_copy(message);
    record->code = schema.spelling.data();
    record->schema = static_cast<std::uint32_t>(code);
    auto* record_slots = slots_of(record);
    for (std::size_t i = 0; i < schema.details.size(); ++i) {
        if (quidra::runtime::node_failure_active()) {
            if (retain_texts && schema.details[i].kind == abi::ErrorDetailKind::text)
                retain_text(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(slots[i])));
            record_slots[i] = slots[i];
        }else {
            record_slots[i] = slots[i];
            if (retain_texts && schema.details[i].kind == abi::ErrorDetailKind::text)
                retain_text(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(slots[i])));
        }
    }
    set_origin(record, line, column);
    partial.relinquish();
    return record;
}

} // namespace quidra::runtime

// A user or package error: its text (retained, never copied), its code (an
// immortal spelling; null is ERROR) and its cause (retained), made at the
// site's position (0, 0 in package code: at the user statement).
extern "C" void* quidra_error_new(const char* text, const char* code, const void* cause,
                                  unsigned long long line, unsigned long long column) {
    auto* record = allocate_record(0);
    quidra::runtime::NodeRuntimeOwner partial(record);
    retain_text(text);
    record->message = text ? text : "";
    record->code = code;
    if (cause) {
        retain_text(cause);
        record->cause = static_cast<const abi::ErrorRecord*>(cause);
    }
    set_origin(record, line, column);
    partial.relinquish();
    return record;
}

// A Core error whose details are values of the program: `slots` holds them
// in schema order (text details retained, never copied), and the message is
// rendered from them.
extern "C" void* quidra_error_make(int schema, const void* slots, unsigned long long line,
                                   unsigned long long column) {
    return quidra::runtime::make_error_record(static_cast<abi::ErrorValueCode>(schema),
                                              static_cast<const std::uint64_t*>(slots), line,
                                              column, true);
}

// A Core error made in package code from its site's constant record: a copy
// whose origin is the user statement that led into the package.
extern "C" void* quidra_error_from_site(const void* site) {
    const auto* constant = static_cast<const abi::ErrorRecord*>(site);
    const auto slots = slot_count(constant);
    auto* record = allocate_record(slots);
    if(quidra::runtime::node_failure_active()) {
        quidra::runtime::NodeRuntimeOwner partial(record);
        std::memcpy(static_cast<void*>(record), constant, abi::error_record_size(slots));
        record->message=nullptr;record->cause=nullptr;record->hops=nullptr;
        std::memset(slots_of(record),0,slots*sizeof(std::uint64_t));
        retain_text(constant->message);record->message=constant->message;
        if(const auto* schema=abi::error_value_schema(record->schema)) {
            for(std::size_t i=0;i<schema->details.size();++i) {
                const auto value=slots_of(const_cast<abi::ErrorRecord*>(constant))[i];
                if(schema->details[i].kind==abi::ErrorDetailKind::text)
                    retain_text(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(value)));
                slots_of(record)[i]=value;
            }
        }
    set_origin(record, 0, 0);
        partial.relinquish();return record;
    }
    std::memcpy(static_cast<void*>(record), constant, abi::error_record_size(slots));
    retain_text(record->message);
    if (const auto* schema = abi::error_value_schema(record->schema)) {
        const auto* record_slots = slots_of(record);
        for (std::size_t i = 0; i < schema->details.size(); ++i)
            if (schema->details[i].kind == abi::ErrorDetailKind::text)
                retain_text(reinterpret_cast<const void*>(
                    static_cast<std::uintptr_t>(record_slots[i])));
    }
    record->cause = nullptr;
    record->hops = nullptr;
    set_origin(record, 0, 0);
    return record;
}

namespace {

// The detail of `record` named error_detail_names[detail]: its value, or
// absent when the record's code has no such detail.
abi::ErrorDetailValue detail_of(const abi::ErrorRecord& record, int detail) {
    if (detail < 0 || static_cast<std::size_t>(detail) >= abi::error_detail_names.size())
        return abi::ErrorDetailValue::absent(abi::ErrorDetailKind::text);
    const auto name = abi::error_detail_names[static_cast<std::size_t>(detail)];
    const auto* schema = abi::error_value_schema(record.schema);
    if (!schema) {
        return name == "text" ? abi::ErrorDetailValue::text_value(record.message)
                              : abi::ErrorDetailValue::absent(abi::ErrorDetailKind::text);
    }
    const int index = abi::error_detail_index(*schema, name);
    if (index < 0) return abi::ErrorDetailValue::absent(abi::ErrorDetailKind::text);
    return abi::error_record_details(record, *schema)[static_cast<std::size_t>(index)];
}

std::string_view code_of(const abi::ErrorRecord& record) {
    return record.code ? std::string_view(record.code) : abi::user_error_code;
}

// One record's identity, without its cause: its code and its details (a
// user error's text).
bool same_record(const abi::ErrorRecord& left, const abi::ErrorRecord& right) {
    if (code_of(left) != code_of(right) || left.schema != right.schema) return false;
    const auto* schema = abi::error_value_schema(left.schema);
    if (!schema) return std::string_view(left.message) == std::string_view(right.message);
    const auto a = abi::error_record_details(left, *schema);
    const auto b = abi::error_record_details(right, *schema);
    const auto count = schema->details.size();
    return abi::same_error_identity({code_of(left), std::span(a.data(), count), nullptr, schema->details},
                                    {code_of(right), std::span(b.data(), count), nullptr, schema->details});
}

void put_quoted(std::string_view text) {
    std::fputc('"', stdout);
    std::fwrite(text.data(), 1, text.size(), stdout);
    std::fputc('"', stdout);
}

} // namespace

// The detail of an error named error_detail_names[detail], for a member
// read: a text (retained) or a name's spelling, or null when absent.
extern "C" const char* quidra_error_detail(const void* error, int detail) {
    if (!error) return nullptr;
    const auto value = detail_of(*static_cast<const abi::ErrorRecord*>(error), detail);
    if (!value.present || value.kind == abi::ErrorDetailKind::integer) return nullptr;
    retain_text(value.text.data());
    return value.text.data();
}

// The integer detail of an error named error_detail_names[detail], with
// *present false when its code has no such detail.
extern "C" long long quidra_error_detail_int(const void* error, int detail, bool* present) {
    const auto value = error ? detail_of(*static_cast<const abi::ErrorRecord*>(error), detail)
                             : abi::ErrorDetailValue::absent(abi::ErrorDetailKind::integer);
    const bool found = value.present && value.kind == abi::ErrorDetailKind::integer;
    if (present) *present = found;
    return found ? value.integer : 0;
}

// `==` on errors: the codes, the details that take part in identity and the
// cause chains, compared along the chain in a loop; never the origin or the
// hops.
extern "C" bool quidra_error_equal(const void* left, const void* right) {
    const auto* a = static_cast<const abi::ErrorRecord*>(left);
    const auto* b = static_cast<const abi::ErrorRecord*>(right);
    while (a && b) {
        if (a != b && !same_record(*a, *b)) return false;
        if (a == b) return true;
        a = a->cause;
        b = b->cause;
    }
    return a == nullptr && b == nullptr;
}

// The REPL's display of an error, in the form of its constructor: the
// message, the code (left out for ERROR), the details other than a user
// error's text in schema order (texts and names quoted, integers in
// decimal; absent ones left out), and the cause, nested.
extern "C" void quidra_error_display(const void* error) {
    std::size_t open = 0;
    for (const auto* record = static_cast<const abi::ErrorRecord*>(error); record;
         record = record->cause) {
        std::fputs("error(", stdout);
        put_quoted(record->message ? record->message : "");
        if (record->code) {
            std::fputs(", code = ", stdout);
            put_quoted(record->code);
        }
        if (const auto* schema = abi::error_value_schema(record->schema)) {
            const auto details = abi::error_record_details(*record, *schema);
            for (std::size_t i = 0; i < schema->details.size(); ++i) {
                if (!details[i].present) continue;
                std::fputs(", ", stdout);
                std::fwrite(schema->details[i].name.data(), 1, schema->details[i].name.size(), stdout);
                std::fputs(" = ", stdout);
                if (details[i].kind == abi::ErrorDetailKind::integer)
                    std::fprintf(stdout, "%lld", static_cast<long long>(details[i].integer));
                else
                    put_quoted(details[i].text);
            }
        }
        ++open;
        if (record->cause) std::fputs(", cause = ", stdout);
    }
    while (open-- != 0) std::fputc(')', stdout);
}

namespace {

[[noreturn]] void hop_allocation_failure() {
    quidra::runtime::report_uncoded("allocation failed");
}

abi::ErrorHopList* clone_hops(const abi::ErrorHopList* hops) {
    if (!hops) return nullptr;
    auto* copy = static_cast<abi::ErrorHopList*>(std::malloc(sizeof(abi::ErrorHopList)));
    if (!copy) hop_allocation_failure();
    copy->entries=nullptr;
    quidra::runtime::NodeRuntimeOwner partial(copy,[](void* raw){free_hops(static_cast<abi::ErrorHopList*>(raw));});
    copy->count = hops->count;
    copy->capacity = hops->count;
    copy->entries = static_cast<abi::ErrorHopEntry*>(
        std::malloc(sizeof(abi::ErrorHopEntry) * (hops->count ? hops->count : 1)));
    if (!copy->entries) hop_allocation_failure();
    if (hops->count)
        std::memcpy(copy->entries, hops->entries, sizeof(abi::ErrorHopEntry) * hops->count);
    partial.relinquish();
    return copy;
}

// A copy of a record this thread may not change (immortal, shared or held
// elsewhere): its header and details, the strings and the cause retained,
// its hop list cloned.
abi::ErrorRecord* copy_record(const abi::ErrorRecord* record) {
    const auto slots = slot_count(record);
    auto* copy = allocate_record(slots);
    if(quidra::runtime::node_failure_active()) {
        quidra::runtime::NodeRuntimeOwner partial(copy);
        std::memcpy(static_cast<void*>(copy), record, abi::error_record_size(slots));
        copy->message=nullptr;copy->cause=nullptr;copy->hops=nullptr;
        std::memset(slots_of(copy),0,slots*sizeof(std::uint64_t));
        retain_text(record->message);copy->message=record->message;
        if(const auto* schema=abi::error_value_schema(copy->schema)) {
            for(std::size_t i=0;i<schema->details.size();++i) {
                const auto value=slots_of(const_cast<abi::ErrorRecord*>(record))[i];
                if(schema->details[i].kind==abi::ErrorDetailKind::text)
                    retain_text(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(value)));
                slots_of(copy)[i]=value;
            }
        }
        retain_text(record->cause);copy->cause=record->cause;
        copy->hops=clone_hops(record->hops);
        partial.relinquish();return copy;
    }
    std::memcpy(static_cast<void*>(copy), record, abi::error_record_size(slots));
    retain_text(copy->message);
    if (const auto* schema = abi::error_value_schema(copy->schema)) {
        const auto* copy_slots = slots_of(copy);
        for (std::size_t i = 0; i < schema->details.size(); ++i)
            if (schema->details[i].kind == abi::ErrorDetailKind::text)
                retain_text(reinterpret_cast<const void*>(
                    static_cast<std::uintptr_t>(copy_slots[i])));
    }
    retain_text(copy->cause);
    copy->hops = clone_hops(record->hops);
    return copy;
}

void append_hop(abi::ErrorRecord* record, const abi::ErrorHopSite* site, const void* callee) {
    auto* hops = record->hops;
    if (hops && hops->count != 0 && hops->entries[hops->count - 1].site == site &&
        hops->entries[hops->count - 1].callee == callee) {
        ++hops->entries[hops->count - 1].repeat;
        return;
    }
    if (!hops) {
        hops = static_cast<abi::ErrorHopList*>(std::malloc(sizeof(abi::ErrorHopList)));
        if (!hops) hop_allocation_failure();
        hops->count = 0;
        hops->capacity = 4;
        hops->entries = nullptr;
        if(quidra::runtime::node_failure_active())record->hops=hops;
        hops->entries =
            static_cast<abi::ErrorHopEntry*>(std::malloc(sizeof(abi::ErrorHopEntry) * 4));
        if (!hops->entries) hop_allocation_failure();
        record->hops = hops;
    } else if (hops->count == hops->capacity) {
        const auto capacity = hops->capacity * 2;
        auto* entries = static_cast<abi::ErrorHopEntry*>(
            std::realloc(hops->entries, sizeof(abi::ErrorHopEntry) * capacity));
        if (!entries) hop_allocation_failure();
        hops->entries = entries;
        hops->capacity = capacity;
    }
    hops->entries[hops->count++] = abi::ErrorHopEntry{site, 1, callee};
}

} // namespace

// A hop: `error` left a call at `site` on the error path. Consumes one
// reference to `error` and returns one: the same record with the hop
// appended when this thread holds its only reference; otherwise a copy
// (the argument released once), so that no other holder sees the hop.
extern "C" void* quidra_error_hop(void* error, const void* site) {
    return quidra_error_hop_indirect(error, site, nullptr);
}

// A hop of a call through an `func` value: the same, with the code address
// the call reached.
extern "C" void* quidra_error_hop_indirect(void* error, const void* site, const void* callee) {
    auto* record = static_cast<abi::ErrorRecord*>(error);
    if (!record) return nullptr;
    quidra::runtime::NodeRuntimeOwner partial(record);
    if (quidra::runtime::managed_owners(record) != 1) {
        auto* copy = copy_record(record);
        partial.replace(copy);
        quidra_managed_release(record, nullptr);
        record = copy;
    }
    append_hop(record, static_cast<const abi::ErrorHopSite*>(site), callee);
    partial.relinquish();
    return record;
}
