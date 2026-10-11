#pragma once
#include "ir/function_builder.hpp"
#include "quidra/ir/aggregate.hpp"
#include "quidra/ir/lifetime.hpp"

namespace quidra::lowering {
inline ir::ValueId copy_owned(ir::FunctionBuilder& builder,ir::ValueId value,const Type& type) {
    if(type.kind==TypeKind::Tuple && has_managed_elements(type)) {
        std::vector<ir::ValueId> elements;
        for(std::size_t i=0;i<type.parameters.size();++i) {
            auto element=builder.fresh();builder.emit(ir::TupleGet{element,value,i,type.parameters[i]});
            elements.push_back(copy_owned(builder,element,type.parameters[i]));
        }
        auto copy=builder.fresh();builder.emit(ir::TupleMake{copy,std::move(elements),type});return copy;
    }
    if(requires_value_clone(type)) {
        auto copy=builder.fresh();builder.emit(ir::Clone{copy,value,type});return copy;
    }
    if(uses_shared_immutable_storage(type)) {
        auto copy=builder.fresh();builder.emit(ir::Retain{copy,value,type});return copy;
    }
    return value;
}
// Keep a borrowed managed value alive without making a semantic value copy.
// Aggregate liveness follows its managed leaves, like aggregate release.
inline ir::ValueId retain_owned(ir::FunctionBuilder& builder,ir::ValueId value,const Type& type) {
    if(type.kind==TypeKind::Tuple && has_managed_elements(type)) {
        std::vector<ir::ValueId> elements;
        for(std::size_t i=0;i<type.parameters.size();++i) {
            auto element=builder.fresh();builder.emit(ir::TupleGet{element,value,i,type.parameters[i]});
            elements.push_back(retain_owned(builder,element,type.parameters[i]));
        }
        auto held=builder.fresh();builder.emit(ir::TupleMake{held,std::move(elements),type});return held;
    }
    if(requires_lifetime_management(type)) {
        auto held=builder.fresh();builder.emit(ir::Retain{held,value,type});return held;
    }
    return value;
}
inline void release_owned(ir::FunctionBuilder& builder,ir::ValueId value,const Type& type) {
    if(type.kind==TypeKind::Tuple) {
        for(std::size_t i=0;i<type.parameters.size();++i) if(owns_managed(type.parameters[i])) {
            auto element=builder.fresh();builder.emit(ir::TupleGet{element,value,i,type.parameters[i]});
            release_owned(builder,element,type.parameters[i]);
        }
    } else if(requires_lifetime_management(type)) builder.emit(ir::Release{value,type});
}
} // namespace quidra::lowering
