#pragma once
#include "llvm_backend/scratch_planner.hpp"
#include "llvm_backend/temporary_names.hpp"
#include "llvm_text/llvm_builder.hpp"
#include "quidra/abi/parallel_call_ownership.h"
#include <map>
#include <string>
#include <vector>
namespace quidra::llvm_backend {
struct CallArgumentOwnerLocation {
    std::string stable_cell;
    std::string clear_symbol;
    bool clear_is_operand{};
};
// Actual argument contracts and stable mirror selection are supplied by
// OwnedValuePlan. This emitter never guesses a foreign consumption policy.
class CallAcceptanceEmitter {
public:
    CallAcceptanceEmitter(llvm_text::LlvmBuilder& builder,ScratchPlanner& scratch,TemporaryNames& names)
        :builder_(builder),scratch_(scratch),names_(names){}
    void reserve(const ir::Instruction& instruction,std::size_t owned_arguments);
    std::string begin(const ir::Instruction& instruction,const std::string& canonical_target,
                      const std::vector<CallArgumentOwnerLocation>& owners,bool target_is_operand=false);
    void accept(const std::string& canonical_target);
    // An empty return means there was no ticket. Otherwise the caller must
    // emitter checks this boolean before returning; false is a
    // compiler/runtime ownership contract violation, not a normal node error.
    std::string end(const std::string& ticket);
private:
    std::map<const ir::Instruction*,std::string> tables_;
    llvm_text::LlvmBuilder& builder_;
    ScratchPlanner& scratch_;
    TemporaryNames& names_;
};
}
