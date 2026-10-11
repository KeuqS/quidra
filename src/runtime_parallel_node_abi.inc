#include "quidra/abi/parallel_block.h"

namespace quidra::runtime_parallel::detail {
struct JoinedLanguageBlock {
    void* error{};
    std::shared_ptr<quidra::runtime::OwnedNodeReport> report;
    std::optional<int> exit_status;
    bool invalid_status{};
};
JoinedLanguageBlock join_language_block(const void* const* pointers,
    const std::uint64_t* numbers,void* const* frames,std::uint32_t count,
    quidra::runtime::ModuleState state) {
    std::vector<NodeSpec> nodes(count);
    for(std::uint32_t i=0;i<count;++i) {
        auto& node=nodes[i];
        node.body=reinterpret_cast<std::uint8_t(*)(void*)>(const_cast<void*>(pointers[i*5]));
        node.trace_body=pointers[i*5+1];
        node.predecessors=static_cast<const std::uint32_t*>(pointers[i*5+2]);
        node.predecessor_count=static_cast<std::uint32_t>(numbers[i*4]);
        node.frame=frames[i];node.worker_safe=numbers[i*4+1]!=0;node.module_state=state;
        node.display_name=static_cast<const char*>(pointers[i*5+4]);
        node.line=numbers[i*4+2];node.column=numbers[i*4+3];
        if(numbers[i*4]>std::numeric_limits<std::uint32_t>::max() || !node.frame)
            throw std::invalid_argument("invalid parallel node frame");
    }
    auto selected=run_shared_nodes(nodes.data(),count);
    // Results made by fallible nodes currently stay on the caller. The
    // worker-safe proof excludes managed output storage and fallible nodes.
    // Clear receipt slots before invoking generated drops so cleanup cannot
    // double-release a box if a drop itself reports a runtime failure.
    for(std::uint32_t i=0;i<count;++i) {
        if(selected.status==1 && selected.index==i && !selected.report && !selected.exit_status)continue;
        const auto drop=reinterpret_cast<void(*)(void*)>(const_cast<void*>(pointers[i*5+3]));
        if(!drop || !*static_cast<void**>(frames[i]))continue;
        quidra::runtime::NodeFailureScope cleanup(state);
        struct Drop {void(*body)(void*);void* frame;} invocation{drop,frames[i]};
        const bool okay=quidra::runtime::invoke_node_body(&cleanup,[](void* raw){
            auto& invocation=*static_cast<Drop*>(raw);invocation.body(invocation.frame);
        },&invocation);
        if(!okay && (!selected.status || i<selected.index)) {
            // If cleanup supersedes a normal error representative, release
            // its retained cell too. A failure in that cleanup belongs to the
            // earlier representative already selected and cannot replace it.
            if(selected.status==1 && selected.index<count) {
                const auto old=selected.index;
                const auto old_drop=reinterpret_cast<void(*)(void*)>(const_cast<void*>(pointers[old*5+3]));
                if(old_drop && *static_cast<void**>(frames[old])) {
                    quidra::runtime::NodeFailureScope old_cleanup(state);
                    Drop old_invocation{old_drop,frames[old]};
                    quidra::runtime::invoke_node_body(&old_cleanup,[](void* raw){
                        auto& invocation=*static_cast<Drop*>(raw);invocation.body(invocation.frame);
                    },&old_invocation);
                }
            }
            selected.index=i;selected.status=101;
            selected.report=std::move(cleanup.report);selected.exit_status=cleanup.exit_status;
            if(selected.report)selected.report->append_join(nodes[i].display_name,nodes[i].line,nodes[i].column,quidra::runtime::walk_call_path());
        }
    }
    JoinedLanguageBlock result;
    result.report=std::move(selected.report);result.exit_status=selected.exit_status;
    if(selected.status==1 && selected.index<count && !result.report && !result.exit_status) {
        auto& error=*static_cast<void**>(frames[selected.index]);result.error=error;error=nullptr;
        result.invalid_status=!result.error;
    }else result.invalid_status=selected.status!=0 && !result.report && !result.exit_status;
    return result;
}
}
extern "C" void* quidra_parallel_block(const void* const* pointers,const std::uint64_t* numbers,
    void* const* frames,std::uint32_t count,quidra_parallel_module_state state,
    unsigned long long line,unsigned long long column) {
    using namespace quidra::runtime_parallel::detail;
    JoinedLanguageBlock result;
    std::string start_error;
    try {
        if(count && (!pointers || !numbers || !frames))throw std::invalid_argument("invalid parallel node table");
        quidra::device::check_package_hold_returned("a parallel block started");
        result=join_language_block(pointers,numbers,frames,count,state);
    }catch(const quidra::runtime::CapturedNodeFailure&){throw;}
    catch(const std::exception& error){start_error=error.what();}
    // No scheduler vectors, synchronization locks or worker invocations
    // remain alive when an outcome propagates into the enclosing node.
    if(!start_error.empty() || result.invalid_status)
        quidra::runtime::report_failure(quidra::abi::FailureReason::parallel_start_failed,
            quidra::abi::FailureArgs{.message=start_error.empty()?"invalid parallel node outcome":start_error},line,column);
    if(result.report) {
        if(quidra::runtime::current_node_failure) {
            const auto& report=*result.report;
            quidra::runtime::current_node_failure->report=std::make_unique<quidra::runtime::OwnedNodeReport>(report.head(),report.location(),report.message(),report.data(),report.raw_site());
            throw quidra::runtime::CapturedNodeFailure{};
        }
        result.report->write();std::exit(quidra::abi::failure_exit_status);
    }
    if(result.exit_status) {
        if(quidra::runtime::current_node_failure)quidra::runtime::capture_node_exit(*result.exit_status);
        std::exit(*result.exit_status);
    }
    return result.error;
}

namespace quidra::runtime_parallel::detail {
// Only the configured worker count is materialized. Each claimed ordinal is
// a separate language node, including its ownership frame and deferred drain.
JoinedLanguageBlock join_language_iterations(const void* const* pointers,
    const std::uint64_t* numbers,void* const* captures,std::uint32_t capture_count,
    std::uint64_t count,bool worker_safe,quidra::runtime::ModuleState state) {
    if(count==0)return {};
    struct Shared {
        const void* const* pointers;const std::uint64_t* numbers;
        quidra::runtime::ModuleState state;
        std::uint64_t count;
        std::atomic<std::uint64_t> next{0},failed{std::numeric_limits<std::uint64_t>::max()};
        std::mutex mutex{};
        JoinedLanguageBlock selected{};
    } shared{pointers,numbers,state,count};
    struct Worker {Shared* shared{};std::uint64_t ordinal{};std::vector<void*> frame;};
    const auto workers=worker_safe?std::min(count,configured_thread_count()):1;
    std::vector<Worker> frames(workers);
    std::vector<NodeSpec> nodes(workers);
    for(std::size_t i=0;i<workers;++i) {
        auto& frame=frames[i];frame.shared=&shared;frame.frame.resize(static_cast<std::size_t>(capture_count)+2);
        if(capture_count)std::copy(captures,captures+capture_count,frame.frame.begin()+1);
        frame.frame.back()=&frame.ordinal;
        nodes[i].frame=&frame;nodes[i].worker_safe=worker_safe;nodes[i].module_state=state;
        nodes[i].body=[](void* raw)->std::uint8_t {
            auto& frame=*static_cast<Worker*>(raw);auto& shared=*frame.shared;
            for(;;) {
                const auto ordinal=shared.next.fetch_add(1,std::memory_order_relaxed);
                if(ordinal>=shared.count)return 0;
                frame.ordinal=ordinal;frame.frame[0]=nullptr;
                void* individual=frame.frame.data();
                std::uint64_t numbers[4]{0,0,shared.numbers[2],shared.numbers[3]};
                quidra::runtime::NodeFailureScope iteration(shared.state);
                struct Invocation {Shared* shared;std::uint64_t* numbers;void** individual;JoinedLanguageBlock result;} call{&shared,numbers,&individual,{}};
                const bool returned=quidra::runtime::invoke_node_body(&iteration,[](void* raw) {
                    auto& call=*static_cast<Invocation*>(raw);
                    call.result=join_language_block(call.shared->pointers,call.numbers,call.individual,1,call.shared->state);
                },&call);
                auto result=std::move(call.result);
                if(!returned) {result.report=std::move(iteration.report);result.exit_status=iteration.exit_status;result.invalid_status=!result.report&&!result.exit_status;}
                if(result.error||result.report||result.exit_status||result.invalid_status) {
                    std::lock_guard guard(shared.mutex);
                    if(ordinal<shared.failed.load(std::memory_order_relaxed)) {
                        // Iterations are nonfallible void nodes. Retain only
                        // the lowest logical ordinal's report or process exit;
                        // every independent iteration still runs and drains.
                        shared.selected=std::move(result);
                        shared.failed.store(ordinal,std::memory_order_release);
                    }
                }
            }
        };
    }
    const auto outer=run_shared_nodes(nodes.data(),static_cast<std::uint32_t>(workers));
    if(outer.status && !shared.selected.report && !shared.selected.exit_status) {
        shared.selected.report=outer.report;shared.selected.exit_status=outer.exit_status;
        shared.selected.invalid_status=!outer.report&&!outer.exit_status;
    }
    return std::move(shared.selected);
}
}
extern "C" void* quidra_parallel_iterations(const void* const* pointers,const std::uint64_t* numbers,
    void* const* captures,std::uint32_t capture_count,std::uint64_t count,bool worker_safe,
    quidra_parallel_module_state state,unsigned long long line,unsigned long long column) {
    using namespace quidra::runtime_parallel::detail;
    JoinedLanguageBlock result;std::string start_error;
    try {
        if(!pointers||!numbers||!pointers[0]||numbers[0]||pointers[3]||
           count>static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max())||
           (capture_count&&!captures)||capture_count==std::numeric_limits<std::uint32_t>::max())
            throw std::invalid_argument("invalid parallel iteration table");
        quidra::device::check_package_hold_returned("parallel iterations started");
        result=join_language_iterations(pointers,numbers,captures,capture_count,count,worker_safe,state);
    } catch(const quidra::runtime::CapturedNodeFailure&){throw;}
    catch(const std::exception& error){start_error=error.what();}
    if(!start_error.empty()||result.invalid_status)
        quidra::runtime::report_failure(quidra::abi::FailureReason::parallel_start_failed,
            quidra::abi::FailureArgs{.message=start_error.empty()?"invalid parallel iteration outcome":start_error},line,column);
    if(result.report) {
        if(quidra::runtime::current_node_failure) {
            const auto& report=*result.report;
            quidra::runtime::current_node_failure->report=std::make_unique<quidra::runtime::OwnedNodeReport>(report.head(),report.location(),report.message(),report.data(),report.raw_site());
            throw quidra::runtime::CapturedNodeFailure{};
        }
        result.report->write();std::exit(quidra::abi::failure_exit_status);
    }
    if(result.exit_status) {
        if(quidra::runtime::current_node_failure)quidra::runtime::capture_node_exit(*result.exit_status);
        std::exit(*result.exit_status);
    }
    return result.error;
}
