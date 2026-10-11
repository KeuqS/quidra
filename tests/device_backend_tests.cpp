#include "device_backend.hpp"
#include "deferred_node.hpp"
#include "node_failure.hpp"
#include <atomic>
#include <cassert>
#include <new>
#include "unified_storage.hpp"
#include "quidra/abi/half_format.hpp"
#include "quidra/abi/dtype.hpp"
#include "quidra/abi/complex_format.hpp"
#include "quidra/abi/tensor_codes.hpp"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#ifndef _WIN32
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace {
std::atomic<long> allocations_before_failure{-1};
std::atomic<bool> reject_all_allocations{};
}
void* operator new(std::size_t bytes) {
    if(reject_all_allocations.load(std::memory_order_relaxed))throw std::bad_alloc{};
    const auto remaining=allocations_before_failure.load(std::memory_order_relaxed);
    if(remaining>=0) {
        if(allocations_before_failure.fetch_sub(1,std::memory_order_relaxed)==0) {
            allocations_before_failure=-1;throw std::bad_alloc{};
        }
    }
    if(void* memory=std::malloc(bytes?bytes:1))return memory;
    throw std::bad_alloc{};
}
void* operator new[](std::size_t bytes) {return ::operator new(bytes);}
void operator delete(void* memory) noexcept {std::free(memory);}
void operator delete[](void* memory) noexcept {std::free(memory);}
void operator delete(void* memory,std::size_t) noexcept {std::free(memory);}
void operator delete[](void* memory,std::size_t) noexcept {std::free(memory);}

namespace {

using quidra::device::Backend;
using quidra::device::Buffer;

using BufferPtr = std::unique_ptr<Buffer, void(*)(Buffer*)>;

[[noreturn]] void fail(const std::string& message) {
    std::cerr << "device backend test failure: " << message << '\n';
    std::exit(1);
}

void require(bool condition, const std::string& message) {
    if (!condition) fail(message);
}

BufferPtr buffer(int device, std::size_t bytes, std::string& error) {
    return BufferPtr(
        quidra::device::allocate(device, bytes, error),
        [](Buffer* value) { quidra::device::release(value); });
}

template <typename T>
void upload(Buffer* target, const std::vector<T>& values, std::string& error) {
    require(
        quidra::device::copy_from_host(
            target, 0, values.data(), values.size() * sizeof(T), error),
        error);
}

template <typename T>
std::vector<T> download(const Buffer* source, std::size_t count, std::string& error);

int wrapped_releases = 0;

void count_wrapped_release(void* pointer, std::size_t) {
    ++wrapped_releases;
    std::free(pointer);
}

// HostBytes replaces std::vector<unsigned char> as tensor host storage, so it
// must keep vector semantics, and its view/adopt/release modes must never
// free memory they do not own.
void test_host_bytes() {
    using quidra::unified::HostBytes;
    HostBytes bytes;
    require(bytes.empty() && bytes.data() == nullptr, "empty HostBytes");
    bytes.resize(5);
    require(bytes.size() == 5 && bytes.owns(), "HostBytes resize");
    for (std::size_t i = 0; i < bytes.size(); ++i)
        require(bytes[i] == 0, "HostBytes zero fill");
    bytes[0] = 7;
    bytes[4] = 9;
    bytes.resize(9);
    require(bytes[0] == 7 && bytes[4] == 9 && bytes[8] == 0,
            "HostBytes grow keeps the prefix and zero-fills the tail");
    bytes.resize(2);
    require(bytes.size() == 2 && bytes[0] == 7, "HostBytes shrink");

    HostBytes moved(std::move(bytes));
    require(bytes.empty() && moved.size() == 2 && moved[0] == 7, "HostBytes move");

    unsigned char external[4] = {1, 2, 3, 4};
    HostBytes view;
    view.view(external, sizeof(external));
    require(!view.owns() && view.data() == external && view[3] == 4, "HostBytes view");
    view = HostBytes{}; // must not free `external`

    std::size_t capacity = 0;
    auto* raw = quidra::unified::allocate_host(100000, capacity);
    require(capacity >= 100000, "allocate_host capacity");
    const std::size_t page = quidra::unified::host_page_bytes();
    if (page != 0 && quidra::unified::enabled()) {
        require(reinterpret_cast<std::uintptr_t>(raw) % page == 0 && capacity % page == 0,
                "large host allocations are page aligned and page rounded");
    }
    HostBytes adopted;
    adopted.adopt(raw, 100000, capacity, &count_wrapped_release);
    adopted.release_ownership(); // ownership handed elsewhere: nothing freed
    require(wrapped_releases == 0 && adopted.data() == raw, "HostBytes release_ownership");
    adopted = HostBytes{};
    require(wrapped_releases == 0, "released HostBytes must not free");
    count_wrapped_release(raw, capacity);
    wrapped_releases = 0;
}

// The fake GPU under QUIDRA_TEST_FAKE_GPU_UNIFIED=1 behaves like unified memory.
void test_fake_unified(int gpu) {
    std::string error;
    require(quidra::device::host_visible(gpu), "fake GPU must be host-visible");
    require(!quidra::device::host_visible(99), "unknown index is not host-visible");
    require(quidra::device::host_wrap_granularity(gpu) == 1, "fake wrap granularity");

    auto plain = buffer(gpu, 3 * sizeof(float), error);
    require(static_cast<bool>(plain), error);
    upload<float>(plain.get(), {1.0F, 2.0F, 3.0F}, error);
    auto* host = quidra::device::host_address(plain.get());
    require(host != nullptr, "fake host address");
    float second = 0.0F;
    std::memcpy(&second, host + sizeof(float), sizeof(float));
    require(second == 2.0F, "host address views the device bytes");
    bool settled = false;
    require(quidra::device::prepare_host_view(plain.get(), 3 * sizeof(float), error, settled),
            error);
    require(settled, "the fake GPU settles a host view at once");
    error.clear();
    require(!quidra::device::prepare_host_view(plain.get(), 4 * sizeof(float), error, settled) &&
                !settled && error == "invalid GPU download range",
            "prepare_host_view keeps copy_to_host's range diagnostic");
    error.clear();
    require(quidra::device::wait_for_host_write(plain.get(), error), error);

    auto* memory = static_cast<unsigned char*>(std::malloc(4 * sizeof(float)));
    require(memory != nullptr, "malloc");
    const float values[4] = {5.0F, 6.0F, 7.0F, 8.0F};
    std::memcpy(memory, values, sizeof(values));
    auto* wrapped = quidra::device::wrap_host_memory(
        gpu, memory, sizeof(values), sizeof(values), &count_wrapped_release, error);
    require(wrapped != nullptr, error);
    require(quidra::device::host_address(wrapped) == memory, "wrapped buffer views the host bytes");
    auto output = buffer(gpu, sizeof(values), error);
    require(static_cast<bool>(output), error);
    require(quidra::device::compute_binary(
                output.get(), wrapped, 0, wrapped, 0, nullptr, 0, 10, 1, 4, error),
            error);
    require(download<float>(output.get(), 4, error) ==
                std::vector<float>({10.0F, 12.0F, 14.0F, 16.0F}),
            "kernels read wrapped host memory");
    require(wrapped_releases == 0, "wrapped memory freed early");
    quidra::device::release(wrapped);
    require(wrapped_releases == 1, "wrapped memory is freed with its buffer");
}

// Defers a failed check on `gpu` the way a checked package kernel does
// (qcore_device_status_slot, the kernel writes a nonzero status word,
// qcore_device_defer_status).
void defer_failed_check(int gpu, const char* message) {
    std::string error;
    std::uint64_t handle = 0, offset = 0, slot = 0;
    require(quidra::device::status_slot(gpu, handle, offset, slot, error), error);
    const std::uint32_t failed = 1;
    std::memcpy(reinterpret_cast<unsigned char*>(static_cast<std::uintptr_t>(handle)) + offset,
                &failed, sizeof(failed));
    require(quidra::device::defer_status(gpu, slot, message, error), error);
}

void test_owned_validation_drain_oom(int gpu) {
    namespace parallel=quidra::runtime_parallel::detail;
    bool reached_success=false;
    for(long injected=-1;injected<32;++injected) {
        auto first=std::make_shared<parallel::DeferredNode>();
        auto second=std::make_shared<parallel::DeferredNode>();
        auto foreign=std::make_shared<parallel::DeferredNode>();
        {
            parallel::DeferredNodeScope owner(first);
            defer_failed_check(gpu,"first validation retained beyond foreign drain failure");
        }
        {
            parallel::DeferredNodeScope owner(second);
            defer_failed_check(gpu,"second validation retained beyond foreign drain failure");
        }
        bool failed=false;
        std::string error;
        {
            parallel::DeferredNodeScope consumer(foreign);
            reject_all_allocations=injected<0;
            allocations_before_failure=injected;
            try {const bool okay=quidra::device::synchronize(gpu,error);assert(okay);(void)okay;}
            catch(const std::bad_alloc&) {failed=true;}
            reject_all_allocations=false;allocations_before_failure=-1;
        }
        assert(first->idle()&&second->idle()&&foreign->idle());
        assert(!foreign->first_failure_view());
        for(const auto& owner:{first,second}) {
            const auto* failure=owner->first_failure_view();assert(failure);
            if(failure->report) {
                assert(failure->report->head().kind==quidra::runtime::ReportKind::uncoded);
                assert(failure->report->message()=="allocation failed");
            }else assert(failure->message.find("validation retained beyond foreign drain failure")!=std::string::npos);
        }
        if(injected<0)assert(failed);
        if(!failed) {reached_success=true;break;}
    }
    assert(reached_success);
    // Subsequent ordinary use verifies arena consumed/recycling flags were
    // not stranded by a partial batch/recycle allocation failure.
    std::string error;defer_failed_check(gpu,"validation after an allocation failure");
    const bool okay=quidra::device::synchronize(gpu,error);assert(!okay);(void)okay;
    assert(error.find("validation after an allocation failure")!=std::string::npos);
}

bool starts_with(const std::string& text, const std::string& prefix) {
    return text.rfind(prefix, 0) == 0;
}

// A host read is a synchronization point on the fake GPU as on Metal: it
// reports the deferred checks pending on its device, through copy_to_host
// and through the preparation of a host view alike, and consumes them; a
// read of another device leaves them pending.
void test_fake_host_reads_consume_checks(int gpu, int other) {
    std::string error;
    auto data = buffer(gpu, sizeof(float), error);
    auto other_data = buffer(other, sizeof(float), error);
    require(data && other_data, error);
    upload<float>(data.get(), {1.0F}, error);
    upload<float>(other_data.get(), {2.0F}, error);

    defer_failed_check(gpu, "deferred check read by copy_to_host");
    float value = 0.0F;
    require(quidra::device::copy_to_host(other_data.get(), 0, &value, sizeof(value), error),
            "a read of another device consumed the check: " + error);
    error.clear();
    require(!quidra::device::copy_to_host(data.get(), 0, &value, sizeof(value), error) &&
                starts_with(error, "deferred check read by copy_to_host"),
            "copy_to_host did not report the pending deferred check: " + error);
    error.clear();
    require(quidra::device::copy_to_host(data.get(), 0, &value, sizeof(value), error) &&
                value == 1.0F,
            "the reported check stayed pending: " + error);

    defer_failed_check(gpu, "deferred check read by a host view");
    bool settled = false;
    error.clear();
    require(!quidra::device::prepare_host_view(data.get(), sizeof(float), error, settled) &&
                !settled && starts_with(error, "deferred check read by a host view"),
            "prepare_host_view did not report the pending deferred check: " + error);
    error.clear();
    require(quidra::device::prepare_host_view(data.get(), sizeof(float), error, settled) &&
                settled,
            "the check reported by a host view stayed pending: " + error);
}

std::string read_file(const std::filesystem::path& path) {
    std::ifstream in(path, std::ios::binary);
    return std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
}

// A deferred check that fails at exit (GPU_ASYNC) keeps the output written
// before it: the exit guard flushes standard output ahead of its report.
// The child (this program with --exit-with-pending-check) writes a line to
// its fully buffered standard output, leaves a failed check pending and
// returns from main.
void test_exit_check_keeps_output(const char* self) {
    const auto directory = std::filesystem::temp_directory_path();
    const auto tag = std::to_string(
#ifdef _WIN32
        static_cast<long long>(std::rand())
#else
        static_cast<long long>(getpid())
#endif
    );
    const auto out = directory / ("quidra-device-exit-" + tag + ".out");
    const auto err = directory / ("quidra-device-exit-" + tag + ".err");
    const auto command = "\"" + std::string(self) + "\" --exit-with-pending-check >\"" +
                         out.string() + "\" 2>\"" + err.string() + "\"";
#ifdef _WIN32
    // cmd.exe strips the outer quotes of a command that starts with one.
    const int status = std::system(("\"" + command + "\"").c_str());
#else
    const int raw = std::system(command.c_str());
    const int status = WIFEXITED(raw) ? WEXITSTATUS(raw) : -1;
#endif
    const auto output = read_file(out);
    const auto report = read_file(err);
    std::filesystem::remove(out);
    std::filesystem::remove(err);
    require(status == 101, "a check pending at exit ends with status 101, got " +
                               std::to_string(status));
    require(output == "before exit\n", "output written before exit was lost: '" + output + "'");
    require(report.find("Quidra runtime error[GPU_ASYNC]: check pending at exit") !=
                std::string::npos,
            "missing GPU_ASYNC report: " + report);
}

int exit_with_pending_check() {
    const auto& infos = quidra::device::devices();
    for (const auto& info : infos) {
        if (info.backend != Backend::Test) continue;
        defer_failed_check(info.index, "check pending at exit");
        std::fputs("before exit\n", stdout);
        return 0;
    }
    return 1;
}

template <typename T>
std::vector<T> download(const Buffer* source, std::size_t count, std::string& error) {
    std::vector<T> values(count);
    require(
        quidra::device::copy_to_host(
            source, 0, values.data(), values.size() * sizeof(T), error),
        error);
    return values;
}

} // namespace

namespace {
template <typename T>
void test_half_compute(int gpu, int dtype) {
    using namespace quidra;
    std::string error;
    auto left=buffer(gpu,3*sizeof(T),error),right=buffer(gpu,3*sizeof(T),error),out=buffer(gpu,3*sizeof(T),error);
    require(left&&right&&out,error);
    upload<T>(left.get(),{T(1),T(2),T(3)},error);
    upload<T>(right.get(),{T(4),T(3),T(2)},error);
    require(device::compute_binary(out.get(),left.get(),0,right.get(),0,nullptr,abi::scalar_side::none,
        dtype,abi::tensor_binary_opcode::multiply,3,error),error);
    require(download<T>(out.get(),3,error)==std::vector<T>({T(4),T(6),T(6)}),"half device multiplication");
    auto mask=buffer(gpu,3,error);
    require(device::compute_compare_elements(mask.get(),left.get(),right.get(),nullptr,abi::scalar_side::none,
        dtype,abi::tensor_comparison_opcode::less,3,error),error);
    require(download<unsigned char>(mask.get(),3,error)==std::vector<unsigned char>({1,1,0}),"half device comparison");
    bool equal=false;
    require(device::compute_compare_all(left.get(),0,left.get(),0,dtype,abi::tensor_comparison_opcode::equal,3,equal,error)&&equal,error);
    require(device::compute_binary_backward(out.get(),out.get(),right.get(),left.get(),left.get(),
        dtype,abi::tensor_binary_opcode::multiply,3,error),error);
    require(download<T>(out.get(),3,error)==std::vector<T>({T(8),T(12),T(12)}),"half shared gradient contributions");
    upload<T>(left.get(),{T(0.01),T(0.3),T(1.1)},error);
    upload<T>(right.get(),{T(0.07),T(0.3),T(0.1)},error);
    require(device::compute_scalar_backward(out.get(),right.get(),left.get(),dtype,
        abi::tensor_binary_opcode::power,false,3.0,3,error),error);
    const auto actual_power=download<T>(out.get(),3,error);
    const auto bases=download<T>(left.get(),3,error),seeds=download<T>(right.get(),3,error);
    for(std::size_t i=0;i<3;++i){
        const float x=static_cast<float>(bases[i]),g=static_cast<float>(seeds[i]);
        require(actual_power[i]==T(g*3.0f*std::pow(x,2.0f)),"half power backward rounds the completed contribution");
    }
    const int large=dtype==QCORE_DTYPE_FLOAT16?2048:256;
    upload<T>(right.get(),{T(large),T(1),T(-large)},error);
    const std::uint64_t indices[3]={0,0,0};
    require(device::compute_gather_backward(out.get(),right.get(),dtype,indices,1,3,error,true),error);
    require(download<T>(out.get(),1,error)[0]==T(0),"half scatter rounds each addition");
    require(device::compute_gather_backward(out.get(),right.get(),dtype,indices,1,3,error),error);
    require(download<T>(out.get(),1,error)[0]==T(1),"half gather backward float accumulator");
}

template <typename P>
void test_complex_compute(int gpu,int dtype) {
    using namespace quidra;
    using C=abi::complex::ComplexElement<P>;
    std::string error;
    auto left=buffer(gpu,2*sizeof(C),error),right=buffer(gpu,2*sizeof(C),error),out=buffer(gpu,2*sizeof(C),error);
    require(left&&right&&out,error);
    const C a{P(1),P(2)},b{P(3),P(4)};
    upload<C>(left.get(),{a,b},error);upload<C>(right.get(),{b,a},error);
    require(device::compute_binary(out.get(),left.get(),0,right.get(),0,nullptr,abi::scalar_side::none,
        dtype,abi::tensor_binary_opcode::multiply,2,error),error);
    const auto product=download<C>(out.get(),2,error);
    const C expected=a*b;
    require(std::memcmp(&product[0],&expected,sizeof(C))==0&&std::memcmp(&product[1],&expected,sizeof(C))==0,"complex device component rounding");
    require(device::compute_fill_ones(out.get(),dtype,2,error),error);
    require(download<C>(out.get(),2,error)==std::vector<C>({C{P(1),P(0)},C{P(1),P(0)}}),"complex ones storage");
    require(device::compute_unary(out.get(),left.get(),0,dtype,abi::tensor_unary_opcode::negate,2,error),error);
    require(download<C>(out.get(),2,error)==std::vector<C>({-a,-b}),"complex negation");
    auto mask=buffer(gpu,2,error);
    require(device::compute_compare_elements(mask.get(),left.get(),left.get(),nullptr,abi::scalar_side::none,
        dtype,abi::tensor_comparison_opcode::equal,2,error),error);
    require(download<unsigned char>(mask.get(),2,error)==std::vector<unsigned char>({1,1}),"complex equality");
    const std::uint64_t indices[2]={1,0};
    require(device::compute_gather(out.get(),left.get(),dtype,indices,2,error),error);
    require(download<C>(out.get(),2,error)==std::vector<C>({b,a}),"complex opaque gather");
}

void test_additional_numeric(int gpu) {
    using namespace quidra;
    test_half_compute<abi::half::Real16>(gpu,QCORE_DTYPE_FLOAT16);
    test_half_compute<abi::half::Real16b>(gpu,QCORE_DTYPE_BFLOAT16);
    test_complex_compute<abi::half::Real16>(gpu,QCORE_DTYPE_COMPLEX_FLOAT16);
    test_complex_compute<abi::half::Real16b>(gpu,QCORE_DTYPE_COMPLEX_BFLOAT16);
    test_complex_compute<float>(gpu,QCORE_DTYPE_COMPLEX_FLOAT32);
    test_complex_compute<double>(gpu,QCORE_DTYPE_COMPLEX_FLOAT64);
    std::string error;
    auto source=buffer(gpu,sizeof(std::uint64_t),error),half=buffer(gpu,2,error),complex=buffer(gpu,4,error);
    upload<std::uint64_t>(source.get(),{(std::uint64_t{1}<<63)+(std::uint64_t{1}<<55)+1},error);
    require(device::compute_cast(half.get(),source.get(),0,QCORE_DTYPE_UINT64,QCORE_DTYPE_BFLOAT16,1,error),error);
    require(download<std::uint16_t>(half.get(),1,error)[0]==0x5f01,"direct uint64 to bfloat16 rounding");
    require(device::compute_cast(complex.get(),source.get(),0,QCORE_DTYPE_UINT64,QCORE_DTYPE_COMPLEX_BFLOAT16,1,error),error);
    require(download<std::uint16_t>(complex.get(),2,error)==std::vector<std::uint16_t>({0x5f01,0}),"direct integer to complex half rounding");
}
} // namespace

int main(int argc, char** argv) {
#ifdef _WIN32
    _putenv_s("QUIDRA_TEST_FAKE_GPU_COUNT", "2");
    _putenv_s("QUIDRA_TEST_FAKE_GPU_UNIFIED", "1");
#else
    setenv("QUIDRA_TEST_FAKE_GPU_COUNT", "2", 1);
    setenv("QUIDRA_TEST_FAKE_GPU_UNIFIED", "1", 1);
#endif
    if (argc == 2 && std::string(argv[1]) == "--exit-with-pending-check")
        return exit_with_pending_check();
    test_host_bytes();

    const auto& infos = quidra::device::devices();
    std::vector<int> test_indices;
    for (const auto& info : infos) {
        if (info.backend == Backend::Test) test_indices.push_back(info.index);
    }
    require(test_indices.size() >= 2, "expected two fake GPU devices");
    test_owned_validation_drain_oom(test_indices[0]);
    const int gpu0 = test_indices[0];
    const int gpu1 = test_indices[1];
    std::string error;
    require(quidra::device::synchronize(gpu0, error), error);
    require(quidra::device::synchronize_all(error), error);

    auto left = buffer(gpu0, 4 * sizeof(float), error);
    auto right = buffer(gpu0, 4 * sizeof(float), error);
    auto output = buffer(gpu0, 4 * sizeof(float), error);
    require(left && right && output, error);
    upload<float>(left.get(), {1.0F, 2.0F, 3.0F, 4.0F}, error);
    upload<float>(right.get(), {4.0F, 3.0F, 2.0F, 1.0F}, error);

    require(
        quidra::device::compute_binary(
            output.get(), left.get(), 0, right.get(), 0, nullptr, 0,
            10, 1, 4, error),
        error);
    const auto added = download<float>(output.get(), 4, error);
    require(added == std::vector<float>({5.0F, 5.0F, 5.0F, 5.0F}),
            "float32 binary kernel result mismatch");

    auto int_left = buffer(gpu0, sizeof(std::int8_t), error);
    auto int_output = buffer(gpu0, sizeof(std::int8_t), error);
    require(int_left && int_output, error);
    upload<std::int8_t>(int_left.get(), {127}, error);
    const std::int8_t one = 1;
    error.clear();
    require(
        !quidra::device::compute_binary(
            int_output.get(), int_left.get(), 0, nullptr, 0, &one, 2,
            2, 1, 1, error),
        "checked integer overflow unexpectedly succeeded");
    require(error.find("overflow") != std::string::npos,
            "checked integer overflow diagnostic missing");

    auto wide_float = buffer(gpu0, sizeof(double), error);
    auto narrow_float = buffer(gpu0, sizeof(float), error);
    require(wide_float && narrow_float, error);
    upload<double>(wide_float.get(), {1.0e100}, error);
    error.clear();
    require(
        !quidra::device::compute_cast(
            narrow_float.get(), wide_float.get(), 0, 9, 10, 1, error),
        "out-of-range float64 to float32 GPU cast unexpectedly succeeded");
    require(error.find("out of range") != std::string::npos,
            "float narrowing range diagnostic missing");

    upload<double>(wide_float.get(), {0.1}, error);
    error.clear();
    require(
        quidra::device::compute_cast(
            narrow_float.get(), wide_float.get(), 0, 9, 10, 1, error),
        error);
    const float rounded = download<float>(narrow_float.get(), 1, error)[0];
    require(rounded > 0.099F && rounded < 0.101F,
            "float narrowing should allow deterministic precision loss");

    auto other_device = buffer(gpu1, 4 * sizeof(float), error);
    require(static_cast<bool>(other_device), error);
    upload<float>(other_device.get(), {1.0F, 1.0F, 1.0F, 1.0F}, error);
    error.clear();
    require(
        !quidra::device::compute_binary(
            output.get(), left.get(), 0, other_device.get(), 0, nullptr, 0,
            10, 1, 4, error),
        "cross-device kernel unexpectedly succeeded");
    require(!error.empty(), "cross-device kernel diagnostic missing");

    test_additional_numeric(gpu0);
    test_fake_unified(gpu0);
    test_fake_host_reads_consume_checks(gpu0, gpu1);
    test_exit_check_keeps_output(argv[0]);

    std::cout << "device backend kernels: ok\n";
    return 0;
}
