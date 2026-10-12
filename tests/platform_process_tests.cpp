#include "platform/process.hpp"
#include "platform/temporary_directory.hpp"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#else
#include <cerrno>
#include <unistd.h>
#endif

namespace fs = std::filesystem;
using quidra::platform::native_text;
using quidra::platform::run_native_program;

namespace {

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

void write_bytes(const fs::path& path, std::string_view bytes) {
    std::ofstream out(path, std::ios::binary);
    out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    require(static_cast<bool>(out), "cannot write process test input");
}

std::string read_bytes(const fs::path& path) {
    std::ifstream in(path, std::ios::binary);
    require(static_cast<bool>(in), "cannot read process test output");
    return std::string(std::istreambuf_iterator<char>(in), {});
}

int copy_standard_input() {
#ifdef _WIN32
    _setmode(_fileno(stdin), _O_BINARY);
    _setmode(_fileno(stdout), _O_BINARY);
    _setmode(_fileno(stderr), _O_BINARY);
#endif
    char buffer[4096];
    while (const auto size = std::fread(buffer, 1, sizeof(buffer), stdin)) {
        if (std::fwrite(buffer, 1, size, stdout) != size) return 2;
    }
    if (std::ferror(stdin)) return 3;
    std::fputs("child stderr\n", stderr);
    return 37;
}

void test_redirects(const fs::path& program, const fs::path& root) {
    const auto input = root / "input bytes.bin";
    const auto output = root / "output bytes.bin";
    const auto error = root / "error bytes.txt";
    constexpr char bytes[] = "first line\nsecond\0line\n";
    const std::string payload(bytes, sizeof(bytes) - 1);
    write_bytes(input, payload);
    write_bytes(output, "stale stdout");
    write_bytes(error, "stale stderr");

    require(run_native_program(program, {native_text("--copy")}, output, error, input) == 37,
            "stdin redirection changed the child's exit status");
    require(read_bytes(output) == payload, "redirected stdin bytes did not reach stdout");
    require(read_bytes(error) == "child stderr\n", "stdin redirection changed stderr capture");
    require(read_bytes(input) == payload, "stdin redirection modified its input file");

    // The original four-argument API inherits the redirected input of its
    // parent while still handling stdout and stderr redirection itself.
    require(run_native_program(program,
                {native_text("--forward"), output.native(), error.native()},
                std::nullopt, std::nullopt, input) == 37,
            "the four-argument API changed the child's exit status");
    require(read_bytes(output) == payload, "the four-argument API lost inherited stdin");
    require(read_bytes(error) == "child stderr\n", "the four-argument API changed stderr capture");
    require(run_native_program(program, {native_text("--quiet")}) == 19,
            "the default process API changed the child's exit status");

#ifndef _WIN32
    // When stdin was already closed, open() can return descriptor zero.
    // Redirecting that descriptor must leave the child's new stdin open.
    const int saved_input = ::dup(STDIN_FILENO);
    require(saved_input >= 0 || errno == EBADF, "cannot save process test stdin");
    ::close(STDIN_FILENO);
    const auto restore_input = [&] {
        if (saved_input >= 0) {
            require(::dup2(saved_input, STDIN_FILENO) >= 0, "cannot restore process test stdin");
            ::close(saved_input);
        }
    };
    int status;
    try {
        status = run_native_program(program, {native_text("--copy")}, output, error, input);
    } catch (...) {
        restore_input();
        throw;
    }
    restore_input();
    require(status == 37, "closed parent stdin prevented input redirection");
    require(read_bytes(output) == payload, "redirected descriptor zero was closed before exec");
#endif

    // The parent must release its redirected input handle when the child
    // exits; Windows denies this removal while a non-delete-shared handle lives.
    require(fs::remove(input), "the process runner retained its input handle");
}

void test_missing_files(const fs::path& program, const fs::path& root) {
    const auto input = root / "missing input";
#ifdef _WIN32
    bool rejected = false;
    try {
        (void)run_native_program(program, {native_text("--quiet")}, std::nullopt, std::nullopt, input);
    } catch (const std::runtime_error& error) {
        rejected = std::string_view(error.what()) == "cannot open process stdin file";
    }
    require(rejected, "missing stdin did not report an input-open failure");
#else
    require(run_native_program(program, {native_text("--quiet")}, std::nullopt, std::nullopt, input) == 126,
            "missing stdin did not preserve the redirection failure status");
#endif
    require(!fs::exists(input), "stdin redirection created its missing input file");

    write_bytes(input, "input stays readable");
    const auto invalid_output = root / "missing directory" / "output";
#ifdef _WIN32
    rejected = false;
    try {
        (void)run_native_program(program, {native_text("--quiet")}, invalid_output, std::nullopt, input);
    } catch (const std::runtime_error& error) {
        rejected = std::string_view(error.what()) == "cannot open process stdout file";
    }
    require(rejected, "stdout-open failure changed when stdin was redirected");
#else
    require(run_native_program(program, {native_text("--quiet")}, invalid_output, std::nullopt, input) == 126,
            "stdout-open failure changed when stdin was redirected");
#endif
    require(fs::remove(input), "a redirect failure retained the input handle");
}

} // namespace

int main(int argc, char** argv) {
    if (argc == 2 && std::string_view(argv[1]) == "--copy") return copy_standard_input();
    if (argc == 2 && std::string_view(argv[1]) == "--quiet") return 19;
    if (argc == 4 && std::string_view(argv[1]) == "--forward")
        return run_native_program(fs::absolute(argv[0]), {native_text("--copy")},
                                  fs::path(argv[2]), fs::path(argv[3]));
    try {
        const quidra::platform::TemporaryDirectory root(
            "quidra process tests ", "cannot create process test directory");
        const auto program = fs::absolute(argv[0]);
        test_redirects(program, root.path());
        test_missing_files(program, root.path());
    } catch (const std::exception& error) {
        std::fprintf(stderr, "process test failed: %s\n", error.what());
        return 1;
    }
    std::puts("process redirection tests passed");
    return 0;
}
