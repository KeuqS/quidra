#pragma once
#include "runtime_location.hpp"
#include "runtime_trace.hpp"
#include "runtime_report.hpp"
#include "runtime_tail.hpp"
#include <algorithm>
#include <csetjmp>
#include <cstdlib>
#include <limits>
#include <new>
#include <cstring>
#include <deque>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace quidra::runtime {
class OwnedError {
public:
    explicit OwnedError(const abi::ErrorRecord& source) : OwnedError(source,Shallow{}) {
        auto* previous=this;
        for(auto* cause=source.cause;cause;cause=cause->cause) {
            auto child=std::unique_ptr<OwnedError>(new OwnedError(*cause,Shallow{}));
            previous->record()->cause=child->record();
            previous=child.get();
            causes_.push_back(std::move(child));
        }
    }
    abi::ErrorRecord* record() noexcept {
        return reinterpret_cast<abi::ErrorRecord*>(bytes_.get());
    }
private:
    struct Shallow {};
    OwnedError(const abi::ErrorRecord& source,Shallow) {
        const auto* schema = abi::error_value_schema(source.schema);
        const auto slots = schema ? schema->details.size() : 0;
        bytes_ = std::make_unique<std::byte[]>(abi::error_record_size(slots));
        std::memcpy(bytes_.get(), &source, abi::error_record_size(slots));
        auto& copy = *record();
        copy.message = own(source.message);
        copy.code = own(source.code);
        copy.cause=nullptr;
        if (source.hops) {
            if (source.hops->count) hops_.assign(source.hops->entries, source.hops->entries + source.hops->count);
            hop_list_ = {hops_.size(), hops_.size(), hops_.data()};
            copy.hops = &hop_list_;
        }
        auto* details = reinterpret_cast<abi::ErrorDetailSlot*>(bytes_.get() + sizeof(copy));
        for (std::size_t i=0; i<slots; ++i) {
            if (schema->details[i].kind == abi::ErrorDetailKind::integer) continue;
            const auto* original = reinterpret_cast<const char*>(details[i].bits);
            details[i].bits = reinterpret_cast<std::uintptr_t>(own(original));
        }
    }
    const char* own(const char* source) {
        if (!source) return nullptr;
        text_.emplace_back(source);
        return text_.back().c_str();
    }
    std::unique_ptr<std::byte[]> bytes_;
    std::deque<std::string> text_;
    // Each child is a shallow record. Neither capture nor destruction uses
    // one C++ stack frame per cause in an arbitrarily long error chain.
    std::vector<std::unique_ptr<OwnedError>> causes_;
    std::vector<abi::ErrorHopEntry> hops_;
    abi::ErrorHopList hop_list_{};
};

class OwnedNodeReport {
public:
    OwnedNodeReport(const ReportHead& head, ReportLocation location,
                    std::string_view message, const ReportData& data,
                    std::optional<ReportSite> raw_site=std::nullopt)
        : head_(head), location_(location), data_(data), code_(head.code),
          message_(message), arg_type_(data.args.type),
          arg_message_(data.args.message), arg_path_(data.args.path),
          arg_slice_(data.args.slice),arg_marker_(data.args.marker),
          arg_step_(data.args.step_text),raw_site_(raw_site) {
        head_.code = code_;
        data_.args.type = arg_type_;
        data_.args.message = arg_message_;
        data_.args.path = arg_path_;
        data_.args.slice=arg_slice_;data_.args.marker=arg_marker_;
        data_.args.step_text=arg_step_;
        if (data.reason) {reason_ = *data.reason; data_.reason = &reason_;}
        if (data.error) {error_ = std::make_unique<OwnedError>(*data.error); data_.error = error_->record();}
        const auto raw = data.path ? *data.path : walk_call_path();
        path_ = raw;
        if (raw.count) items_.assign(raw.items, raw.items + raw.count);
        std::size_t candidates = 0;
        for (const auto& item : items_) {
            names_.emplace_back(item.function);
            candidates = (std::max)(candidates,
                static_cast<std::size_t>(item.first_candidate) + item.candidate_count);
        }
        if (candidates) candidates_.assign(raw.candidates, raw.candidates + candidates);
        for (std::size_t i=0; i<items_.size(); ++i) items_[i].function = names_[i];
        path_.items = items_.data(); path_.candidates = candidates_.data();
        data_.path = &path_;
    }
    void append_join(std::string_view body, unsigned long long line,
                     unsigned long long column, const CallPath& joining) {
        // Own every name and candidate before the joining thread walks again.
        names_.emplace_back(body);
        items_.push_back(PathItem{PathItemKind::call,PathVia::call,names_.back(),line,column,0,0,1});
        const auto candidate_base=static_cast<std::uint32_t>(candidates_.size());
        std::size_t count=0;
        for (std::size_t i=0;i<joining.count;++i)
            count=(std::max)(count,static_cast<std::size_t>(joining.items[i].first_candidate)+joining.items[i].candidate_count);
        if (count) candidates_.insert(candidates_.end(),joining.candidates,joining.candidates+count);
        for (std::size_t i=0;i<joining.count;++i) {
            auto item=joining.items[i];
            names_.emplace_back(item.function);
            item.function=names_.back();
            if (item.candidate_count) item.first_candidate+=candidate_base;
            items_.push_back(item);
        }
        path_.items=items_.data();path_.count=items_.size();path_.candidates=candidates_.data();
        path_.complete=path_.complete && joining.complete;
    }
    const ReportHead& head() const noexcept {return head_;}
    ReportLocation location() const noexcept {return raw_site_ ? locate_report_site(*raw_site_) : location_;}
    std::optional<ReportSite> raw_site() const noexcept {return raw_site_;}
    void write() const {
        if(raw_site_) {
            ReportSourceScope source(raw_site_->table);
            write_report(head_,location(),message_,data_);
        } else write_report(head_,location_,message_,data_);
    }
    const ReportData& data() const noexcept {return data_;}
    const CallPath& path() const noexcept {return path_;}
    std::string_view message() const noexcept {return message_;}
private:
    ReportHead head_;
    ReportLocation location_;
    ReportData data_;
    abi::FailureReason reason_{};
    std::string code_, message_, arg_type_, arg_message_, arg_path_,arg_slice_,arg_marker_,arg_step_;
    std::optional<ReportSite> raw_site_;
    std::unique_ptr<OwnedError> error_;
    CallPath path_{};
    std::vector<PathItem> items_;
    std::deque<std::string> names_;
    std::vector<PathCandidate> candidates_;
};
struct CapturedNodeFailure {};
using ModuleState = void(*)(std::uint64_t*, bool);
// The generated helper saves and clears when restore is false. A snapshot
// must put those values back before the caller continues executing.
inline void snapshot_module_state(ModuleState state,std::uint64_t* values) {
    if(state) {state(values,false);state(values,true);}
}

struct NodeFailureScope;
struct NodeCleanupFrame {
    NodeCleanupFrame* previous{};
    NodeFailureScope* owner{};
    void (*drop)(void*){};
    void* allocation{};
    void* payload{};
};
inline bool finish_node_frames(NodeFailureScope* scope);
inline thread_local NodeFailureScope* current_node_failure{};
#ifdef _MSC_VER
// std::jmp_buf intentionally imposes alignment padding.
#pragma warning(push)
#pragma warning(disable: 4324)
#endif
struct NodeFailureScope {
    NodeFailureScope* previous{current_node_failure};
    std::unique_ptr<OwnedNodeReport> report;
    std::optional<int> exit_status;
    runtime_tail::NodeScope tail_state;
    NodeSourceState source_state{save_node_source_state()};
    ModuleState module_state{};
    std::uint64_t saved_module_state[3]{};
    std::jmp_buf target;
    NodeCleanupFrame* cleanup_frames{};
    explicit NodeFailureScope(ModuleState state = nullptr) noexcept : module_state(state) {
        current_node_failure = this;
        if (module_state) module_state(saved_module_state, false);
    }
    ~NodeFailureScope() {
        if (module_state) module_state(saved_module_state, true);
        restore_node_source_state(source_state);
        current_node_failure = previous;
    }
};
#ifdef _MSC_VER
#pragma warning(pop)
#endif
inline bool node_failure_active() noexcept {return current_node_failure != nullptr;}
[[noreturn]] inline void capture_node_failure(const ReportHead& head,
        ReportLocation location, std::string_view message, const ReportData& data,
        std::optional<ReportSite> raw_site=std::nullopt) {
    current_node_failure->report = std::make_unique<OwnedNodeReport>(head, location, message, data,raw_site);
    throw CapturedNodeFailure{};
}
[[noreturn]] inline void capture_node_exit(int status) {
    current_node_failure->exit_status = status;
    throw CapturedNodeFailure{};
}

using NodeBody = void(*)(void*);
inline bool call_node_body(NodeBody body, void* frame) {
    try {body(frame);}
    catch (const CapturedNodeFailure&) {return true;}
    catch (const std::bad_alloc&) {
        // The language wrapper is unwindable. Convert before returning through
        // the scheduler's noexcept entry, after runtime intermediates unwound.
        try {report_uncoded("allocation failed");}
        catch (const CapturedNodeFailure&) {return true;}
    }
    return false;
}
// The catch and every runtime C++ frame have returned before this jump.
// This frame contains only pointers and the setjmp expression.
#ifdef _MSC_VER
// All nontrivial C++ frames unwind in call_node_body before longjmp.
#pragma warning(push)
#pragma warning(disable: 4611)
#endif
inline bool invoke_node_body(NodeFailureScope* scope, NodeBody body, void* frame) {
    if (setjmp(scope->target) != 0) return false;
    const bool failed=call_node_body(body, frame);
    const bool cleanup_failed=finish_node_frames(scope);
    if (failed || cleanup_failed || scope->report || scope->exit_status)
        std::longjmp(scope->target, 1);
    return true;
}
#ifdef _MSC_VER
#pragma warning(pop)
#endif

// Generated owned slots live in this payload when a function runs inside
// a node. Unlike a pointer to an LLVM alloca, it remains valid after the
// cold unwind has left the function. Borrowed and outer captured storage
// never belongs to this frame.
inline void* create_node_frame(std::uint64_t bytes,std::uint64_t alignment,
                              void (*drop)(void*)) {
    if(!current_node_failure) return nullptr;
    if(alignment<alignof(NodeCleanupFrame)) alignment=alignof(NodeCleanupFrame);
    if((alignment & (alignment-1)) || alignment>std::numeric_limits<std::size_t>::max() ||
       bytes>std::numeric_limits<std::size_t>::max()-sizeof(NodeCleanupFrame)-(alignment-1))
        report_uncoded("parallel cleanup frame size is invalid");
    const auto count=sizeof(NodeCleanupFrame)+static_cast<std::size_t>(alignment-1+bytes);
    void* allocation=std::malloc(count);
    if(!allocation) report_uncoded("cannot allocate parallel cleanup frame");
    const auto first=reinterpret_cast<std::uintptr_t>(allocation)+sizeof(NodeCleanupFrame);
    const auto aligned=(first+alignment-1)&~(static_cast<std::uintptr_t>(alignment)-1);
    void* payload=reinterpret_cast<void*>(aligned);
    auto* header=new(reinterpret_cast<void*>(aligned-sizeof(NodeCleanupFrame))) NodeCleanupFrame{
        current_node_failure->cleanup_frames,current_node_failure,drop,allocation,payload};
    current_node_failure->cleanup_frames=header;
    std::memset(payload,0,static_cast<std::size_t>(bytes));
    return payload;
}

// A normal function exit already released its owned values. Remove and
// free only the backing storage; a failure instead calls the generated
// typed drop callback exactly once in finish_node_frames.
inline void leave_node_frame(void* payload) noexcept {
    if(!payload) return;
    auto* header=reinterpret_cast<NodeCleanupFrame*>(
        static_cast<unsigned char*>(payload)-sizeof(NodeCleanupFrame));
    auto** link=&header->owner->cleanup_frames;
    while(*link && *link!=header) link=&(*link)->previous;
    if(*link==header) *link=header->previous;
    std::free(header->allocation);
}

inline void cleanup_node_slot(void (*drop)(void*),void* slot) {
    if(!drop) return;
    auto* owner=current_node_failure;
    if(!owner) {drop(slot);return;}
    NodeFailureScope cleanup;
    struct Call {void (*drop)(void*);void* slot;} call{drop,slot};
    const bool okay=invoke_node_body(&cleanup,[](void* raw) {
        auto* call=static_cast<Call*>(raw);
        call->drop(call->slot);
    },&call);
    if(!okay && !owner->report && !owner->exit_status) {
        owner->report=std::move(cleanup.report);
        owner->exit_status=cleanup.exit_status;
    }
}

inline bool finish_node_frames(NodeFailureScope* scope) {
    bool failed=false;
    while(auto* frame=scope->cleanup_frames) {
        scope->cleanup_frames=frame->previous;
        struct Storage {
            void* allocation;
            ~Storage() {std::free(allocation);}
        } storage{frame->allocation};
        // A cleanup failure has its own jump target. It cannot overwrite
        // the still-active outer trampoline target or the primary outcome.
        NodeFailureScope cleanup;
        struct Drop {NodeCleanupFrame* frame;} drop{frame};
        const bool okay=invoke_node_body(&cleanup,[](void* raw) {
            const auto* frame=static_cast<Drop*>(raw)->frame;
            if(frame->drop) frame->drop(frame->payload);
        },&drop);
        if(!okay) {
            failed=true;
            if(!scope->report && !scope->exit_status) {
                scope->report=std::move(cleanup.report);
                scope->exit_status=cleanup.exit_status;
            }
        }
    }
    return failed;
}
} // namespace quidra::runtime
