#pragma once
#include "quidra/ast.hpp"
namespace quidra {
// Both generic materialization and type checking select the same product shape.
template<class Candidate,class Children,class Leaf>
bool tuple_pattern_matches(const Pattern& pattern,const Candidate& candidate,Children children,Leaf leaf) {
    if(pattern.kind==Pattern::Kind::Tuple){const auto* elements=children(candidate);if(!elements || elements->size()!=pattern.elements.size())return false;for(std::size_t i=0;i<elements->size();++i)if(!tuple_pattern_matches(pattern.elements[i],(*elements)[i],children,leaf))return false;return true;}
    if(pattern.kind==Pattern::Kind::Discard || (pattern.type && pattern.type->name=="auto"))return true;
    return pattern.type && leaf(*pattern.type,candidate);
}
} // namespace quidra
