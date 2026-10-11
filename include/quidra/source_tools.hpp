#pragma once

#include "quidra/checker.hpp"

#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace quidra {

struct SourceNode {
    std::string node_id;
    std::string kind;
    SourceSpan span{};
    std::string source_hash;
    std::optional<Type> inferred_type;
    std::optional<std::string> authority;
    std::optional<std::string> parent_id;
    std::size_t depth{};
    // A name node resolved to a receiver member.
    bool this_qualified{};
    // A call or a declaration written with the mutation marker (L1).
    bool mutation_marker{};
    std::optional<bool> start_inclusive;
    std::optional<bool> end_inclusive;
    bool is_local{};
    bool self_reference{};
    std::string instance_name{};
    std::optional<std::size_t> collection_count;
};

struct SourceInspection {
    std::string revision;
    std::vector<SourceNode> nodes;
};

struct InspectOptions {
    bool include_source{true};
    bool include_effects{true};
    std::optional<std::string> kind;
    std::optional<std::size_t> max_depth;
};

std::string sha256_hex(std::string_view text);
SourceInspection inspect_syntax_source(std::string_view source);
SourceInspection inspect_source(std::string_view source, const CheckedProgram& checked);
std::string inspect_source_json(std::string_view source,
                                const CheckedProgram& checked,
                                std::string_view filename,
                                InspectOptions options = {});

} // namespace quidra
