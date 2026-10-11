#pragma once
#include "quidra/ir/module.hpp"
#include <cstdint>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>
#include <type_traits>
#include <utility>
#include <limits>
namespace quidra::llvm_backend {
enum class ResultOwner { unresolved, unmanaged, borrowed, owned, alias };
enum class OwnerOrigin { none, value, local, reference, field, element, variant_payload };
struct OwnershipOrigin {
    OwnerOrigin kind{};
    ir::ValueId value{};
    std::string storage;
    bool operator==(const OwnershipOrigin&)const=default;
};
struct OwnedValueRecord {
    ir::ValueId value{};
    Type type{Type::simple(TypeKind::Void)};
    ResultOwner ownership{ResultOwner::unresolved};
    OwnershipOrigin origin;
    const ir::Instruction* producer{};
    std::uint64_t offset{};
};
struct OwnedPinRecord {
    const ir::Instruction* instruction{};
    ir::ValueId target{};
    std::uint64_t offset{};
};
// Reserved before function entry; typed contracts are resolved by the
// owning domain before its result is emitted. Reserving every result gives
// no domain permission to treat an unknown result as owned or borrowed.
class OwnedValuePlan {
public:
    static constexpr std::uint64_t value_cell_bytes=32;
    static constexpr std::uint64_t origin_link_bytes=8;
    static constexpr std::uint64_t cell_stride=48;
    void reserve(const ir::Function& function,std::uint64_t first_offset) {
        values_.clear();pins_.clear();next_offset_=aligned(first_offset);
        for(const auto& block:function.blocks)for(const auto& instruction:block.instructions)
            std::visit([&](const auto& node){
                if constexpr(requires{node.out;}) {
                    if(node.out) {
                        if(values_.contains(node.out))throw std::logic_error("duplicate final-IR ownership result");
                        values_.emplace(node.out,OwnedValueRecord{node.out,Type::simple(TypeKind::Void),ResultOwner::unresolved,{},&instruction,next_offset_});
                        advance();
                    }
                }
                if constexpr(std::is_same_v<std::decay_t<decltype(node)>,ir::Pin>) {
                    pins_.push_back({&instruction,node.value,next_offset_});advance();
                }
            },instruction);
    }
    void resolve(ir::ValueId value,const Type& type,ResultOwner ownership,OwnershipOrigin origin={}) {
        auto& record=values_.at(value);
        if(record.ownership!=ResultOwner::unresolved && (record.type!=type || record.ownership!=ownership || record.origin!=origin))
            throw std::logic_error("conflicting final-IR ownership contract");
        if(ownership==ResultOwner::unresolved)throw std::logic_error("unresolved ownership contract supplied");
        if(ownership==ResultOwner::alias && origin.kind==OwnerOrigin::none)
            throw std::logic_error("owned alias lacks an origin");
        record.type=type;record.ownership=ownership;record.origin=std::move(origin);
    }
    const OwnedValueRecord& value(ir::ValueId id)const{return values_.at(id);}
    const std::map<ir::ValueId,OwnedValueRecord>& values()const{return values_;}
    const std::vector<OwnedPinRecord>& pins()const{return pins_;}
    std::uint64_t bytes()const{return next_offset_;}
    void require_resolved()const {
        for(const auto& [_,value]:values_)if(value.ownership==ResultOwner::unresolved)
            throw std::logic_error("node result lacks an explicit ownership contract");
    }
    std::optional<ir::ValueId> value_origin(ir::ValueId id)const {
        std::size_t remaining=values_.size()+1;
        while(remaining--) {
            const auto& record=value(id);
            if(record.ownership==ResultOwner::owned)return id;
            if(record.ownership!=ResultOwner::alias || record.origin.kind!=OwnerOrigin::value)return {};
            id=record.origin.value;
        }
        throw std::logic_error("cyclic final-IR ownership alias");
    }
private:
    static std::uint64_t aligned(std::uint64_t n){
        if(n>std::numeric_limits<std::uint64_t>::max()-15)throw std::logic_error("node ownership frame overflow");
        return (n+15)&~std::uint64_t{15};
    }
    void advance(){
        if(next_offset_>std::numeric_limits<std::uint64_t>::max()-cell_stride)throw std::logic_error("node ownership frame overflow");
        next_offset_+=cell_stride;
    }
    std::map<ir::ValueId,OwnedValueRecord> values_;
    std::vector<OwnedPinRecord> pins_;
    std::uint64_t next_offset_{};
};
}
