#pragma once
#include "deferred_node.hpp"
#include "node_failure.hpp"
#include <cfenv>

namespace quidra::runtime_parallel::detail {
struct DeferredContext {
    runtime::NodeSourceState source{};
    runtime::ModuleState module{};
    std::uint64_t values[3]{};
    std::fenv_t environment{};
    bool has_environment{};
    std::shared_ptr<std::unique_ptr<runtime::OwnedNodeReport>> report_owner;
};
inline std::shared_ptr<void> capture_deferred_context() {
    auto context=std::make_shared<DeferredContext>();
    context->report_owner=std::make_shared<std::unique_ptr<runtime::OwnedNodeReport>>();
    context->source=runtime::save_node_source_state();
    if(runtime::current_node_failure) context->module=runtime::current_node_failure->module_state;
    runtime::snapshot_module_state(context->module,context->values);
    context->has_environment=std::fegetenv(&context->environment)==0;
    return context;
}
inline DeferredFailure run_deferred_callback(void(*body)(void*),void* frame,
                                             const std::shared_ptr<void>& raw) {
    const auto& context=*std::static_pointer_cast<DeferredContext>(raw);
    struct Environment {
        std::fenv_t saved{};
        bool restore{};
        explicit Environment(const DeferredContext& context) {
            restore=context.has_environment && std::fegetenv(&saved)==0;
            if(restore) std::fesetenv(&context.environment);
        }
        ~Environment() {
            if(restore) {
                if(current_deferred_node) current_deferred_node->add_exceptions(std::fetestexcept(FE_ALL_EXCEPT));
                std::fesetenv(&saved);
            }
        }
    } environment(context);
    runtime::NodeFailureScope scope(context.module);
    runtime::restore_node_source_state(context.source);
    std::uint64_t values[3]{context.values[0],context.values[1],context.values[2]};
    if(context.module) context.module(values,true);
    const bool success=runtime::invoke_node_body(&scope,body,frame);
    DeferredFailure outcome;
    if(!success) {
        *context.report_owner=std::move(scope.report);
        if(*context.report_owner)outcome.report=std::shared_ptr<runtime::OwnedNodeReport>(
            context.report_owner,context.report_owner->get());
        outcome.exit_status=scope.exit_status;
    }
    return outcome;
}
[[noreturn]] inline void raise_deferred_failure(const DeferredFailure& failure) {
    if(failure.exit_status) runtime::capture_node_exit(*failure.exit_status);
    if(failure.report) {
        const auto& report=*failure.report;
        runtime::capture_node_failure(report.head(),report.location(),report.message(),report.data(),report.raw_site());
    }
    const auto reason=abi::FailureReason::deferred_check_failed;
    const abi::FailureArgs args{.message=failure.message};
    runtime::ReportMessage message;
    abi::write_failure_message(reason,args,[&](std::string_view piece) {message.append(piece);});
    const auto site=failure.raw_site.value_or(runtime::report_site(0,0,runtime::current_user_statement()));
    const runtime::ReportHead head{runtime::ReportKind::coded,abi::spelling(abi::failure_reason_info(reason).code)};
    runtime::ReportData data;
    data.reason=&reason;data.args=args;data.provenance=site.statement;
    runtime::capture_node_failure(head,runtime::locate_report_site(site),message.text(),data,site);
}
inline std::shared_ptr<DeferredNode> make_deferred_node() {
    auto owner=std::make_shared<DeferredNode>();
    owner->capture_callback_context=capture_deferred_context;
    owner->run_callback=run_deferred_callback;
    owner->raise_failure=raise_deferred_failure;
    return owner;
}
} // namespace quidra::runtime_parallel::detail
