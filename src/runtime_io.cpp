#include "quidra/abi/io_status.hpp"
#include "quidra/abi/layout.hpp"
#include "quidra/abi/process_status.hpp"
#include "quidra/abi/runtime_entry_points.hpp"
#include "platform/environment.hpp"
#include "runtime_internal.hpp"
#include "runtime_report.hpp"

#include <algorithm>
#include <array>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <string>
#include <system_error>
#include <vector>

// The ABI this runtime shares with generated code (include/quidra/abi).
namespace abi = quidra::abi;

namespace {

// Why the calling thread's last file operation failed, as the reason's
// position in abi::file_reasons, written only on failure; the error block
// of the failed operation reads it (quidra_error_file).
enum FileReason : int {
    not_found, permission_denied, is_a_directory, not_a_directory, already_exists,
    invalid_utf8, embedded_nul, unaligned_bin, path_not_text, handle_closed, not_writable,
    io_failure
};
thread_local int last_file_reason = io_failure;

// Records `reason` and returns `result` (the failed operation's result).
template <class T>
T fail_with(FileReason reason, T result) {
    last_file_reason = reason;
    return result;
}

// The reason of an error the operating system reported, or -1.
int system_reason(const std::error_code& error) {
    if (error == std::errc::no_such_file_or_directory) return not_found;
    if (error == std::errc::permission_denied || error == std::errc::operation_not_permitted)
        return permission_denied;
    if (error == std::errc::is_a_directory) return is_a_directory;
    if (error == std::errc::not_a_directory) return not_a_directory;
    if (error == std::errc::file_exists) return already_exists;
    return -1;
}

// The reason a path operation failed: the error it reported (`error`, or
// errno as the failed open left it), else what the path is now: missing,
// or a directory where a file was wanted (`wants_directory` false) or the
// other way round.
FileReason path_reason(const char* path, std::error_code error, bool wants_directory = false) {
    if (const int reason = system_reason(error); reason >= 0) return static_cast<FileReason>(reason);
    if (!path) return io_failure;
    std::error_code status_error;
    const auto status = std::filesystem::status(path, status_error);
    if (const int reason = system_reason(status_error); reason >= 0)
        return static_cast<FileReason>(reason);
    if (status.type() == std::filesystem::file_type::not_found) return not_found;
    if (!wants_directory && status.type() == std::filesystem::file_type::directory)
        return is_a_directory;
    if (wants_directory && status.type() != std::filesystem::file_type::directory)
        return not_a_directory;
    return io_failure;
}

FileReason open_reason(const char* path, int saved_errno) {
    return path_reason(path, std::error_code(saved_errno, std::generic_category()));
}

// Bytes that are not Quidra text: a NUL, or else invalid UTF-8.
FileReason text_reason(const std::string& data) {
    return data.find('\0') != std::string::npos ? embedded_nul : invalid_utf8;
}

// The reason of a failed operation on a handle: closed, or not writable
// when it writes.
FileReason handle_reason(void* value, bool writes);

bool valid_text(const std::string& value) {
    return quidra_runtime_text_valid_bytes(
        value.data(), static_cast<unsigned long long>(value.size()));
}

char* copy_validated_text(const std::string& value) {
    return quidra_runtime_copy_validated_text_bytes(
        value.data(), static_cast<unsigned long long>(value.size()));
}

char* read_text_direct(const char* path) {
    std::error_code size_error;
    const auto file_bytes = std::filesystem::file_size(path, size_error);
    if (size_error ||
        file_bytes >
            static_cast<std::uintmax_t>(
                std::numeric_limits<std::streamsize>::max()) ||
        file_bytes >
            static_cast<std::uintmax_t>(
                std::numeric_limits<unsigned long long>::max())) {
        return nullptr;
    }

    std::ifstream in(path, std::ios::binary);
    if (!in) return nullptr;

    const auto size = static_cast<unsigned long long>(file_bytes);
    auto* result = quidra_runtime_allocate_text_buffer(size);
    if (!result) return nullptr;

    if (size != 0) {
        in.read(result, static_cast<std::streamsize>(size));
        if (in.gcount() != static_cast<std::streamsize>(size)) {
            quidra_managed_release(result, nullptr);
            return nullptr;
        }
    }

    // file_size() is only a hint: if the file grew after the query, use the
    // general streaming path instead of silently truncating it.
    char extra = 0;
    in.read(&extra, 1);
    if (in.gcount() != 0 || (!in.eof() && in.fail())) {
        quidra_managed_release(result, nullptr);
        return nullptr;
    }

    if (!quidra_runtime_commit_text_buffer(result, size)) {
        quidra_managed_release(result, nullptr);
        return nullptr;
    }
    return result;
}

bool read_stream_bytes(std::istream& in, std::string& data) {
    std::array<char, 64 * 1024> buffer{};
    while (true) {
        in.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
        const auto count = in.gcount();
        if (count > 0) {
            const auto size = static_cast<std::size_t>(count);
            if (size > std::numeric_limits<std::size_t>::max() - data.size())
                return false;
            data.append(buffer.data(), size);
        }
        if (in.eof()) return true;
        if (!in) return false;
    }
}

bool read_all_bytes(const char* path, std::string& data) {
    std::ifstream in(path, std::ios::binary);
    if (!in) return false;

    std::error_code size_error;
    const auto file_bytes = std::filesystem::file_size(path, size_error);
    if (!size_error &&
        file_bytes <= static_cast<std::uintmax_t>(
            std::numeric_limits<std::size_t>::max())) {
        data.reserve(static_cast<std::size_t>(file_bytes));
    }
    return read_stream_bytes(in, data);
}

enum class FileMode { Read, Create, Append };
enum class FileStreamDirection { None, Read, Write };

struct FileResource {
    std::fstream stream;
    std::mutex mutex;
    bool readable{};
    bool writable{};
    std::uint64_t stream_position{};
    bool stream_position_valid{};
    FileStreamDirection stream_direction{FileStreamDirection::None};
};

bool position_file_stream(
    FileResource& resource, std::uint64_t position,
    FileStreamDirection direction) {
    if (!resource.stream.is_open()) return false;
    if (resource.stream_position_valid &&
        resource.stream_position == position &&
        resource.stream_direction == direction) {
        return true;
    }

    // Switching away from output must publish buffered bytes before the
    // shared fstream is repositioned for a reader or another logical handle.
    if (resource.stream_direction == FileStreamDirection::Write) {
        resource.stream.flush();
        if (!resource.stream) {
            resource.stream.clear();
            resource.stream_position_valid = false;
            resource.stream_direction = FileStreamDirection::None;
            return false;
        }
    }

    resource.stream.clear();
    const auto offset = static_cast<std::streamoff>(position);
    if (direction == FileStreamDirection::Read)
        resource.stream.seekg(offset, std::ios::beg);
    else
        resource.stream.seekp(offset, std::ios::beg);
    if (!resource.stream) {
        resource.stream.clear();
        resource.stream_position_valid = false;
        resource.stream_direction = FileStreamDirection::None;
        return false;
    }
    resource.stream_position = position;
    resource.stream_position_valid = true;
    resource.stream_direction = direction;
    return true;
}

void advance_file_stream(
    FileResource& resource, std::uint64_t position,
    FileStreamDirection direction) {
    resource.stream_position = position;
    resource.stream_position_valid = true;
    resource.stream_direction = direction;
}

void invalidate_file_stream(FileResource& resource) {
    resource.stream_position_valid = false;
    resource.stream_direction = FileStreamDirection::None;
}

struct FileState {
    std::shared_ptr<FileResource> resource;
    std::uint64_t position{};
    bool closed{};
    // Reuse the host-side traversal buffer across read_line() calls. The
    // returned Quidra string is still an independent value, so this allocation
    // optimization is unobservable at the language level.
    std::string line_buffer;

    explicit FileState(std::shared_ptr<FileResource> source)
        : resource(std::move(source)) {}
};

struct FileHandle {
    std::unique_ptr<FileState> state;
};

FileHandle* file_handle_from_value(void* value) {
    if (!value) return nullptr;
    std::uintptr_t bits{};
    std::memcpy(&bits, value, sizeof(bits));
    return reinterpret_cast<FileHandle*>(bits);
}

void* make_file_handle(FileHandle* handle) {
    auto* value = quidra_managed_alloc(sizeof(std::uintptr_t));
    const auto bits = reinterpret_cast<std::uintptr_t>(handle);
    std::memcpy(value, &bits, sizeof(bits));
    return value;
}

void* make_bin_value(const std::string& data) {
    if (data.size() >
            static_cast<std::size_t>(
                std::numeric_limits<long long>::max() / 8) ||
        data.size() > std::numeric_limits<std::size_t>::max() - abi::bin_layout::payload_offset) {
        return nullptr;
    }
    auto* result = static_cast<unsigned char*>(
        quidra_managed_alloc(
            static_cast<unsigned long long>(abi::bin_layout::payload_offset + data.size())));
    const auto bit_count = static_cast<long long>(data.size() * 8);
    std::memcpy(result, &bit_count, sizeof(bit_count));
    if (!data.empty()) std::memcpy(result + abi::bin_layout::payload_offset, data.data(), data.size());
    return result;
}
}

void* file_open_mode_raw(const char* path, FileMode mode) {
    if (!path) return nullptr;
    if (!*path) return fail_with<void*>(not_found, nullptr);
    errno = 0;
    try {
        auto resource = std::make_shared<FileResource>();
        resource->readable = true;
        resource->writable = mode != FileMode::Read;

        if (mode == FileMode::Read) {
            resource->stream.open(path, std::ios::binary | std::ios::in);
        } else if (mode == FileMode::Create) {
            resource->stream.open(
                path, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
        } else {
            // Ensure the target exists, then reopen without std::ios::app so each
            // copied Handle can keep an independent logical position.
            {
                std::ofstream ensure(path, std::ios::binary | std::ios::app);
                if (!ensure) return fail_with<void*>(open_reason(path, errno), nullptr);
            }
            resource->stream.open(path, std::ios::binary | std::ios::in | std::ios::out);
        }
        if (!resource->stream) return fail_with<void*>(open_reason(path, errno), nullptr);
        if (std::error_code kind_error; std::filesystem::is_directory(path, kind_error))
            return fail_with<void*>(is_a_directory, nullptr);

        auto state = std::make_unique<FileState>(resource);
        if (mode == FileMode::Append) {
            std::error_code error;
            const auto size = std::filesystem::file_size(path, error);
            if (error || size > std::numeric_limits<std::uint64_t>::max())
                return fail_with<void*>(path_reason(path, error), nullptr);
            state->position = static_cast<std::uint64_t>(size);
        }
        auto* handle = new FileHandle{std::move(state)};
        return make_file_handle(handle);
    } catch (...) {
        return fail_with<void*>(io_failure, nullptr);
    }
}

extern "C" void* quidra_file_open_raw(const char* path) {
    return file_open_mode_raw(path, FileMode::Read);
}

extern "C" void* quidra_file_create_raw(const char* path) {
    return file_open_mode_raw(path, FileMode::Create);
}

extern "C" void* quidra_file_append_raw(const char* path) {
    return file_open_mode_raw(path, FileMode::Append);
}

namespace {

FileReason handle_reason(void* value, bool writes) {
    auto* handle = file_handle_from_value(value);
    if (!handle || !handle->state || handle->state->closed || !handle->state->resource)
        return handle_closed;
    if (writes && !handle->state->resource->writable) return not_writable;
    return io_failure;
}

} // namespace

extern "C" char* quidra_file_handle_read_raw(void* value) {
    auto* handle = file_handle_from_value(value);
    if (!handle || !handle->state || handle->state->closed ||
        !handle->state->resource) {
        return fail_with<char*>(handle_closed, nullptr);
    }
    const auto start = handle->state->position;
    if (start > static_cast<std::uint64_t>(
            std::numeric_limits<std::streamoff>::max())) {
        return nullptr;
    }
    if (!handle->state->resource->readable) return nullptr;
    auto& resource = *handle->state->resource;
    std::lock_guard<std::mutex> lock(resource.mutex);
    auto& stream = resource.stream;
    if (!position_file_stream(resource, start, FileStreamDirection::Read))
        return nullptr;

    std::string data;
    if (!read_stream_bytes(stream, data) ||
        data.size() > std::numeric_limits<std::uint64_t>::max() - start) {
        stream.clear();
        invalidate_file_stream(resource);
        return fail_with<char*>(io_failure, nullptr);
    }
    if (!valid_text(data)) {
        stream.clear();
        invalidate_file_stream(resource);
        return fail_with<char*>(text_reason(data), nullptr);
    }
    auto* result = copy_validated_text(data);
    if (!result) {
        stream.clear();
        invalidate_file_stream(resource);
        return nullptr;
    }
    handle->state->position =
        start + static_cast<std::uint64_t>(data.size());
    advance_file_stream(
        resource, handle->state->position, FileStreamDirection::Read);
    return result;
}

extern "C" int quidra_file_handle_read_line_raw(void* value, char** out) {
    if (!out) return abi::read_line_status::failed;
    *out = nullptr;
    auto* handle = file_handle_from_value(value);
    if (!handle || !handle->state || handle->state->closed ||
        !handle->state->resource || !handle->state->resource->readable)
        return fail_with(handle_closed, abi::read_line_status::failed);
    const auto start = handle->state->position;
    if (start > static_cast<std::uint64_t>(std::numeric_limits<std::streamoff>::max())) return abi::read_line_status::failed;

    auto& resource = *handle->state->resource;
    std::lock_guard<std::mutex> lock(resource.mutex);
    auto& stream = resource.stream;
    if (!position_file_stream(resource, start, FileStreamDirection::Read))
        return abi::read_line_status::failed;

    auto& line = handle->state->line_buffer;
    line.clear();
    if (!std::getline(stream, line)) {
        const bool eof = stream.eof();
        stream.clear();
        if (eof) {
            advance_file_stream(resource, start, FileStreamDirection::Read);
            return abi::read_line_status::end_of_input;
        }
        invalidate_file_stream(resource);
        return abi::read_line_status::failed;
    }

    const auto delimiter_bytes = stream.eof() ? 0ULL : 1ULL;
    if (line.size() > std::numeric_limits<std::uint64_t>::max() - delimiter_bytes ||
        start > std::numeric_limits<std::uint64_t>::max() -
                    static_cast<std::uint64_t>(line.size()) - delimiter_bytes) {
        stream.clear();
        invalidate_file_stream(resource);
        return fail_with(io_failure, abi::read_line_status::failed);
    }
    if (!valid_text(line)) {
        stream.clear();
        invalidate_file_stream(resource);
        return fail_with(text_reason(line), abi::read_line_status::failed);
    }
    auto* text = copy_validated_text(line);
    if (!text) {
        stream.clear();
        invalidate_file_stream(resource);
        return abi::read_line_status::failed;
    }
    handle->state->position =
        start + static_cast<std::uint64_t>(line.size()) + delimiter_bytes;
    advance_file_stream(
        resource, handle->state->position, FileStreamDirection::Read);
    *out = text;
    return abi::read_line_status::line;
}

extern "C" void* quidra_file_handle_read_bin_raw(void* value) {
    auto* handle = file_handle_from_value(value);
    if (!handle || !handle->state || handle->state->closed ||
        !handle->state->resource) {
        return fail_with<void*>(handle_closed, nullptr);
    }
    const auto start = handle->state->position;
    if (start > static_cast<std::uint64_t>(
            std::numeric_limits<std::streamoff>::max())) {
        return nullptr;
    }
    auto& resource = *handle->state->resource;
    std::lock_guard<std::mutex> lock(resource.mutex);
    auto& stream = resource.stream;
    if (!position_file_stream(resource, start, FileStreamDirection::Read))
        return nullptr;

    std::string data;
    if (!read_stream_bytes(stream, data) ||
        data.size() > std::numeric_limits<std::uint64_t>::max() - start) {
        stream.clear();
        invalidate_file_stream(resource);
        return nullptr;
    }
    auto* result = make_bin_value(data);
    if (!result) {
        stream.clear();
        invalidate_file_stream(resource);
        return nullptr;
    }
    handle->state->position =
        start + static_cast<std::uint64_t>(data.size());
    advance_file_stream(
        resource, handle->state->position, FileStreamDirection::Read);
    return result;
}

static bool quidra_file_handle_write_raw_unclassified(void* value, const char* text, bool line) {
    auto* handle = file_handle_from_value(value);
    if (!handle || !handle->state || handle->state->closed ||
        !handle->state->resource || !handle->state->resource->writable || !text) {
        return false;
    }
    const auto byte_count = quidra_runtime_text_byte_length(text);
    const auto extra = line ? 1ULL : 0ULL;
    if (byte_count > static_cast<unsigned long long>(std::numeric_limits<std::streamsize>::max()) ||
        byte_count > std::numeric_limits<std::uint64_t>::max() - extra ||
        handle->state->position > std::numeric_limits<std::uint64_t>::max() - byte_count - extra ||
        handle->state->position > static_cast<std::uint64_t>(std::numeric_limits<std::streamoff>::max())) {
        return false;
    }

    auto& resource = *handle->state->resource;
    std::lock_guard<std::mutex> lock(resource.mutex);
    auto& stream = resource.stream;
    if (!position_file_stream(
            resource, handle->state->position, FileStreamDirection::Write))
        return false;
    if (byte_count) stream.write(text, static_cast<std::streamsize>(byte_count));
    if (line) stream.put('\n');
    if (!stream) {
        stream.clear();
        invalidate_file_stream(resource);
        return false;
    }
    handle->state->position += byte_count + extra;
    advance_file_stream(
        resource, handle->state->position, FileStreamDirection::Write);
    return true;
}

static bool quidra_file_handle_flush_raw_unclassified(void* value) {
    auto* handle = file_handle_from_value(value);
    if (!handle || !handle->state || handle->state->closed ||
        !handle->state->resource || !handle->state->resource->writable) {
        return false;
    }
    auto& resource = *handle->state->resource;
    std::lock_guard<std::mutex> lock(resource.mutex);
    auto& stream = resource.stream;
    if (!stream.is_open()) return false;
    stream.flush();
    if (!stream) {
        stream.clear();
        invalidate_file_stream(resource);
        return false;
    }
    return true;
}

static bool quidra_file_handle_seek_raw_unclassified(void* value, long long position) {
    auto* handle = file_handle_from_value(value);
    if (!handle || !handle->state || handle->state->closed ||
        !handle->state->resource || position < 0) {
        return false;
    }
    const auto requested = static_cast<std::uint64_t>(position);
    if (requested > static_cast<std::uint64_t>(std::numeric_limits<std::streamoff>::max())) return false;

    auto& resource = *handle->state->resource;
    std::lock_guard<std::mutex> lock(resource.mutex);
    auto& stream = resource.stream;
    if (!stream.is_open()) return false;
    if (resource.writable) {
        stream.flush();
        if (!stream) {
            stream.clear();
            invalidate_file_stream(resource);
            return false;
        }
    }
    stream.clear();
    stream.seekg(0, std::ios::end);
    const auto end = stream.tellg();
    invalidate_file_stream(resource);
    if (end == std::streampos(-1) || end < std::streampos(0)) {
        stream.clear();
        return false;
    }
    const auto size = static_cast<std::uint64_t>(end - std::streampos(0));
    if (requested > size) return false;
    handle->state->position = requested;
    return true;
}

extern "C" void quidra_file_handle_close(void* value) {
    auto* handle = file_handle_from_value(value);
    if (!handle || !handle->state || handle->state->closed) return;
    // Release this value's ownership immediately. Other copied Handles keep
    // the shared opened resource alive and retain their own logical positions.
    handle->state->resource.reset();
    handle->state->closed = true;
}

extern "C" void* quidra_file_handle_clone(void* value) {
    try {
        auto* handle = file_handle_from_value(value);
        if (!handle || !handle->state) {
            quidra::runtime::report_uncoded("invalid file handle copy");
        }

        auto state = std::make_unique<FileState>(handle->state->resource);
        state->position = handle->state->position;
        state->closed = handle->state->closed;

        // Preserve the originally opened resource identity. The copied value
        // has its own logical position and close state.
        auto* copy = new FileHandle{std::move(state)};
        return make_file_handle(copy);
    } catch (...) {
        quidra::runtime::report_uncoded("allocation failed");
    }
}

extern "C" void quidra_file_handle_drop(void* value) {
    if (!value) return;
    auto* handle = file_handle_from_value(value);
    std::uintptr_t zero{};
    std::memcpy(value, &zero, sizeof(zero));
    delete handle;
}

extern "C" char* quidra_file_read_raw(const char* path) {
    if (!path) return nullptr;
    if (auto* direct = read_text_direct(path)) return direct;
    std::string data;
    errno = 0;
    if (!read_all_bytes(path, data)) return fail_with<char*>(open_reason(path, errno), nullptr);
    // A directory is not a file (some systems open and read one as empty).
    if (std::error_code kind_error; data.empty() && std::filesystem::is_directory(path, kind_error))
        return fail_with<char*>(is_a_directory, nullptr);
    auto* text = quidra_runtime_try_copy_text_bytes(
        data.data(), static_cast<unsigned long long>(data.size()));
    if (!text) return fail_with<char*>(text_reason(data), nullptr);
    return text;
}

extern "C" void* quidra_file_read_bin_raw(const char* path) {
    if (!path) return nullptr;
    std::string data;
    errno = 0;
    if (!read_all_bytes(path, data)) return fail_with<void*>(open_reason(path, errno), nullptr);
    if (std::error_code kind_error; data.empty() && std::filesystem::is_directory(path, kind_error))
        return fail_with<void*>(is_a_directory, nullptr);
    auto* value = make_bin_value(data);
    if (!value) return fail_with<void*>(io_failure, nullptr);
    return value;
}

extern "C" bool quidra_file_write_raw(const char* path,const char* text) {
    if(!path||!text) return false;
    const auto byte_count = quidra_runtime_text_byte_length(text);
    if (byte_count >
        static_cast<unsigned long long>(std::numeric_limits<std::streamsize>::max()))
        return false;
    errno = 0;
    std::ofstream out(path,std::ios::binary|std::ios::trunc);
    if(!out) return fail_with(open_reason(path,errno),false);
    if(byte_count)
        out.write(text,static_cast<std::streamsize>(byte_count));
    out.close();
    if(!out) return fail_with(io_failure,false);
    return true;
}

extern "C" bool quidra_file_write_bin_raw(const char* path,const void* bin_raw) {
    if(!path||!bin_raw) return false;
    long long bit_count=0;
    std::memcpy(&bit_count,bin_raw,sizeof(bit_count));
    if(bit_count<0 || bit_count%8!=0) return fail_with(unaligned_bin,false);
    const auto byte_count=static_cast<unsigned long long>(bit_count/8);
    const auto size=static_cast<std::size_t>(byte_count);
    if(static_cast<unsigned long long>(size)!=byte_count ||
       size>static_cast<std::size_t>(std::numeric_limits<std::streamsize>::max())) return false;
    errno = 0;
    std::ofstream out(path,std::ios::binary|std::ios::trunc);
    if(!out) return fail_with(open_reason(path,errno),false);
    if(size) out.write(static_cast<const char*>(bin_raw)+abi::bin_layout::payload_offset,static_cast<std::streamsize>(size));
    out.close();
    if(!out) return fail_with(io_failure,false);
    return true;
}

extern "C" int quidra_file_exists_raw(const char* path) {
    if(!path) return abi::path_query_status::failed;
    std::error_code error;
    const bool result=std::filesystem::exists(path,error);
    if(error) return fail_with(path_reason(path,error,true),abi::path_query_status::failed);
    return result?abi::path_query_status::yes:abi::path_query_status::no;
}
extern "C" int quidra_file_is_directory_raw(const char* path) {
    if(!path) return abi::path_query_status::failed;
    std::error_code error;
    const bool exists=std::filesystem::exists(path,error);
    if(error) return fail_with(path_reason(path,error,true),abi::path_query_status::failed);
    if(!exists) return abi::path_query_status::no;
    const bool result=std::filesystem::is_directory(path,error);
    if(error) return fail_with(path_reason(path,error,true),abi::path_query_status::failed);
    return result?abi::path_query_status::yes:abi::path_query_status::no;
}
extern "C" bool quidra_file_remove_raw(const char* path) {
    if(!path) return false;
    std::error_code error;
    if(std::filesystem::remove(path,error)&&!error) return true;
    return fail_with(error?path_reason(path,error,true):not_found,false);
}
extern "C" bool quidra_file_copy_raw(const char* source,const char* destination) {
    if(!source||!destination) return false;
    std::error_code error;
    if(std::filesystem::copy_file(
           source,destination,std::filesystem::copy_options::overwrite_existing,error)&&!error)
        return true;
    return fail_with(path_reason(source,error),false);
}
extern "C" bool quidra_file_move_raw(const char* source,const char* destination) {
    if(!source||!destination) return false;
    std::error_code error;
    std::filesystem::rename(source,destination,error);
    if(!error) return true;
    return fail_with(path_reason(source,error,true),false);
}
extern "C" bool quidra_file_mkdir_raw(const char* path) {
    if(!path) return false;
    std::error_code error;
    if(std::filesystem::create_directory(path,error)&&!error) return true;
    return fail_with(error?path_reason(path,error,true):already_exists,false);
}

extern "C" void* quidra_file_list_raw(const char* path,bool recursive) {
    if(!path) return nullptr;
    std::error_code error;
    std::vector<std::string> entries;
    auto append=[&](const std::filesystem::path& entry){
        try{
            const auto encoded=entry.u8string();
            std::string text(reinterpret_cast<const char*>(encoded.data()),encoded.size());
            if(!valid_text(text)) return fail_with(path_not_text,false);
            entries.push_back(std::move(text));
            return true;
        }catch(const std::system_error&){return fail_with(path_not_text,false);}
    };
    if(recursive){
        std::filesystem::recursive_directory_iterator current(path,error);
        if(error) return fail_with<void*>(path_reason(path,error,true),nullptr);
        const std::filesystem::recursive_directory_iterator end;
        while(current!=end){
            if(!append(current->path())) return nullptr;
            current.increment(error);
            if(error) return fail_with<void*>(path_reason(path,error,true),nullptr);
        }
    }else{
        std::filesystem::directory_iterator current(path,error);
        if(error) return fail_with<void*>(path_reason(path,error,true),nullptr);
        const std::filesystem::directory_iterator end;
        while(current!=end){
            if(!append(current->path())) return nullptr;
            current.increment(error);
            if(error) return fail_with<void*>(path_reason(path,error,true),nullptr);
        }
    }
    std::sort(entries.begin(),entries.end());
    if(entries.size()>(std::numeric_limits<std::size_t>::max()-abi::array_layout::payload_offset)/sizeof(char*)) return nullptr;
    const auto bytes=abi::array_layout::payload_offset+entries.size()*sizeof(char*);
    auto* result=static_cast<unsigned char*>(
        quidra_managed_alloc(static_cast<unsigned long long>(bytes)));
    const auto count=static_cast<long long>(entries.size());
    std::memcpy(result,&count,sizeof(count));
    for(std::size_t i=0;i<entries.size();++i){
        auto* item=copy_validated_text(entries[i]);
        std::memcpy(result+abi::array_layout::payload_offset+i*sizeof(char*),&item,sizeof(item));
    }
    return result;
}

// --- classified entry points
extern "C" bool quidra_file_handle_seek_raw(void* value, long long position) {
    errno = 0;
    const auto result = quidra_file_handle_seek_raw_unclassified(value, position);
    if (!result) last_file_reason = handle_reason(value, false);
    return result;
}

extern "C" bool quidra_file_handle_flush_raw(void* value) {
    errno = 0;
    const auto result = quidra_file_handle_flush_raw_unclassified(value);
    if (!result) last_file_reason = handle_reason(value, true);
    return result;
}

extern "C" bool quidra_file_handle_write_raw(void* value, const char* text, bool line) {
    errno = 0;
    const auto result = quidra_file_handle_write_raw_unclassified(value, text, line);
    if (!result) last_file_reason = handle_reason(value, true);
    return result;
}


// The error of the calling thread's last failed file operation: `code` (an
// abi::ErrorValueCode), FILE_OPEN's mode (its position in
// abi::file_open_modes), the path and the destination the program passed
// (null: absent), and the reason the operation recorded.
extern "C" void* quidra_error_file(int code, int mode, const char* path, const char* destination,
                                   unsigned long long line, unsigned long long column) {
    const auto value = static_cast<abi::ErrorValueCode>(code);
    const auto text = [](const void* pointer) {
        return static_cast<std::uint64_t>(reinterpret_cast<std::uintptr_t>(pointer));
    };
    const auto reason = text(abi::file_reasons[static_cast<std::size_t>(
        last_file_reason >= 0 && last_file_reason < static_cast<int>(abi::file_reasons.size())
            ? last_file_reason : io_failure)].data());
    std::uint64_t slots[abi::max_error_details]{};
    if (value == abi::ErrorValueCode::file_open) {
        slots[0] = text(path);
        slots[1] = text(abi::file_open_modes[static_cast<std::size_t>(
            mode >= 0 && mode < static_cast<int>(abi::file_open_modes.size()) ? mode : 0)].data());
        slots[2] = reason;
    } else if (value == abi::ErrorValueCode::file_copy || value == abi::ErrorValueCode::file_move) {
        slots[0] = text(path);
        slots[1] = text(destination);
        slots[2] = reason;
    } else {
        slots[0] = text(path);
        slots[1] = reason;
    }
    return quidra::runtime::make_error_record(value, slots, line, column, true);
}

extern "C" char* quidra_environment_get(const char* name) {
    if(!name) return nullptr;
    const auto text=quidra::platform::environment_value(name);
    if(!text) return nullptr;
    if(!valid_text(*text)) {
        quidra_runtime_text_error(
            "environment value must be valid UTF-8 text without NUL");
    }
    return copy_validated_text(*text);
}

extern "C" bool quidra_environment_has(const char* name) {
    if(!name) return false;
    return quidra::platform::environment_has(name);
}
