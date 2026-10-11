#pragma once
#include "quidra/types.hpp"
namespace quidra::llvm_backend {
// Function parameters describe a callable signature, not aggregate fields.
// Other parameter-bearing non-pointer value types carry their own children.
inline bool node_owns_value(const Type& type) {
    if(requires_lifetime_management(type) || type.kind==TypeKind::Real || is_bare_integer(type))return true;
    if(type.kind==TypeKind::Function)return false;
    for(const auto& child:type.parameters)if(node_owns_value(child))return true;
    return false;
}
}
