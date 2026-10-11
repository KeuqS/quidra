#include "llvm_backend/call_acceptance_emitter.hpp"
#include <limits>
#include <stdexcept>
namespace quidra::llvm_backend {
using namespace llvm_text;
using namespace llvm_text::types;
namespace {
inline constexpr auto begin_abi=llvm_callee<decltype(&quidra_parallel_call_begin)>("quidra_parallel_call_begin");
inline constexpr auto accept_abi=llvm_callee<decltype(&quidra_parallel_call_accept)>("quidra_parallel_call_accept");
inline constexpr auto require_abi=llvm_callee<decltype(&quidra_parallel_call_require_accept)>("quidra_parallel_call_require_accept");
inline constexpr auto end_abi=llvm_callee<decltype(&quidra_parallel_call_end)>("quidra_parallel_call_end");
}
void CallAcceptanceEmitter::reserve(const ir::Instruction& instruction,std::size_t count) {
    if(count>std::numeric_limits<std::uint32_t>::max())throw std::logic_error("too many owning call arguments");
    if(!count)return;
    if(tables_.contains(&instruction))throw std::logic_error("duplicate call ownership table");
    // reserve first, then identify its appended position without assuming
    // the call domain owns the instruction's first scratch reservation.
    std::size_t index=0;
    for(;;++index) {
        try { (void)scratch_.instruction_slot(instruction,index); }
        catch(const std::logic_error&) { break; }
    }
    scratch_.reserve(instruction,LlvmType::array(count*2,ptr),Align::none);
    tables_[&instruction]=scratch_.instruction_slot(instruction,index);
}
std::string CallAcceptanceEmitter::begin(const ir::Instruction& instruction,const std::string& target,
    const std::vector<CallArgumentOwnerLocation>& owners,bool target_is_operand) {
    if(owners.empty())return {};
    const auto& table=tables_.at(&instruction);
    for(std::size_t i=0;i<owners.size();++i) {
        if(owners[i].stable_cell.empty() || owners[i].clear_symbol.empty())throw std::logic_error("owning argument lacks a stable mirror");
        const auto address=names_.value("ownership.argument"),clear=names_.value("ownership.clear");
        builder_.getelementptr(address,Inbounds::no,ptr,table,{{i64,i*2}});
        builder_.store({ptr,owners[i].stable_cell},address,Align::none);
        builder_.getelementptr(clear,Inbounds::no,ptr,table,{{i64,i*2+1}});
        builder_.store({ptr,owners[i].clear_is_operand?LlvmOperand(owners[i].clear_symbol):LlvmOperand::global(owners[i].clear_symbol)},clear,Align::none);
    }
    const auto ticket=names_.value("ownership.ticket");
    builder_.call(ticket,begin_abi,{{ptr,target_is_operand?LlvmOperand(target):LlvmOperand::global(target)},{ptr,table},{i32,owners.size()}});
    return ticket;
}
void CallAcceptanceEmitter::accept(const std::string& target) {
    builder_.call(accept_abi,{{ptr,LlvmOperand::global(target)}});
}
std::string CallAcceptanceEmitter::end(const std::string& ticket) {
    if(ticket.empty())return {};
    const auto accepted=names_.value("ownership.accepted");builder_.call(accepted,end_abi,{{ptr,ticket}});
    builder_.call(require_abi,{{i1,accepted}});return accepted;
}
}
