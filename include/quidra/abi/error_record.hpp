#pragma once

// The error value of a Quidra program: the record an `error` points to, the
// schema of every Core error code, the rendering of a record's message from
// its code and details, and the identity that `==` compares.
//
// An error has a code, typed details defined per code, an optional cause,
// and, kept apart from these, its origin (where it was made) and the hops it
// propagated through. Its message is a rendering of the code and the
// details, made once, when the error is made: by the backend for a constant
// record of a site (at compile time) and by the runtime for a record made at
// run time, both through render_error, so the two never differ.
//
// Owns: the ErrorRecord layout (shared with generated code, which emits
// constant records of this layout, and with the runtime, which allocates
// them); the Core error codes (ErrorValueCode) with their detail schemas and
// the closed lists of their name details; the rules of a user or package
// code. Std-only: no runtime allocator, no LLVM.

#include "quidra/abi/runtime_failure.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <type_traits>

namespace quidra::abi {

// How an error left a call (the JSON report's "via").
enum class ErrorHopKind : std::uint64_t { try_call = 0, fail_fast = 1, match = 2 };

// The site of a hop, an immortal constant of generated code: the display
// name of the function the error left ("parse_port()", "Model.forward()"),
// the call's position (the line encoded as (file index << 32) | line; 0 for
// a call in package code) and the ErrorHopKind.
struct ErrorHopSite {
    const char* name;
    std::uint64_t line;
    std::uint64_t column;
    std::uint64_t kind;
};

// One hop of an error: its site, how many times in a row the error left it
// (a recursion propagating through one site is one entry), and for a call
// through an `func` value the code address it called (null otherwise), which
// the report names through the call-site table.
struct ErrorHopEntry {
    const ErrorHopSite* site;
    std::uint64_t repeat;
    const void* callee;
};

// The hops of an error, inner to outer, owned by the one record that holds
// the list (a copy of a record clones its list).
struct ErrorHopList {
    std::uint64_t count;
    std::uint64_t capacity;
    ErrorHopEntry* entries;
};

constexpr std::string_view error_hop_via(std::uint64_t kind) {
    switch (static_cast<ErrorHopKind>(kind)) {
        case ErrorHopKind::try_call: return "try";
        case ErrorHopKind::fail_fast: return "fail_fast";
        case ErrorHopKind::match: return "match";
    }
    return "try";
}

static_assert(sizeof(ErrorHopSite) == 32);

// The record header. The detail slots immediately follow it, eight bytes
// per slot, in the order of the code's schema: a text detail is a
// `const char*` (a Quidra string; null when absent), a name detail a
// `const char*` to an immortal spelling (null when absent), an integer
// detail a std::int64_t. A user or package error has no slot: its text is
// its message.
struct ErrorRecord {
    // The rendering of the code and the details; never null.
    const char* message;
    // The code's immortal spelling; null is ERROR (a user error without
    // `code =`).
    const char* code;
    // The row of error_value_codes (its ErrorValueCode) for a Core code; 0
    // for a user or package code.
    std::uint32_t schema;
    // The origin's column (one-based bytes).
    std::uint32_t column;
    // An owned reference to the cause, or null.
    const ErrorRecord* cause;
    // The origin's line: (file index << 32) | line; 0 when the error was made
    // in package code, whose origin is the statement below.
    std::uint64_t line;
    // The origin of an error made in package code: the user statement
    // (abi::SourceProvenanceRecord) that led into the package; null
    // otherwise.
    const void* statement;
    // The hops the error propagated through (owned; null before the first).
    ErrorHopList* hops;
};

static_assert(std::is_standard_layout_v<ErrorRecord>);
// Emscripten builds the frontend-only bridge, which uses the schemas below
// but neither emits nor allocates native error records. The native ABI remains
// 64-bit; do not apply its layout assertions to the bridge's host pointers.
#ifndef __EMSCRIPTEN__
static_assert(sizeof(void*) == 8, "Quidra's error-record ABI requires 64-bit pointers");
static_assert(sizeof(ErrorRecord) == 56);
static_assert(alignof(ErrorRecord) == 8);
static_assert(offsetof(ErrorRecord, message) == 0);
static_assert(offsetof(ErrorRecord, code) == 8);
static_assert(offsetof(ErrorRecord, schema) == 16);
static_assert(offsetof(ErrorRecord, column) == 20);
static_assert(offsetof(ErrorRecord, cause) == 24);
static_assert(offsetof(ErrorRecord, line) == 32);
static_assert(offsetof(ErrorRecord, statement) == 40);
static_assert(offsetof(ErrorRecord, hops) == 48);
#endif

struct ErrorDetailSlot { std::uint64_t bits; };
static_assert(sizeof(ErrorDetailSlot) == 8);
static_assert(alignof(ErrorDetailSlot) == 8);

// The byte offset of detail slot `index`.
constexpr std::size_t error_slot_offset(std::size_t index) {
    return sizeof(ErrorRecord) + sizeof(ErrorDetailSlot) * index;
}

// The size of a record with `slots` detail slots.
constexpr std::size_t error_record_size(std::size_t slots) { return error_slot_offset(slots); }

enum class ErrorDetailKind : std::uint8_t { text, name, integer };

// One detail of a code's schema: its name (the member a program reads it
// through, and its key in the JSON report), its kind, whether it takes part
// in `==` (identity), whether one error may lack it (optional; never for an
// integer), and, for a name detail, the closed list of its spellings (empty
// for a text or integer detail, and for `type`, which holds a type's Quidra
// spelling).
struct ErrorDetailSchema {
    std::string_view name;
    ErrorDetailKind kind;
    bool identity;
    bool optional;
    std::span<const std::string_view> values{};
};

// Schema 0 is a user or package code, whose one detail is its text (its
// message). The Core codes' numbers are stable: a record names its schema.
enum class ErrorValueCode : std::uint32_t {
    file_read = 1, file_write, file_open, file_seek, file_status,
    file_list, file_remove, file_copy, file_move, file_mkdir,
    numeric_parse, bin_parse, utf8_decode, input_end, input_read,
    input_format, output_write, numeric_conversion, json_parse,
    json_value, http_request
};

struct ErrorValueCodeInfo {
    ErrorValueCode code;
    std::string_view spelling;
    std::span<const ErrorDetailSchema> details;
};

// The closed lists of the name details, in their order (a record array of a
// site is indexed by a reason's position in its code's list).
inline constexpr std::array<std::string_view, 12> file_reasons{
    "NOT_FOUND", "PERMISSION_DENIED", "IS_A_DIRECTORY", "NOT_A_DIRECTORY", "ALREADY_EXISTS",
    "INVALID_UTF8", "EMBEDDED_NUL", "UNALIGNED_BIN", "PATH_NOT_TEXT", "HANDLE_CLOSED",
    "NOT_WRITABLE", "IO_FAILURE"};
inline constexpr std::array<std::string_view, 3> file_open_modes{"READ", "CREATE", "APPEND"};
inline constexpr std::array<std::string_view, 2> parse_reasons{"INVALID_TEXT", "OUT_OF_RANGE"};
inline constexpr std::array<std::string_view, 3> input_read_reasons{"INVALID_UTF8", "EMBEDDED_NUL",
                                                                    "IO_FAILURE"};
inline constexpr std::array<std::string_view, 3> input_format_reasons{
    "MISSING_TEXT", "UNREADABLE_FIELD", "TRAILING_INPUT"};
// In the order of abi::ConversionSubject and abi::ConversionReason.
inline constexpr std::array<std::string_view, 3> conversion_subject_spellings{
    "VALUE", "ARRAY_ELEMENT", "TENSOR_ELEMENT"};
inline constexpr std::array<std::string_view, 4> conversion_reason_spellings{
    "OUT_OF_RANGE", "NON_FINITE", "NOT_INTEGRAL", "UNDECIDED"};

inline constexpr ErrorDetailSchema detail_path{"path", ErrorDetailKind::text, true, true};
inline constexpr ErrorDetailSchema detail_file_reason{"reason", ErrorDetailKind::name, true, false,
                                                      file_reasons};
inline constexpr std::array<ErrorDetailSchema, 2> path_and_reason{detail_path, detail_file_reason};
inline constexpr std::array<ErrorDetailSchema, 3> open_details{
    ErrorDetailSchema{"path", ErrorDetailKind::text, true, false},
    ErrorDetailSchema{"mode", ErrorDetailKind::name, true, false, file_open_modes},
    detail_file_reason};
inline constexpr std::array<ErrorDetailSchema, 3> transfer_details{
    ErrorDetailSchema{"path", ErrorDetailKind::text, true, false},
    ErrorDetailSchema{"destination", ErrorDetailKind::text, true, false}, detail_file_reason};
inline constexpr std::array<ErrorDetailSchema, 2> parse_details{
    ErrorDetailSchema{"type", ErrorDetailKind::name, true, false},
    ErrorDetailSchema{"reason", ErrorDetailKind::name, true, false, parse_reasons}};
inline constexpr std::array<ErrorDetailSchema, 4> input_format_details{
    ErrorDetailSchema{"reason", ErrorDetailKind::name, true, false, input_format_reasons},
    ErrorDetailSchema{"literal", ErrorDetailKind::text, true, true},
    ErrorDetailSchema{"type", ErrorDetailKind::name, true, true},
    ErrorDetailSchema{"input", ErrorDetailKind::text, true, true}};
inline constexpr std::array<ErrorDetailSchema, 3> conversion_details{
    ErrorDetailSchema{"type", ErrorDetailKind::name, true, false},
    ErrorDetailSchema{"subject", ErrorDetailKind::name, true, false, conversion_subject_spellings},
    ErrorDetailSchema{"reason", ErrorDetailKind::name, true, false, conversion_reason_spellings}};
inline constexpr std::array<ErrorDetailSchema, 2> json_parse_details{
    ErrorDetailSchema{"problem", ErrorDetailKind::text, true, false},
    ErrorDetailSchema{"offset", ErrorDetailKind::integer, true, false}};
inline constexpr std::array<ErrorDetailSchema, 1> problem_details{
    ErrorDetailSchema{"problem", ErrorDetailKind::text, true, false}};
inline constexpr std::array<ErrorDetailSchema, 1> input_read_details{
    ErrorDetailSchema{"reason", ErrorDetailKind::name, true, false, input_read_reasons}};
inline constexpr std::array<ErrorDetailSchema, 0> no_details{};

// The table is ordered by the schema number. Adding a code appends a row;
// renumbering a row would misread the records that name it.
inline constexpr std::array error_value_codes{
    ErrorValueCodeInfo{ErrorValueCode::file_read, "FILE_READ", path_and_reason},
    ErrorValueCodeInfo{ErrorValueCode::file_write, "FILE_WRITE", path_and_reason},
    ErrorValueCodeInfo{ErrorValueCode::file_open, "FILE_OPEN", open_details},
    ErrorValueCodeInfo{ErrorValueCode::file_seek, "FILE_SEEK", path_and_reason},
    ErrorValueCodeInfo{ErrorValueCode::file_status, "FILE_STATUS", path_and_reason},
    ErrorValueCodeInfo{ErrorValueCode::file_list, "FILE_LIST", path_and_reason},
    ErrorValueCodeInfo{ErrorValueCode::file_remove, "FILE_REMOVE", path_and_reason},
    ErrorValueCodeInfo{ErrorValueCode::file_copy, "FILE_COPY", transfer_details},
    ErrorValueCodeInfo{ErrorValueCode::file_move, "FILE_MOVE", transfer_details},
    ErrorValueCodeInfo{ErrorValueCode::file_mkdir, "FILE_MKDIR", path_and_reason},
    ErrorValueCodeInfo{ErrorValueCode::numeric_parse, "NUMERIC_PARSE", parse_details},
    ErrorValueCodeInfo{ErrorValueCode::bin_parse, "BIN_PARSE", no_details},
    ErrorValueCodeInfo{ErrorValueCode::utf8_decode, "UTF8_DECODE", no_details},
    ErrorValueCodeInfo{ErrorValueCode::input_end, "INPUT_END", no_details},
    ErrorValueCodeInfo{ErrorValueCode::input_read, "INPUT_READ", input_read_details},
    ErrorValueCodeInfo{ErrorValueCode::input_format, "INPUT_FORMAT", input_format_details},
    ErrorValueCodeInfo{ErrorValueCode::output_write, "OUTPUT_WRITE", no_details},
    ErrorValueCodeInfo{ErrorValueCode::numeric_conversion, "NUMERIC_CONVERSION", conversion_details},
    ErrorValueCodeInfo{ErrorValueCode::json_parse, "JSON_PARSE", json_parse_details},
    ErrorValueCodeInfo{ErrorValueCode::json_value, "JSON_VALUE", no_details},
    ErrorValueCodeInfo{ErrorValueCode::http_request, "HTTP_REQUEST", problem_details}
};

// The spelling of a user error without `code =`.
inline constexpr std::string_view user_error_code = "ERROR";

// The largest number of detail slots of a Core schema.
inline constexpr std::size_t max_error_details = 4;

constexpr const ErrorValueCodeInfo* error_value_schema(std::uint32_t id) {
    if (id == 0 || id > error_value_codes.size()) return nullptr;
    const auto& value = error_value_codes[id - 1];
    return static_cast<std::uint32_t>(value.code) == id ? &value : nullptr;
}

constexpr const ErrorValueCodeInfo& error_value_schema(ErrorValueCode code) {
    return error_value_codes[static_cast<std::size_t>(code) - 1];
}

// The position of `spelling` in a closed list, or -1.
constexpr int spelling_index(std::span<const std::string_view> values, std::string_view spelling) {
    for (std::size_t i = 0; i < values.size(); ++i)
        if (values[i] == spelling) return static_cast<int>(i);
    return -1;
}

// The schema index of the detail `name`, or -1.
constexpr int error_detail_index(const ErrorValueCodeInfo& schema, std::string_view name) {
    for (std::size_t i = 0; i < schema.details.size(); ++i)
        if (schema.details[i].name == name) return static_cast<int>(i);
    return -1;
}

// The detail names a program reads as members of an `error` (e.path, ...):
// the vocabulary of every Core schema, plus `text`, the detail of a user or
// package error. A member's index is its position here.
inline constexpr std::array<std::string_view, 11> error_detail_names{
    "path", "destination", "mode", "reason", "type", "subject", "literal", "input",
    "problem", "text", "offset"};

constexpr int error_detail_name_index(std::string_view name) {
    return spelling_index(error_detail_names, name);
}

// Whether the detail named `name` is an integer in every schema that has it.
constexpr bool error_detail_is_integer(std::string_view name) { return name == "offset"; }

// The spelling rule of a user or package code: words of capital letters and
// digits joined by single underscores, starting with a letter.
constexpr bool valid_user_error_code(std::string_view spelling) {
    if (spelling.empty() || spelling.front() < 'A' || spelling.front() > 'Z')
        return false;
    bool after_underscore = false;
    for (const char c : spelling) {
        if (c == '_') {
            if (after_underscore) return false;
            after_underscore = true;
        } else if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            after_underscore = false;
        } else {
            return false;
        }
    }
    return !after_underscore;
}

// A Core code: ERROR, an error-value code or a runtime failure code. A user
// or package error may not use one.
constexpr bool is_core_error_code(std::string_view spelling) {
    if (spelling == user_error_code) return true;
    for (const auto& value : error_value_codes)
        if (value.spelling == spelling) return true;
    for (const auto& value : runtime_failure_codes)
        if (value.spelling == spelling) return true;
    return false;
}

// A package's code prefix: its name in upper case, every other character an
// underscore ("nn" -> "NN", "my-pkg" -> "MY_PKG"); a code of the package
// starts with it and an underscore.
inline std::string package_error_code_prefix(std::string_view package) {
    std::string prefix;
    for (const char c : package) {
        if (c >= 'a' && c <= 'z') prefix += static_cast<char>(c - 'a' + 'A');
        else if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) prefix += c;
        else prefix += '_';
    }
    return prefix;
}

constexpr bool valid_custom_error_code(std::string_view spelling,
                                       std::string_view required_prefix = {}) {
    if (!valid_user_error_code(spelling) || is_core_error_code(spelling)) return false;
    if (required_prefix.empty()) return true;
    return spelling.size() > required_prefix.size() &&
           spelling.substr(0, required_prefix.size()) == required_prefix &&
           spelling[required_prefix.size()] == '_';
}

static_assert(error_value_codes.size() ==
              static_cast<std::uint32_t>(ErrorValueCode::http_request));
static_assert(valid_custom_error_code("DATASET_LOAD"));
static_assert(valid_custom_error_code("NN_CHECKPOINT", "NN"));
static_assert(!valid_custom_error_code("NN__BAD"));
static_assert(!valid_custom_error_code("ERROR"));
static_assert(!valid_custom_error_code("FILE_READ"));
static_assert(!valid_custom_error_code("OTHER_SHAPE", "NN"));

// Materialized details, in schema order. An absent text or name detail
// differs from a present but empty one. Integer details cannot be absent.
// These are plain views: the runtime passes its managed strings to the
// renderer without giving up ownership.
struct ErrorDetailValue {
    bool present{};
    ErrorDetailKind kind{ErrorDetailKind::text};
    std::string_view text{};
    std::int64_t integer{};

    static constexpr ErrorDetailValue text_value(std::string_view value) {
        return {true, ErrorDetailKind::text, value, 0};
    }
    static constexpr ErrorDetailValue name_value(std::string_view value) {
        return {true, ErrorDetailKind::name, value, 0};
    }
    static constexpr ErrorDetailValue integer_value(std::int64_t value) {
        return {true, ErrorDetailKind::integer, {}, value};
    }
    static constexpr ErrorDetailValue absent(ErrorDetailKind kind) {
        return {false, kind, {}, 0};
    }
};

// Whether `values` fit `schema`: one per detail, of its kind, present unless
// optional, and a name from the detail's closed list when it has one.
constexpr bool valid_error_details(const ErrorValueCodeInfo& schema,
                                   std::span<const ErrorDetailValue> values) {
    if (values.size() != schema.details.size()) return false;
    for (std::size_t i = 0; i != values.size(); ++i) {
        const auto& value = values[i];
        const auto& detail = schema.details[i];
        if (value.kind != detail.kind || (!value.present && !detail.optional))
            return false;
        if (value.present && !detail.values.empty() &&
            spelling_index(detail.values, value.text) < 0)
            return false;
    }
    return true;
}

// The details of a record, read from its slots by its schema.
inline std::array<ErrorDetailValue, max_error_details> error_record_details(
    const ErrorRecord& record, const ErrorValueCodeInfo& schema) {
    std::array<ErrorDetailValue, max_error_details> values{};
    const auto* slots = reinterpret_cast<const std::uint64_t*>(
        reinterpret_cast<const unsigned char*>(&record) + sizeof(ErrorRecord));
    for (std::size_t i = 0; i < schema.details.size() && i < values.size(); ++i) {
        const auto kind = schema.details[i].kind;
        if (kind == ErrorDetailKind::integer) {
            values[i] = ErrorDetailValue::integer_value(static_cast<std::int64_t>(slots[i]));
            continue;
        }
        const auto* text = reinterpret_cast<const char*>(static_cast<std::uintptr_t>(slots[i]));
        values[i] = text ? ErrorDetailValue{true, kind, std::string_view(text), 0}
                         : ErrorDetailValue::absent(kind);
    }
    return values;
}

// The identity that `==` compares: the code (as text; ERROR for a codeless
// user error), the details of the code's schema (a user or package error:
// its text, with an empty schema) and the cause, by the same rule. The
// origin, the hops and the call path are not part of it, and the message is
// not compared on its own, being a rendering of the code and the details.
struct ErrorValueIdentity {
    std::string_view code;
    std::span<const ErrorDetailValue> details;
    const ErrorValueIdentity* cause{};
    // The schema of the details: a detail whose schema row has identity
    // false is left out; with no schema every detail takes part.
    std::span<const ErrorDetailSchema> schema{};
};

inline bool same_error_identity(const ErrorValueIdentity& first,
                                const ErrorValueIdentity& second) {
    const ErrorValueIdentity* left = &first;
    const ErrorValueIdentity* right = &second;
    while (left != nullptr && right != nullptr) {
        if (left->code != right->code || left->details.size() != right->details.size())
            return false;
        for (std::size_t i = 0; i != left->details.size(); ++i) {
            if (i < left->schema.size() && !left->schema[i].identity) continue;
            const auto& a = left->details[i];
            const auto& b = right->details[i];
            if (a.present != b.present || a.kind != b.kind) return false;
            if (!a.present) continue;
            if (a.kind == ErrorDetailKind::integer) {
                if (a.integer != b.integer) return false;
            } else if (a.text != b.text) {
                return false;
            }
        }
        left = left->cause;
        right = right->cause;
    }
    return left == nullptr && right == nullptr;
}

// The text of a file or input reason in a message ("file not found").
constexpr std::string_view error_reason_text(std::string_view reason) {
    if (reason == "NOT_FOUND") return "file not found";
    if (reason == "PERMISSION_DENIED") return "permission denied";
    if (reason == "IS_A_DIRECTORY") return "path is a directory";
    if (reason == "NOT_A_DIRECTORY") return "path is not a directory";
    if (reason == "ALREADY_EXISTS") return "path already exists";
    if (reason == "INVALID_UTF8") return "invalid UTF-8 text";
    if (reason == "EMBEDDED_NUL") return "text contains a NUL character";
    if (reason == "UNALIGNED_BIN") return "bin length is not a multiple of 8";
    if (reason == "PATH_NOT_TEXT") return "path is not valid text";
    if (reason == "HANDLE_CLOSED") return "handle is closed";
    if (reason == "NOT_WRITABLE") return "handle is not writable";
    return "I/O failure";
}

// The verb of a file code's message ("cannot <verb> ..."); FILE_OPEN's
// follows its mode.
constexpr std::string_view file_error_verb(ErrorValueCode code, std::string_view mode = {}) {
    switch (code) {
        case ErrorValueCode::file_read: return "read";
        case ErrorValueCode::file_write: return "write";
        case ErrorValueCode::file_open:
            if (mode == "CREATE") return "create";
            if (mode == "APPEND") return "open for appending";
            return "open";
        case ErrorValueCode::file_seek: return "seek in";
        case ErrorValueCode::file_status: return "inspect";
        case ErrorValueCode::file_list: return "list";
        case ErrorValueCode::file_remove: return "remove";
        case ErrorValueCode::file_copy: return "copy";
        case ErrorValueCode::file_move: return "move";
        case ErrorValueCode::file_mkdir: return "create directory";
        default: return "use";
    }
}

// The message of a record of `schema` with `details`, into `output`; false,
// with `output` unchanged, when the details do not fit the schema. One
// renderer serves the backend's constant records and the runtime's records.
// A path is written between double quotes as the program passed it (an
// empty path as ""); an operation on a file handle, which has no path, says
// "the file handle". NUMERIC_CONVERSION is the runtime failure table's
// template for its reason.
inline bool render_error(const ErrorValueCodeInfo& schema,
                         std::span<const ErrorDetailValue> details,
                         std::string& output) {
    if (!valid_error_details(schema, details)) return false;
    const auto detail = [&](std::string_view name) -> const ErrorDetailValue* {
        const int index = error_detail_index(schema, name);
        return index < 0 ? nullptr : &details[static_cast<std::size_t>(index)];
    };
    const auto value = [&](std::string_view name) -> std::string_view {
        const auto* found = detail(name);
        return found && found->present ? found->text : std::string_view{};
    };
    const auto number = [&](std::string_view name) -> std::int64_t {
        const auto* found = detail(name);
        return found && found->present ? found->integer : 0;
    };
    std::string result;
    const auto file_failure = [&](std::string_view verb) {
        result = "cannot ";
        result += verb;
        const auto* path = detail("path");
        if (!path || !path->present) {
            result += " the file handle";
        } else {
            result += " \"";
            result += path->text;
            result += '"';
        }
        if (schema.code == ErrorValueCode::file_copy || schema.code == ErrorValueCode::file_move) {
            result += " to \"";
            result += value("destination");
            result += '"';
        }
        result += ": ";
        result += error_reason_text(value("reason"));
    };

    switch (schema.code) {
        case ErrorValueCode::file_read:
        case ErrorValueCode::file_write:
        case ErrorValueCode::file_seek:
        case ErrorValueCode::file_status:
        case ErrorValueCode::file_list:
        case ErrorValueCode::file_remove:
        case ErrorValueCode::file_mkdir:
        case ErrorValueCode::file_copy:
        case ErrorValueCode::file_move:
            file_failure(file_error_verb(schema.code));
            break;
        case ErrorValueCode::file_open:
            file_failure(file_error_verb(schema.code, value("mode")));
            break;
        case ErrorValueCode::numeric_parse:
            result = "cannot parse numeric input as ";
            result += value("type");
            if (value("reason") == "OUT_OF_RANGE") result += ": value out of range";
            break;
        case ErrorValueCode::bin_parse: result = "cannot parse bin input"; break;
        case ErrorValueCode::utf8_decode: result = "invalid UTF-8 text"; break;
        case ErrorValueCode::input_end: result = "scan reached the end of input"; break;
        case ErrorValueCode::input_read:
            result = "input failed: ";
            result += error_reason_text(value("reason"));
            break;
        case ErrorValueCode::input_format:
            if (value("reason") == "MISSING_TEXT") {
                // The format's literal as the format writes it, a quote
                // doubled.
                result = "scan expected \"";
                for (const char c : value("literal")) {
                    if (c == '"') result += '"';
                    result += c;
                }
                result += "\" in the input";
            } else if (value("reason") == "UNREADABLE_FIELD") {
                result = "scan could not read ";
                result += value("type");
                result += " from \"";
                result += value("input");
                result += '"';
            } else {
                result = "scan found unexpected input after the format: \"";
                result += value("input");
                result += '"';
            }
            break;
        case ErrorValueCode::output_write: result = "output failed"; break;
        case ErrorValueCode::numeric_conversion: {
            const int subject = spelling_index(conversion_subject_spellings, value("subject"));
            const int reason = spelling_index(conversion_reason_spellings, value("reason"));
            write_failure_message(
                conversion_failure_reason(static_cast<ConversionReason>(reason)),
                FailureArgs{.type = value("type"),
                            .subject = static_cast<ConversionSubject>(subject)},
                [&](std::string_view piece) { result += piece; });
            break;
        }
        case ErrorValueCode::json_parse:
            result = value("problem");
            result += " at byte ";
            result += std::to_string(number("offset"));
            break;
        case ErrorValueCode::json_value:
            result = "JSON value has incompatible kind";
            break;
        case ErrorValueCode::http_request:
            result = value("problem");
            break;
    }
    output = std::move(result);
    return true;
}

namespace detail {

constexpr bool error_value_codes_are_ordered() {
    for (std::size_t i = 0; i < error_value_codes.size(); ++i)
        if (static_cast<std::size_t>(error_value_codes[i].code) != i + 1) return false;
    return true;
}

constexpr bool error_details_are_named_members() {
    for (const auto& row : error_value_codes) {
        if (row.details.size() > max_error_details) return false;
        for (const auto& detail : row.details) {
            if (error_detail_name_index(detail.name) < 0) return false;
            if ((detail.kind == ErrorDetailKind::integer) != error_detail_is_integer(detail.name))
                return false;
            if (detail.kind == ErrorDetailKind::integer && detail.optional) return false;
        }
    }
    return true;
}

} // namespace detail

static_assert(detail::error_value_codes_are_ordered(),
              "error_value_codes is in the order of the schema numbers");
static_assert(detail::error_details_are_named_members(),
              "every detail is a member name of an error, of one kind in every schema");
static_assert(conversion_subject_spellings.size() == conversion_subjects.size());

} // namespace quidra::abi
