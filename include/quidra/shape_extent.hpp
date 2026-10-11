#pragma once

#include "quidra/shape_coefficient.hpp"

#include <algorithm>
#include <map>
#include <functional>
#include <string>
#include <cstdint>
#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

namespace quidra {

// A tensor extent is a fact about one runtime value. Different symbolic
// expressions never prove a difference in values; only identical canonical
// forms prove equality. Symbols are local to one checked function body.
struct ShapeTerm {
    ShapeCoefficient coefficient;
    std::vector<std::string> factors;
    bool operator==(const ShapeTerm&) const = default;
};

struct ShapeExtent {
    enum class Kind : std::uint8_t { Unknown, Known, Symbol, Broadcast, Expr };
    Kind kind{Kind::Unknown};
    std::int64_t value{};
    std::vector<std::int64_t> symbols;
    std::vector<ShapeTerm> terms;
    std::vector<ShapeExtent> operands;
    std::map<std::string, std::vector<ShapeExtent>> atom_operands;
    std::map<std::string, std::string> atom_operations;

    ShapeExtent() = default;
    ShapeExtent(long long extent)
        : kind(extent >= 0 ? Kind::Known : Kind::Unknown), value(extent >= 0 ? extent : 0) {}

    static ShapeExtent symbol(std::int64_t id) {
        ShapeExtent extent;
        extent.kind = Kind::Symbol;
        extent.value = id;
        return extent;
    }

    std::optional<long long> known() const {
        if (kind == Kind::Known) return value;
        return std::nullopt;
    }

    bool operator==(const ShapeExtent& other) const {
        if (kind != other.kind) return false;
        if (kind == Kind::Expr) return terms == other.terms;
        if (kind == Kind::Broadcast)
            return operands.empty() && other.operands.empty() ? symbols == other.symbols
                : operands == other.operands;
        return value == other.value;
    }
};

// A result fact expressed in the callee's public input coordinates. Local
// symbolic operands of a broadcast become one fresh symbol at each call.
struct ExtentOrigin {
    enum class Kind : std::uint8_t { Unknown, Known, ParameterAxis, ParameterValue, Broadcast, Expr };
    Kind kind{Kind::Unknown};
    long long value{};
    std::size_t parameter{};
    std::size_t axis{};
    std::vector<std::pair<std::size_t, std::size_t>> axes;
    bool local{};
    ShapeExtent expression;
    std::map<std::int64_t, std::pair<std::size_t, std::size_t>> expression_axes;
    bool operator==(const ExtentOrigin&) const = default;
};

inline bool same_extent(const ShapeExtent& left, const ShapeExtent& right) {
    return left.kind != ShapeExtent::Kind::Unknown && left == right;
}

inline std::string canonical_extent_key(const ShapeExtent& extent) {
    using Kind = ShapeExtent::Kind;
    if (extent.kind == Kind::Unknown) return "?";
    if (extent.kind == Kind::Known) return "k" + std::to_string(extent.value);
    if (extent.kind == Kind::Symbol) return "s" + std::to_string(extent.value);
    if (extent.kind == Kind::Expr) {
        std::string key = "p[";
        for (const auto& term : extent.terms) {
            key += term.coefficient.text() + ":";
            for (const auto& factor : term.factors)
                key += std::to_string(factor.size()) + ":" + factor;
            key += ";";
        }
        return key + "]";
    }
    std::string key = "b[";
    if (!extent.operands.empty()) {
        for (const auto& operand : extent.operands) {
            const auto part = canonical_extent_key(operand);
            key += std::to_string(part.size()) + ":" + part;
        }
    } else {
        for (const auto symbol : extent.symbols) key += "s" + std::to_string(symbol) + ";";
    }
    return key + "]";
}

inline std::vector<ShapeTerm> extent_terms(const ShapeExtent& extent) {
    using Kind = ShapeExtent::Kind;
    if (extent.kind == Kind::Known) return {{ShapeCoefficient(extent.value), {}}};
    if (extent.kind == Kind::Expr) return extent.terms;
    return {{ShapeCoefficient(1), {canonical_extent_key(extent)}}};
}

inline ShapeExtent canonical_extent_expression(std::vector<ShapeTerm> terms,
                                              std::vector<std::int64_t> symbols) {
    std::map<std::vector<std::string>, ShapeCoefficient> merged;
    for (auto& term : terms) {
        std::sort(term.factors.begin(), term.factors.end());
        merged[term.factors] = merged[term.factors] + term.coefficient;
    }
    ShapeExtent result;
    result.kind = ShapeExtent::Kind::Expr;
    for (auto& [factors, coefficient] : merged)
        if (!coefficient.zero()) result.terms.push_back({std::move(coefficient), factors});
    if (result.terms.empty()) return ShapeExtent(0);
    if (result.terms.size() == 1 && result.terms.front().factors.empty()) {
        if (const auto known = result.terms.front().coefficient.nonnegative_word())
            return ShapeExtent(*known);
    }
    const auto direct_symbol = [](const std::string& factor) {
        return factor.size() > 1 && factor.front() == 's' &&
            std::all_of(factor.begin() + 1, factor.end(), [](char c) { return c >= '0' && c <= '9'; });
    };
    if (result.terms.size() == 1 && result.terms.front().coefficient.one() &&
        result.terms.front().factors.size() == 1 && direct_symbol(result.terms.front().factors.front()))
        return ShapeExtent::symbol(std::stoll(result.terms.front().factors.front().substr(1)));
    std::vector<std::int64_t> direct_dependencies;
    bool opaque = false;
    for (const auto& term : result.terms) for (const auto& factor : term.factors) {
        if (direct_symbol(factor)) direct_dependencies.push_back(std::stoll(factor.substr(1)));
        else opaque = true;
    }
    if (!opaque) symbols = std::move(direct_dependencies);
    std::sort(symbols.begin(), symbols.end());
    symbols.erase(std::unique(symbols.begin(), symbols.end()), symbols.end());
    result.symbols = std::move(symbols);
    return result;
}

inline ShapeExtent extent_arithmetic(const std::string& operation,
                                    const ShapeExtent& left, const ShapeExtent& right) {
    using Kind = ShapeExtent::Kind;
    if (left.kind == Kind::Unknown || right.kind == Kind::Unknown) return {};
    std::vector<std::int64_t> symbols;
    const auto append_symbols = [&](const ShapeExtent& extent) {
        if (extent.kind == Kind::Symbol) symbols.push_back(extent.value);
        else symbols.insert(symbols.end(), extent.symbols.begin(), extent.symbols.end());
    };
    append_symbols(left); append_symbols(right);
    auto a = extent_terms(left), b = extent_terms(right);
    std::vector<ShapeTerm> terms;
    std::map<std::string, std::vector<ShapeExtent>> atom_operands;
    std::map<std::string, std::string> atom_operations;
    const auto collect = [&](const ShapeExtent& extent) {
        atom_operands.insert(extent.atom_operands.begin(), extent.atom_operands.end());
        atom_operations.insert(extent.atom_operations.begin(), extent.atom_operations.end());
        if (extent.kind == Kind::Broadcast) {
            const auto key = canonical_extent_key(extent);
            auto values = extent.operands;
            if (values.empty()) for (const auto id : extent.symbols) values.push_back(ShapeExtent::symbol(id));
            atom_operands[key] = std::move(values);
            atom_operations[key] = "broadcast";
        }
    };
    collect(left); collect(right);
    if (operation == "+" || operation == "-") {
        terms = std::move(a);
        for (auto& term : b) {
            if (operation == "-") term.coefficient = -term.coefficient;
            terms.push_back(std::move(term));
        }
    } else if (operation == "*") {
        for (const auto& x : a) for (const auto& y : b) {
            auto factors = x.factors;
            factors.insert(factors.end(), y.factors.begin(), y.factors.end());
            terms.push_back({x.coefficient * y.coefficient, std::move(factors)});
        }
    } else if (operation == "/" || operation == "%") {
        if (left.kind == Kind::Known && right.kind == Kind::Known && right.value != 0)
            return ShapeExtent(operation == "/" ? left.value / right.value : left.value % right.value);
        const auto key = operation + "(" + canonical_extent_key(left) + "," + canonical_extent_key(right) + ")";
        terms.push_back({ShapeCoefficient(1), {key}});
        atom_operands[key] = {left, right};
        atom_operations[key] = operation;
    } else return {};
    auto result = canonical_extent_expression(std::move(terms), std::move(symbols));
    result.atom_operands = std::move(atom_operands);
    result.atom_operations = std::move(atom_operations);
    return result;
}

// The shape check still runs. When it passes, a known non-unit extent is
// the result, and symbolic broadcasts flatten to a canonical symbol set.
inline ShapeExtent broadcast_extent(const ShapeExtent& left, const ShapeExtent& right) {
    using Kind = ShapeExtent::Kind;
    if (same_extent(left, right)) return left;
    const auto a = left.known();
    const auto b = right.known();
    if (a && *a == 1) return right;
    if (b && *b == 1) return left;
    if (a && b) return {};
    if (a) return left;
    if (b) return right;
    if (left.kind == Kind::Unknown || right.kind == Kind::Unknown) return {};
    ShapeExtent result;
    result.kind = Kind::Broadcast;
    if (left.kind == Kind::Expr || right.kind == Kind::Expr ||
        !left.operands.empty() || !right.operands.empty()) {
        const auto append_operand = [&](const ShapeExtent& extent) {
            if (extent.kind == Kind::Broadcast) {
                if (!extent.operands.empty())
                    result.operands.insert(result.operands.end(), extent.operands.begin(), extent.operands.end());
                else for (const auto symbol : extent.symbols)
                    result.operands.push_back(ShapeExtent::symbol(symbol));
            } else result.operands.push_back(extent);
        };
        append_operand(left); append_operand(right);
        std::sort(result.operands.begin(), result.operands.end(), [](const auto& a, const auto& b) {
            return canonical_extent_key(a) < canonical_extent_key(b);
        });
        result.operands.erase(std::unique(result.operands.begin(), result.operands.end()), result.operands.end());
        if (result.operands.size() == 1) return result.operands.front();
        for (const auto& operand : result.operands) {
            if (operand.kind == Kind::Symbol) result.symbols.push_back(operand.value);
            else result.symbols.insert(result.symbols.end(), operand.symbols.begin(), operand.symbols.end());
        }
        std::sort(result.symbols.begin(), result.symbols.end());
        result.symbols.erase(std::unique(result.symbols.begin(), result.symbols.end()), result.symbols.end());
        return result;
    }
    const auto append = [&](const ShapeExtent& extent) {
        if (extent.kind == Kind::Symbol) result.symbols.push_back(extent.value);
        else result.symbols.insert(result.symbols.end(), extent.symbols.begin(), extent.symbols.end());
    };
    append(left);
    append(right);
    std::sort(result.symbols.begin(), result.symbols.end());
    result.symbols.erase(std::unique(result.symbols.begin(), result.symbols.end()), result.symbols.end());
    if (result.symbols.size() == 1) return ShapeExtent::symbol(result.symbols.front());
    return result;
}

inline ShapeExtent substitute_extent(const ShapeExtent& extent,
                                     const std::function<ShapeExtent(std::int64_t)>& symbol) {
    using Kind = ShapeExtent::Kind;
    if (extent.kind == Kind::Unknown || extent.kind == Kind::Known) return extent;
    if (extent.kind == Kind::Symbol) return symbol(extent.value);
    if (extent.kind == Kind::Broadcast) {
        ShapeExtent result(1);
        if (extent.operands.empty()) {
            for (const auto id : extent.symbols) result = broadcast_extent(result, symbol(id));
        } else {
            for (const auto& operand : extent.operands)
                result = broadcast_extent(result, substitute_extent(operand, symbol));
        }
        return result;
    }
    ShapeExtent result(0);
    for (const auto& term : extent.terms) {
        auto product = canonical_extent_expression({{term.coefficient, {}}}, {});
        for (const auto& factor : term.factors) {
            ShapeExtent value;
            if (factor.size() > 1 && factor.front() == 's' &&
                std::all_of(factor.begin() + 1, factor.end(), [](char c) { return c >= '0' && c <= '9'; })) {
                value = symbol(std::stoll(factor.substr(1)));
            } else {
                const auto operation = extent.atom_operations.find(factor);
                const auto operands = extent.atom_operands.find(factor);
                if (operation == extent.atom_operations.end() || operands == extent.atom_operands.end())
                    return {};
                std::vector<ShapeExtent> inputs;
                for (const auto& operand : operands->second) inputs.push_back(substitute_extent(operand, symbol));
                if (operation->second == "broadcast") {
                    value = ShapeExtent(1);
                    for (const auto& input : inputs) value = broadcast_extent(value, input);
                } else if (inputs.size() == 2) {
                    value = extent_arithmetic(operation->second, inputs[0], inputs[1]);
                } else return {};
            }
            product = extent_arithmetic("*", product, value);
        }
        result = extent_arithmetic("+", result, product);
    }
    return result;
}

} // namespace quidra
