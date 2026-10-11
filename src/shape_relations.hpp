#pragma once

#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace quidra {

inline std::vector<std::string> shape_relation_parameters(std::string_view text) {
    std::vector<std::string> result;
    std::set<std::string> seen;
    std::size_t start = 0;
    while (start <= text.size()) {
        const auto comma = text.find(',', start);
        const auto end = comma == std::string_view::npos ? text.size() : comma;
        auto name = text.substr(start, end - start);
        const auto first = name.find_first_not_of(" \t\r");
        const auto last = name.find_last_not_of(" \t\r");
        if (first == std::string_view::npos)
            throw std::invalid_argument("same_shape requires distinct tensor parameter identifiers");
        name = name.substr(first, last - first + 1);
        const auto letter = [](char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'; };
        if (!letter(name.front()))
            throw std::invalid_argument("same_shape requires tensor parameter identifiers");
        for (const auto c : name)
            if (!letter(c) && !(c >= '0' && c <= '9'))
                throw std::invalid_argument("same_shape requires tensor parameter identifiers");
        if (!seen.emplace(name).second)
            throw std::invalid_argument("same_shape requires distinct tensor parameter identifiers");
        result.emplace_back(name);
        if (comma == std::string_view::npos) break;
        start = comma + 1;
    }
    if (result.size() < 2)
        throw std::invalid_argument("same_shape requires at least two tensor parameter identifiers");
    return result;
}

} // namespace quidra
