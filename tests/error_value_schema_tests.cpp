#include "quidra/abi/error_record.hpp"
#include <cstdio>
#include <cstdlib>

// Keep schema checks and their observable calls active under NDEBUG.
#define CHECK(condition) do { \
    if (!(condition)) { \
        std::fprintf(stderr, "error schema check failed at %s:%d: %s\n", \
                     __FILE__, __LINE__, #condition); \
        std::abort(); \
    } \
} while (false)
#include <array>
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

using namespace quidra::abi;

namespace {

const ErrorValueCodeInfo& schema_of(ErrorValueCode code) {
    return *error_value_schema(static_cast<std::uint32_t>(code));
}

std::string rendered(ErrorValueCode code, std::vector<ErrorDetailValue> details) {
    std::string message = "<not rendered>";
    CHECK(render_error(schema_of(code), details, message));
    return message;
}

// The rendering of every file code with every reason and with a path and
// without one (a file.Handle operation), against the verbs and reason texts
// of the error table.
void check_file_renderings() {
    const std::array<std::pair<ErrorValueCode, std::string_view>, 7> verbs{{
        {ErrorValueCode::file_read, "read"},
        {ErrorValueCode::file_write, "write"},
        {ErrorValueCode::file_seek, "seek in"},
        {ErrorValueCode::file_status, "inspect"},
        {ErrorValueCode::file_list, "list"},
        {ErrorValueCode::file_remove, "remove"},
        {ErrorValueCode::file_mkdir, "create directory"},
    }};
    const std::array<std::pair<std::string_view, std::string_view>, 12> reasons{{
        {"NOT_FOUND", "file not found"},
        {"PERMISSION_DENIED", "permission denied"},
        {"IS_A_DIRECTORY", "path is a directory"},
        {"NOT_A_DIRECTORY", "path is not a directory"},
        {"ALREADY_EXISTS", "path already exists"},
        {"INVALID_UTF8", "invalid UTF-8 text"},
        {"EMBEDDED_NUL", "text contains a NUL character"},
        {"UNALIGNED_BIN", "bin length is not a multiple of 8"},
        {"PATH_NOT_TEXT", "path is not valid text"},
        {"HANDLE_CLOSED", "handle is closed"},
        {"NOT_WRITABLE", "handle is not writable"},
        {"IO_FAILURE", "I/O failure"},
    }};
    CHECK(reasons.size() == file_reasons.size());
    for (std::size_t i = 0; i < reasons.size(); ++i) CHECK(file_reasons[i] == reasons[i].first);
    for (const auto& [code, verb] : verbs) {
        for (const auto& [reason, text] : reasons) {
            CHECK(rendered(code, {ErrorDetailValue::text_value("data.csv"),
                                  ErrorDetailValue::name_value(reason)}) ==
                  "cannot " + std::string(verb) + " \"data.csv\": " + std::string(text));
            CHECK(rendered(code, {ErrorDetailValue::absent(ErrorDetailKind::text),
                                  ErrorDetailValue::name_value(reason)}) ==
                  "cannot " + std::string(verb) + " the file handle: " + std::string(text));
        }
    }
    // An empty path is a path: it is shown, never taken for a handle.
    CHECK(rendered(ErrorValueCode::file_read, {ErrorDetailValue::text_value(""),
                                               ErrorDetailValue::name_value("NOT_FOUND")}) ==
          "cannot read \"\": file not found");
    const std::array<std::pair<std::string_view, std::string_view>, 3> modes{{
        {"READ", "open"}, {"CREATE", "create"}, {"APPEND", "open for appending"}}};
    for (const auto& [mode, verb] : modes)
        CHECK(rendered(ErrorValueCode::file_open,
                       {ErrorDetailValue::text_value("log.txt"), ErrorDetailValue::name_value(mode),
                        ErrorDetailValue::name_value("PERMISSION_DENIED")}) ==
              "cannot " + std::string(verb) + " \"log.txt\": permission denied");
    CHECK(rendered(ErrorValueCode::file_copy,
                   {ErrorDetailValue::text_value("a"), ErrorDetailValue::text_value("b"),
                    ErrorDetailValue::name_value("ALREADY_EXISTS")}) ==
          "cannot copy \"a\" to \"b\": path already exists");
    CHECK(rendered(ErrorValueCode::file_move,
                   {ErrorDetailValue::text_value("a"), ErrorDetailValue::text_value("b"),
                    ErrorDetailValue::name_value("NOT_FOUND")}) ==
          "cannot move \"a\" to \"b\": file not found");
}

// The other codes, every reason of their closed lists.
void check_other_renderings() {
    for (const auto reason : parse_reasons) {
        CHECK(rendered(ErrorValueCode::numeric_parse, {ErrorDetailValue::name_value("int8"),
                                                       ErrorDetailValue::name_value(reason)}) ==
              (reason == "OUT_OF_RANGE" ? "cannot parse numeric input as int8: value out of range"
                                        : "cannot parse numeric input as int8"));
    }
    CHECK(rendered(ErrorValueCode::bin_parse, {}) == "cannot parse bin input");
    CHECK(rendered(ErrorValueCode::utf8_decode, {}) == "invalid UTF-8 text");
    CHECK(rendered(ErrorValueCode::input_end, {}) == "scan reached the end of input");
    const std::array<std::string_view, 3> input_texts{
        "input failed: invalid UTF-8 text", "input failed: text contains a NUL character",
        "input failed: I/O failure"};
    for (std::size_t i = 0; i < input_read_reasons.size(); ++i)
        CHECK(rendered(ErrorValueCode::input_read,
                       {ErrorDetailValue::name_value(input_read_reasons[i])}) == input_texts[i]);
    const auto absent_text = ErrorDetailValue::absent(ErrorDetailKind::text);
    const auto absent_name = ErrorDetailValue::absent(ErrorDetailKind::name);
    CHECK(rendered(ErrorValueCode::input_format,
                   {ErrorDetailValue::name_value("MISSING_TEXT"), ErrorDetailValue::text_value("a\"b"),
                    absent_name, absent_text}) == "scan expected \"a\"\"b\" in the input");
    CHECK(rendered(ErrorValueCode::input_format,
                   {ErrorDetailValue::name_value("UNREADABLE_FIELD"), absent_text,
                    ErrorDetailValue::name_value("int"), ErrorDetailValue::text_value("x")}) ==
          "scan could not read int from \"x\"");
    CHECK(rendered(ErrorValueCode::input_format,
                   {ErrorDetailValue::name_value("TRAILING_INPUT"), absent_text, absent_name,
                    ErrorDetailValue::text_value("rest")}) ==
          "scan found unexpected input after the format: \"rest\"");
    CHECK(rendered(ErrorValueCode::output_write, {}) == "output failed");
    // NUMERIC_CONVERSION is the runtime failure table's template, for every
    // subject and reason.
    for (std::size_t s = 0; s < conversion_subject_spellings.size(); ++s) {
        for (std::size_t r = 0; r < conversion_reason_spellings.size(); ++r) {
            const auto expected = format(
                conversion_failure_reason(static_cast<ConversionReason>(r)),
                FailureArgs{.type = "nat8", .subject = static_cast<ConversionSubject>(s)});
            CHECK(rendered(ErrorValueCode::numeric_conversion,
                           {ErrorDetailValue::name_value("nat8"),
                            ErrorDetailValue::name_value(conversion_subject_spellings[s]),
                            ErrorDetailValue::name_value(conversion_reason_spellings[r])}) ==
                  expected);
        }
    }
    CHECK(rendered(ErrorValueCode::numeric_conversion,
                   {ErrorDetailValue::name_value("int8"), ErrorDetailValue::name_value("VALUE"),
                    ErrorDetailValue::name_value("OUT_OF_RANGE")}) ==
          "numeric conversion out of range: value cannot be represented as int8");
    CHECK(rendered(ErrorValueCode::json_parse, {ErrorDetailValue::text_value("expected JSON value"),
                                                ErrorDetailValue::integer_value(17)}) ==
          "expected JSON value at byte 17");
    CHECK(rendered(ErrorValueCode::json_value, {}) == "JSON value has incompatible kind");
    CHECK(rendered(ErrorValueCode::http_request, {ErrorDetailValue::text_value("timed out")}) ==
          "timed out");
}

} // namespace

int main() {
    CHECK(error_value_schema(0) == nullptr);
    CHECK(error_value_schema(22) == nullptr);
    for (std::uint32_t i = 1; i <= error_value_codes.size(); ++i) {
        const auto* schema = error_value_schema(i);
        CHECK(schema != nullptr);
        CHECK(static_cast<std::uint32_t>(schema->code) == i);
        CHECK(is_core_error_code(schema->spelling));
        CHECK(schema->details.size() <= max_error_details);
        for (std::size_t j = 0; j < schema->details.size(); ++j) {
            const auto& detail = schema->details[j];
            CHECK(!detail.name.empty());
            CHECK(detail.identity);
            CHECK(error_detail_name_index(detail.name) >= 0);
            if (detail.kind == ErrorDetailKind::integer) CHECK(!detail.optional);
            if (detail.kind != ErrorDetailKind::name) CHECK(detail.values.empty());
            for (std::size_t k = j + 1; k < schema->details.size(); ++k)
                CHECK(detail.name != schema->details[k].name);
        }
    }
    // The record header and its slots.
    CHECK(sizeof(ErrorRecord) == 56);
    CHECK(error_slot_offset(0) == 56 && error_slot_offset(1) == 64 && error_slot_offset(3) == 80);
    CHECK(error_record_size(2) == 72);

    const auto& file = schema_of(ErrorValueCode::file_read);
    CHECK(file.details.size() == 2);
    CHECK(file.details[0].name == "path" && file.details[0].optional);
    CHECK(file.details[1].name == "reason" && !file.details[1].optional);
    CHECK(schema_of(ErrorValueCode::json_parse).details[1].kind == ErrorDetailKind::integer);
    CHECK(valid_user_error_code("A"));
    CHECK(valid_user_error_code("A9_B2"));
    CHECK(!valid_user_error_code("9A"));
    CHECK(!valid_user_error_code("A__B"));
    CHECK(!valid_user_error_code("A_"));
    CHECK(!valid_user_error_code("_A"));
    CHECK(!valid_user_error_code("a_B"));
    CHECK(valid_user_error_code(std::string(200, 'A')));
    CHECK(is_core_error_code("INDEX_BOUNDS"));
    CHECK(is_core_error_code("ERROR"));
    CHECK(!is_core_error_code("UNHANDLED_ERROR"));
    CHECK(!valid_custom_error_code("INDEX_BOUNDS"));
    CHECK(!valid_custom_error_code("NN", "NN"));
    CHECK(valid_custom_error_code("NN_SHAPE", "NN"));
    CHECK(!valid_custom_error_code("MATH_SHAPE", "NN"));
    CHECK(package_error_code_prefix("nn") == "NN");
    CHECK(package_error_code_prefix("my-pkg.v2") == "MY_PKG_V2");

    check_file_renderings();
    check_other_renderings();

    // Details that do not fit leave the output unchanged: a name given as a
    // text, and a name outside its code's closed list.
    std::string message = "untouched";
    const std::array<ErrorDetailValue, 2> invalid_kind{ErrorDetailValue::text_value("data.csv"),
                                                       ErrorDetailValue::text_value("NOT_FOUND")};
    CHECK(!render_error(file, invalid_kind, message));
    const std::array<ErrorDetailValue, 2> unknown_reason{ErrorDetailValue::text_value("data.csv"),
                                                         ErrorDetailValue::name_value("GONE")};
    CHECK(!render_error(file, unknown_reason, message));
    CHECK(message == "untouched");

    // Identity: the code, the details and the cause chain.
    const std::array<ErrorDetailValue, 1> left_text{ErrorDetailValue::text_value("failure")};
    const std::array<ErrorDetailValue, 1> other_text{ErrorDetailValue::text_value("different")};
    const ErrorValueIdentity cause{"CAUSE", left_text, nullptr};
    const ErrorValueIdentity first{"DATASET_LOAD", left_text, &cause};
    const ErrorValueIdentity equal{"DATASET_LOAD", left_text, &cause};
    const ErrorValueIdentity unequal{"DATASET_LOAD", other_text, &cause};
    const ErrorValueIdentity no_cause{"DATASET_LOAD", left_text, nullptr};
    CHECK(same_error_identity(first, equal));
    CHECK(!same_error_identity(first, unequal));
    CHECK(!same_error_identity(first, no_cause));
    const std::array<ErrorDetailValue, 2> read_a{ErrorDetailValue::text_value("a"),
                                                 ErrorDetailValue::name_value("NOT_FOUND")};
    const std::array<ErrorDetailValue, 2> read_b{ErrorDetailValue::text_value("b"),
                                                 ErrorDetailValue::name_value("NOT_FOUND")};
    CHECK(!same_error_identity({"FILE_READ", read_a, nullptr, file.details},
                               {"FILE_READ", read_b, nullptr, file.details}));
    // A detail its code's schema excludes from identity (a synthetic row; no
    // Core code excludes one) is left out: two errors that differ only there
    // are equal, and they still differ where an identity detail differs.
    const std::array<ErrorDetailSchema, 2> synthetic{
        ErrorDetailSchema{"path", ErrorDetailKind::text, true, false},
        ErrorDetailSchema{"offset", ErrorDetailKind::integer, false, false}};
    const std::array<ErrorDetailValue, 2> at_1{ErrorDetailValue::text_value("p"),
                                               ErrorDetailValue::integer_value(1)};
    const std::array<ErrorDetailValue, 2> at_2{ErrorDetailValue::text_value("p"),
                                               ErrorDetailValue::integer_value(2)};
    const std::array<ErrorDetailValue, 2> other_at_1{ErrorDetailValue::text_value("q"),
                                                     ErrorDetailValue::integer_value(1)};
    CHECK(same_error_identity({"SYNTHETIC", at_1, nullptr, synthetic},
                              {"SYNTHETIC", at_2, nullptr, synthetic}));
    CHECK(!same_error_identity({"SYNTHETIC", at_1, nullptr, synthetic},
                               {"SYNTHETIC", other_at_1, nullptr, synthetic}));
    CHECK(!same_error_identity({"SYNTHETIC", at_1, nullptr, {}}, {"SYNTHETIC", at_2, nullptr, {}}));
}
