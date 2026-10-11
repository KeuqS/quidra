#pragma once

// The module's pool of string constants.
//
// Owns: every string constant of a module (@.str.N, numbered in the order of
// first interning, one constant per distinct value), the source provenance
// records of runtime failures (@.quidra.source.N, each pointing at interned
// strings), and the constant error records of the module's error sites (one
// abi::ErrorRecord, or an array of them indexed by a reason) with the texts
// only they use, both @.quidra.err.N, numbered by one counter apart from
// @.str.N, so that a record adds no name to the string constants, and the
// sites of the hops of errors (@.quidra.hop.N). All
// functions of a module share one pool, so the order in which emission
// interns strings is part of the output.

#include "quidra/ir/module.hpp"

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace quidra::llvm_backend {

struct SourceProvenanceConstant {
    std::string name;
    std::string file;
    std::string revision;
    std::string node_id;
    std::string node_kind;
    unsigned long long line{};
    unsigned long long column{};
};

// One slot of a constant error record: a text or name detail (the global of
// its text, empty for an absent one) or an integer detail.
struct ErrorRecordSlot {
    bool integer{};
    std::string global;
    long long value{};
    friend bool operator==(const ErrorRecordSlot&, const ErrorRecordSlot&) = default;
};

// A constant abi::ErrorRecord: its message and code (globals; an empty code
// is null, ERROR), its schema, its origin and its detail slots.
struct ErrorRecordConstant {
    std::string message;
    std::string code;
    unsigned schema{};
    unsigned long long line{};
    unsigned column{};
    std::vector<ErrorRecordSlot> slots;
    friend bool operator==(const ErrorRecordConstant&, const ErrorRecordConstant&) = default;
};

struct StringPool {
    std::vector<std::pair<std::string,std::string>> entries;
    std::unordered_map<std::string,std::string> names;
    std::vector<SourceProvenanceConstant> provenance_entries;
    // The caches of big integer literals (".int.literal.N"), in the order of
    // first interning, one per distinct spelling.
    std::vector<std::string> integer_literal_caches;
    std::unordered_map<std::string,std::string> integer_literal_names;
    // The slots of contextual constants (".exact.slot.N", float or double
    // globals), in the order of first interning, one per IR slot name.
    std::vector<std::pair<std::string,bool>> exact_slots;
    std::unordered_map<std::string,std::string> exact_slot_names;

    // The name of the constant holding value (".str.N"), created on first use.
    // Defined in the class: every string constant of the module passes
    // through it.
    std::string intern(const std::string& value) {
        if (auto it = names.find(value); it != names.end()) return it->second;
        auto name = ".str." + std::to_string(entries.size());
        entries.emplace_back(name, value);
        names.emplace(value, name);
        return name;
    }
    // The name of the cache of the big integer literal `spelling`
    // (".int.literal.N"), created on first use; the module defines it as an
    // i64 global holding 0 until the literal's word is made.
    std::string intern_integer_literal(const std::string& spelling) {
        if (auto it = integer_literal_names.find(spelling); it != integer_literal_names.end())
            return it->second;
        auto name = ".int.literal." + std::to_string(integer_literal_caches.size());
        integer_literal_caches.push_back(name);
        integer_literal_names.emplace(spelling, name);
        return name;
    }
    // The global of a contextual constant's slot, created on first use;
    // single says whether it holds a float (real32) or a double.
    std::string intern_exact_slot(const std::string& slot, bool single) {
        if (auto it = exact_slot_names.find(slot); it != exact_slot_names.end()) return it->second;
        auto name = ".exact.slot." + std::to_string(exact_slots.size());
        exact_slots.emplace_back(name, single);
        exact_slot_names.emplace(slot, name);
        return name;
    }
    // A new provenance record for location (".quidra.source.N"); its strings
    // are interned in the order file, revision, node id, node kind.
    std::string intern_provenance(const ir::SourceLocation& location);

    // The texts of constant error records (".quidra.err.N"), in the order of
    // first interning, one per distinct value.
    std::vector<std::pair<std::string,std::string>> error_texts;
    std::unordered_map<std::string,std::string> error_text_names;
    // The error record constants: their names and their LLVM text after
    // "constant " (the type and the initializer); an identical constant is
    // shared.
    std::vector<std::pair<std::string,std::string>> error_records;
    std::unordered_map<std::string,std::string> error_record_names;
    // The next number of an error text or record.
    std::size_t error_symbols{};

    std::string intern_error_text(const std::string& value) {
        if (auto it = error_text_names.find(value); it != error_text_names.end()) return it->second;
        auto name = ".quidra.err." + std::to_string(error_symbols++);
        error_texts.emplace_back(name, value);
        error_text_names.emplace(value, name);
        return name;
    }
    // The constant holding `records` (".quidra.err.N"): one record, or an
    // array when `array`; an identical constant is shared.
    std::string intern_error_records(std::vector<ErrorRecordConstant> records, bool array);
    // The hop sites (".quidra.hop.N", abi::ErrorHopSite): their names and
    // their LLVM text after "constant "; an identical site is shared.
    std::vector<std::pair<std::string,std::string>> hop_sites;
    std::unordered_map<std::string,std::string> hop_site_names;
    std::string intern_hop_site(const std::string& name, unsigned long long line,
                                unsigned long long column, unsigned kind);
};

} // namespace quidra::llvm_backend
