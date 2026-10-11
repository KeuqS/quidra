#include "shape_relations.hpp"
#include "optimizer/static_tensor_facts.hpp"
#include <stdexcept>
#include <iostream>
static void require(bool condition) {
    if (!condition) throw std::runtime_error("shape relation assertion failed");
}

int main() {
    using namespace quidra;
    using namespace quidra::optimizer;
    require((shape_relation_parameters(" left, right ,third") == std::vector<std::string>{"left", "right", "third"}));
    for (const auto text : {"", "left", "left,left", "left,", ",right", "left,2right", "left,right.value", "left, right value"}) {
        bool rejected = false;
        try { (void)shape_relation_parameters(text); }
        catch (const std::invalid_argument&) { rejected = true; }
        require(rejected);
    }
    const auto make = [](std::vector<ShapeExtent> extents) {
        StaticTensorFacts result;
        result.has_type = true;
        result.type = Type::tensor(Type::simple(TypeKind::Real32), static_cast<long long>(extents.size()));
        result.extents = std::move(extents);
        return result;
    };
    const auto a = ShapeExtent::symbol(1), b = ShapeExtent::symbol(2);
    const auto left = make({a, broadcast_extent(a, b)});
    require(same_tensor_shape(left, make({a, broadcast_extent(b, a)})));
    require(!same_tensor_shape(left, make({b, broadcast_extent(a, b)})));
    require(!same_tensor_shape(make({ShapeExtent{}}), make({ShapeExtent{}})));
    require(!same_tensor_shape(make({2}), make({3})));
    require(!same_tensor_shape(make({2}), make({2, 3})));
    auto unknown = make({2}); unknown.type.length = -1;
    require(!same_tensor_shape(unknown, make({2})));
    auto invalid = make({}); invalid.type.kind = TypeKind::Invalid;
    require(!same_tensor_shape(invalid, make({})));
    ir::Function function;
    function.blocks.push_back({"entry", {
        ir::LoadLocal{1, "value", Type::tensor(Type::simple(TypeKind::Real32), 1, {}, {a})},
        ir::StoreLocal{"value", 1, Type::tensor(Type::simple(TypeKind::Real32), 1, {}, {a})},
        ir::LoadLocal{2, "value", Type::tensor(Type::simple(TypeKind::Real32), 1, {}, {b})}
    }});
    auto facts = StaticTensorFactsAnalysis::run(function);
    require(same_extent(facts.at(2).extents.at(0), b));
    std::cout << "shape relation schema and canonical same-call proof: ok\n";
}
