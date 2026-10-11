#pragma once
#include "quidra/types.hpp"
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace quidra {
struct ClassTypeInfo;
struct TraversalNode {
    enum class Kind { Visit, Fields, Field, Array, TupleElement } kind{Kind::Fields};
    Type type;
    std::string name;
    std::size_t index{};
    std::vector<TraversalNode> children;
};
struct Expr;
struct TraversalRootStep {TraversalNode::Kind kind;std::string name;std::size_t index{};};
struct TraversalBinding {const Expr* root{};std::vector<TraversalRootStep> prefix;bool borrowed{true};};
struct TraversalPlan {
    Type root,element;
    TraversalNode tree;
    bool writable{};
    bool empty{true};
};
struct TraversalPolicy {
    bool writable{};
    bool internal{};
    std::string module;
};
class TraversalError : public std::runtime_error {
public: using std::runtime_error::runtime_error;
};
TraversalPlan make_traversal_plan(const Type& root,const Type& element,
    const std::unordered_map<std::string,ClassTypeInfo>& classes,
    const TraversalPolicy& policy);
}
