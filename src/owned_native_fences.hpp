#pragma once
#include "deferred_node.hpp"
#include <list>
#include <exception>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

namespace quidra::device::detail {
namespace parallel = runtime_parallel::detail;

enum class NativeFenceStatus { complete, owned_failure, unattributed_failure };
struct NativeFenceResult {
    NativeFenceStatus status{NativeFenceStatus::complete};
    std::string message;
};
struct NativeFence {
    std::function<NativeFenceResult()> wait;
    // Returns a cleanup error instead of reporting a runtime failure.
    std::function<std::string()> release;
    std::function<std::shared_ptr<runtime::OwnedNodeReport>(const std::string&)> failure_report;
};
struct UnattributedNativeFence {
    int device{};
    std::uint64_t serial{};
    std::shared_ptr<parallel::DeferredNode> owner;
    std::optional<runtime::ReportSite> site;
    std::string message;
};

// A completion registry does not raise a node failure. Its caller may raise
// only after drain() returned, when event handles and backend locks are gone.
class OwnedNativeFences {
    struct Pending {
        std::uint64_t serial{};
        parallel::DeferredTicket ticket;
        NativeFence fence;
        std::optional<runtime::ReportSite> site;
        std::string unattributed_message{"native GPU completion could not be proved after a runtime failure"};
        parallel::DeferredFailure abandoned;
        Pending() {abandoned.message="native GPU fence was abandoned before its owner drained";}
        ~Pending() {
            if(fence.release) {
                try {(void)fence.release();} catch(...) {}
            }
            if(ticket) ticket.complete(std::move(abandoned));
        }
    };
    using Queue=std::list<std::unique_ptr<Pending>>;
    struct Device {
        std::recursive_mutex submissions;
        std::mutex pending_mutex;
        std::uint64_t next_serial{1};
        Queue pending;
        Queue unattributed;
    };
public:
    class Submission {
    public:
        Submission(Submission&&)=default;
        Submission& operator=(Submission&&)=delete;
    private:
        friend class OwnedNativeFences;
        Submission(int index,std::shared_ptr<Device> state)
            : index_(index),state_(std::move(state)),lock_(state_->submissions) {}
        int index_;
        std::shared_ptr<Device> state_;
        std::unique_lock<std::recursive_mutex> lock_;
    };
    class Reservation {
    public:
        Reservation()=default;
        Reservation(Reservation&&)=default;
        Reservation& operator=(Reservation&&)=default;
    private:
        friend class OwnedNativeFences;
        int index_{};
        std::shared_ptr<Device> state_;
        Queue ready_;
    };
    Submission submission(int device) {return Submission(device,state(device));}
    Submission submission(const Reservation& reserved) {
        return Submission(reserved.index_,reserved.state_);
    }
    Reservation reserve(Submission& submission,
            const std::shared_ptr<parallel::DeferredNode>& owner,NativeFence fence,
            std::optional<runtime::ReportSite> site={}) {
        Reservation result;
        if(!owner)return result;
        result.index_=submission.index_;result.state_=submission.state_;
        // Allocate the record, callbacks, queue link and future outcome before
        // the caller submits asynchronous work. Publication only splices it.
        result.ready_.push_back(std::make_unique<Pending>());
        auto& pending=*result.ready_.front();
        pending.fence=std::move(fence);pending.site=site;
        auto& device=*submission.state_;
        std::lock_guard guard(device.pending_mutex);
        pending.serial=device.next_serial;
        pending.ticket=owner->enqueue(submission.index_,pending.serial);
        ++device.next_serial;
        return result;
    }
    std::uint64_t publish(Submission& submission,Reservation& reserved) noexcept {
        if(reserved.ready_.empty())return 0;
        const auto serial=reserved.ready_.front()->serial;
        std::lock_guard guard(submission.state_->pending_mutex);
        submission.state_->pending.splice(submission.state_->pending.end(),reserved.ready_);
        return serial;
    }
    std::uint64_t enqueue(Submission& submission,
            const std::shared_ptr<parallel::DeferredNode>& owner,NativeFence fence,
            std::optional<runtime::ReportSite> site={}) {
        auto reserved=reserve(submission,owner,std::move(fence),site);
        return publish(submission,reserved);
    }
    std::uint64_t boundary(int index) {
        auto submission=this->submission(index);
        std::lock_guard guard(submission.state_->pending_mutex);
        return submission.state_->next_serial-1;
    }
    std::vector<UnattributedNativeFence> drain(int index,std::uint64_t covered) {
        drain_records(index,covered);
        // This inspection API may allocate, after all work/handles have been
        // transferred or completed. Runtime joins use drain_or_fail instead.
        return unattributed(index);
    }
    template<class Fatal>
    void drain_or_fail(int index,std::uint64_t covered,Fatal fatal) {
        auto device=drain_records(index,covered);
        const std::string* unknown=nullptr;
        {
            std::lock_guard guard(device->pending_mutex);
            if(!device->unattributed.empty())unknown=&device->unattributed.front()->unattributed_message;
        }
        // The retained unknown cell is stable; no device lock or event handle
        // is held by this call. It cannot reenter an owner idle-wait loop.
        if(unknown) {fatal(*unknown);std::terminate();}
    }
    bool has_pending(int index) {
        auto device=state(index);
        std::lock_guard guard(device->pending_mutex);
        return !device->pending.empty()||!device->unattributed.empty();
    }
    std::vector<UnattributedNativeFence> unattributed(int index) {
        std::vector<UnattributedNativeFence> result;
        auto device=state(index);
        std::lock_guard guard(device->pending_mutex);
        for(const auto& entry:device->unattributed)
            result.push_back({index,entry->serial,entry->ticket.owner(),entry->site,entry->unattributed_message});
        return result;
    }
    std::vector<int> pending_devices() {
        std::vector<int> result;
        std::lock_guard guard(mutex_);
        for(const auto& [index,device]:devices_) {
            std::lock_guard pending(device->pending_mutex);
            if(!device->pending.empty()||!device->unattributed.empty()) result.push_back(index);
        }
        return result;
    }
private:
    std::shared_ptr<Device> drain_records(int index,std::uint64_t covered) {
        auto submission=this->submission(index);
        auto device=submission.state_;
        Queue local;
        {
            std::lock_guard guard(device->pending_mutex);
            // Package reservations can publish later than a newer marker.
            // Coverage is determined by serial, not by publication order.
            for(auto it=device->pending.begin();it!=device->pending.end();) {
                const auto current=it++;
                if((*current)->serial<=covered)local.splice(local.end(),device->pending,current);
            }
        }
        while(!local.empty()) {
            auto& entry=*local.front();
            NativeFenceResult result;
            try {result=entry.fence.wait();}
            catch(...) {result.status=NativeFenceStatus::unattributed_failure;}
            try {
                if(entry.fence.release) {
                    auto cleanup=entry.fence.release();
                    if(!cleanup.empty()) {
                        result.status=NativeFenceStatus::unattributed_failure;
                        result.message=std::move(cleanup);
                    }
                }
            }catch(...) {result.status=NativeFenceStatus::unattributed_failure;}
            auto failure_report=std::move(entry.fence.failure_report);
            entry.fence={};
            if(result.status==NativeFenceStatus::unattributed_failure) {
                if(!result.message.empty())entry.unattributed_message=std::move(result.message);
                // Keep the reservation/ticket intact until the immediate
                // unknown-context fatal policy, without allocating a link.
                std::lock_guard guard(device->pending_mutex);
                device->unattributed.splice(device->unattributed.end(),local,local.begin());
            }else {
                parallel::DeferredFailure failure;
                if(result.status==NativeFenceStatus::owned_failure) {
                    failure.message=result.message.empty()?std::move(entry.unattributed_message):std::move(result.message);
                    // Wait/release already proved completion. Diagnostic
                    // decoration OOM must not strand this owner's ticket.
                    if(failure_report) {
                        try {failure.report=failure_report(failure.message);}catch(const std::bad_alloc&) {}
                    }
                }
                failure.raw_site=entry.site;
                entry.ticket.complete(std::move(failure));local.pop_front();
            }
        }
        return device;
    }
    std::shared_ptr<Device> state(int index) {
        std::lock_guard guard(mutex_);
        auto& result=devices_[index];
        if(!result) result=std::make_shared<Device>();
        return result;
    }
    std::mutex mutex_;
    std::map<int,std::shared_ptr<Device>> devices_;
};
} // namespace quidra::device::detail
