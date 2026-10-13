#ifdef NDEBUG
#undef NDEBUG
#endif
#include "owned_native_fences.hpp"
#include <atomic>
#include <cassert>
#include <thread>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <new>

namespace {
std::atomic<bool> reject_allocations{};
}
void* operator new(std::size_t bytes) {
    if(reject_allocations.load(std::memory_order_relaxed))throw std::bad_alloc{};
    if(void* memory=std::malloc(bytes?bytes:1))return memory;
    throw std::bad_alloc{};
}
void* operator new[](std::size_t bytes) {return ::operator new(bytes);}
void operator delete(void* memory) noexcept {std::free(memory);}
void operator delete[](void* memory) noexcept {std::free(memory);}
void operator delete(void* memory,std::size_t) noexcept {std::free(memory);}
void operator delete[](void* memory,std::size_t) noexcept {std::free(memory);}

using namespace quidra::device::detail;
namespace parallel=quidra::runtime_parallel::detail;
struct FakeApi {
    std::atomic<int> waits{},releases{};
    NativeFence event(NativeFenceStatus status=NativeFenceStatus::complete,
                      std::string message={}) {
        return {[this,status,message=std::move(message)] {
                    ++waits;return NativeFenceResult{status,message};},
                [this] {++releases;return std::string{};}};
    }
};
// CTest prints captured stderr for failures. These checkpoints identify which
// allocation-free fence scenario triggered a Windows fail-fast exit.
static void windows_stage(const char* name) {
#ifdef _WIN32
    std::fprintf(stderr,"native-fences stage: %s\n",name);
    std::fflush(stderr);
#else
    (void)name;
#endif
}
int main(int argc,char** argv) {
    if(argc==2&&std::strcmp(argv[1],"--unknown-oom")==0) {
        FakeApi api;
        OwnedNativeFences fences;
        auto owner=std::make_shared<parallel::DeferredNode>();
        {
            auto submit=fences.submission(8);
            auto reserved=fences.reserve(submit,owner,{
                []() -> NativeFenceResult {throw std::bad_alloc{};},
                [&] {++api.releases;return std::string{};}});
            reject_allocations=true;
            fences.publish(submit,reserved);
        }
        fences.drain_or_fail(8,fences.boundary(8),[&](const std::string& message) {
            assert(api.releases==1&&!owner->idle()&&!owner->first_failure_view());
            std::fprintf(stderr,"Quidra runtime error[GPU_ASYNC]: operation owner unknown: %s\n",message.c_str());
            std::fflush(stderr);std::_Exit(101);
        });
        return 1;
    }
    if(argc==2&&std::strcmp(argv[1],"--unknown-context")==0) {
        FakeApi api;
        OwnedNativeFences fences;
        auto owner=std::make_shared<parallel::DeferredNode>();
        {
            auto submit=fences.submission(7);
            fences.enqueue(submit,owner,api.event(NativeFenceStatus::unattributed_failure,"sticky context"));
        }
        fences.drain_or_fail(7,fences.boundary(7),[&](const std::string& message) {
            assert(api.releases==1&&!owner->idle()&&!owner->first_failure());
            // Another device lock is obtainable: no drain lock survives here.
            std::thread lock_probe([&] {auto next=fences.submission(7);});
            lock_probe.join();
            std::fprintf(stderr,"Quidra runtime error[GPU_ASYNC]: operation owner unknown: %s\n",message.c_str());
            std::fflush(stderr);std::_Exit(101);
        });
        return 1;
    }
    windows_stage("reservation and no-alloc drain");
    // Reservation, publication, success drain, failure completion and view
    // retention require no allocation after work has begun.
    {
        FakeApi reserved_api;
        OwnedNativeFences reserved_fences;
        auto owner=std::make_shared<parallel::DeferredNode>();
        auto submit=reserved_fences.submission(9);
        auto reserved=reserved_fences.reserve(submit,owner,reserved_api.event());
        auto failed=owner->enqueue(9,100);
        windows_stage("no-alloc reservation prepared");
        parallel::DeferredFailure failure;
        failure.message="a preallocated diagnostic larger than the small string buffer";
        reject_allocations=true;
        reserved_fences.publish(submit,reserved);
        windows_stage("no-alloc reservation published");
        reserved_fences.drain_or_fail(9,reserved_fences.boundary(9),[](const std::string&) {std::abort();});
        windows_stage("no-alloc reservation drained");
        const auto& view=failed.complete_view(std::move(failure));
        windows_stage("no-alloc deferred outcome completed");
        assert(owner->idle()&&view.message.size()>32&&owner->first_failure_view()==&view);
        reject_allocations=false;
        assert(reserved_api.waits==1&&reserved_api.releases==1);
    }
    windows_stage("out-of-order publication");
    // An earlier reservation can publish after a later one, as package
    // epochs do. A serial boundary must still drain the earlier cell.
    {
        FakeApi reserved_api;
        OwnedNativeFences reserved_fences;
        auto earlier=std::make_shared<parallel::DeferredNode>();
        auto later=std::make_shared<parallel::DeferredNode>();
        auto submit=reserved_fences.submission(10);
        auto first=reserved_fences.reserve(submit,earlier,reserved_api.event());
        auto last=reserved_fences.reserve(submit,later,reserved_api.event());
        reserved_fences.publish(submit,last);
        const auto covered=reserved_fences.publish(submit,first);
        assert(reserved_fences.drain(10,covered).empty());
        assert(earlier->idle()&&!later->idle());
        assert(reserved_fences.drain(10,reserved_fences.boundary(10)).empty()&&later->idle());
    }
    windows_stage("retained callback");
    // A completed callback keeps its immutable outcome owner alive after
    // removal from a queue/map and after an earlier outcome is inserted.
    {
        auto owner=std::make_shared<parallel::DeferredNode>();
        std::weak_ptr<parallel::DeferredNode> lifetime=owner;
        owner->run_callback=[](void(*body)(void*),void* frame,const std::shared_ptr<void>& raw) {
            body(frame);
            parallel::DeferredFailure outcome;
            outcome.message=std::move(*std::static_pointer_cast<std::string>(raw));return outcome;
        };
        auto earlier=owner->enqueue(11,0);
        std::optional<parallel::DeferredCallback> callback;
        {
            parallel::DeferredNodeScope scope(owner);
            callback.emplace([](void*) {},nullptr,11,1);
        }
        callback->runtime_context=std::make_shared<std::string>("retained callback outcome beyond queue erasure");
        parallel::DeferredFailure failure;failure.message="earlier outcome";
        owner.reset();
        reject_allocations=true;
        const auto& view=callback->invoke(11);
        earlier.complete(std::move(failure));
        assert(!lifetime.expired()&&view.message=="retained callback outcome beyond queue erasure");
        assert(&callback->invoke(11)==&view);
        reject_allocations=false;
        earlier={};
        // Moving the callback models map extraction/recycling without
        // changing the address of the retained outcome.
        auto completed=std::move(*callback);callback.reset();
        assert(&completed.invoke(11)==&view&&!lifetime.expired());
    }
    windows_stage("owned completion");
    FakeApi api;
    auto first=std::make_shared<parallel::DeferredNode>();
    auto second=std::make_shared<parallel::DeferredNode>();
    auto foreign=std::make_shared<parallel::DeferredNode>();
    OwnedNativeFences fences;
    std::uint64_t boundary=0;
    {
        auto submit=fences.submission(0);
        fences.enqueue(submit,first,api.event());
        boundary=fences.enqueue(submit,second,api.event(NativeFenceStatus::owned_failure,"second only"));
    }
    {
        parallel::DeferredNodeScope sync(foreign);
        assert(fences.drain(0,boundary).empty());
    }
    assert(first->idle()&&!first->first_failure());
    assert(second->idle()&&second->first_failure()->message=="second only");
    assert(foreign->idle()&&!foreign->first_failure());
    assert(api.waits==2&&api.releases==2);
    windows_stage("serial boundary");
    // A boundary covers only the submission serials recorded before it.
    auto later=std::make_shared<parallel::DeferredNode>();
    {
        auto submit=fences.submission(0);fences.enqueue(submit,later,api.event());
    }
    assert(fences.drain(0,boundary).empty()&&!later->idle());
    assert(fences.drain(0,fences.boundary(0)).empty()&&later->idle());
    windows_stage("nested owner scopes");
    // Nested scopes retain separate owners even on the same device.
    auto parent=std::make_shared<parallel::DeferredNode>();
    auto child=std::make_shared<parallel::DeferredNode>();
    {
        parallel::DeferredNodeScope outer(parent);
        auto submit=fences.submission(1);
        fences.enqueue(submit,parallel::current_deferred_node,api.event());
        {
            parallel::DeferredNodeScope inner(child);
            fences.enqueue(submit,parallel::current_deferred_node,
                           api.event(NativeFenceStatus::owned_failure,"child only"));
        }
        assert(parallel::current_deferred_node==parent);
    }
    assert(fences.drain(1,fences.boundary(1)).empty());
    assert(parent->idle()&&!parent->first_failure());
    assert(child->idle()&&child->first_failure()->message=="child only");
    windows_stage("event cleanup");
    // Event cleanup precedes ticket completion and any later failure capture.
    auto cleanup_owner=std::make_shared<parallel::DeferredNode>();
    bool cleaned=false;
    {
        auto submit=fences.submission(2);
        fences.enqueue(submit,cleanup_owner,{
            [] {return NativeFenceResult{NativeFenceStatus::owned_failure,"after cleanup"};},
            [&] {assert(!cleanup_owner->first_failure());cleaned=true;return std::string{};}});
    }
    assert(fences.drain(2,fences.boundary(2)).empty());
    assert(cleaned&&cleanup_owner->first_failure());
    windows_stage("multithreaded submissions");
    // Submission locks serialize one device without sharing another lock.
    auto concurrent=std::make_shared<parallel::DeferredNode>();
    std::vector<std::thread> workers;
    for(int worker=0;worker<4;++worker)
        workers.emplace_back([&] {
            for(int i=0;i<100;++i) {
                auto submit=fences.submission(3);
                fences.enqueue(submit,concurrent,api.event());
            }
        });
    for(auto& worker:workers)worker.join();
    assert(fences.drain(3,fences.boundary(3)).empty()&&concurrent->idle());
    windows_stage("unattributed failure");
    // Low-level unknown result exists only until drain_or_fail invokes its
    // immediate fatal callback. It must never be retried by runtime joins.
    auto ambiguous=std::make_shared<parallel::DeferredNode>();
    {
        auto submit=fences.submission(4);
        fences.enqueue(submit,ambiguous,api.event(NativeFenceStatus::unattributed_failure,"sticky context"));
    }
    auto unresolved=fences.drain(4,fences.boundary(4));
    assert(unresolved.size()==1&&unresolved[0].owner==ambiguous);
    assert(!ambiguous->idle()&&!ambiguous->first_failure());
    assert(fences.unattributed(4)[0].message=="sticky context");
    assert(!foreign->first_failure());
}
