#pragma once

// DwarfLines: the subset of an object's DWARF that the call-site table
// needs (toolchain/call_site_table.hpp): the rows of the line programs and
// the tree of subprograms and inlined subroutines.
//
// - .debug_line: version 2 to 4 line programs (the standard, extended and
//   special opcodes, discriminators included; the file table is skipped).
// - .debug_info: version 2 to 4 units with 8-byte addresses;
//   DW_TAG_subprogram and DW_TAG_inlined_subroutine with DW_AT_low_pc,
//   DW_AT_high_pc, DW_AT_ranges (.debug_ranges), DW_AT_call_line,
//   DW_AT_abstract_origin, DW_AT_specification, DW_AT_linkage_name and DW_AT_name
//   (DW_FORM_strp into .debug_str, or DW_FORM_string), linkage identity first. Other attributes are
//   skipped by their form's size; a lexical block is transparent.
//
// An unexpected version, form or 64-bit unit throws std::runtime_error
// naming the object: the table is never built from a misread.

#include "toolchain/object_file.hpp"

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace quidra::toolchain {

struct DwarfLineRow {
    std::uint64_t address{};
    std::uint32_t line{};
    std::uint32_t column{};
    std::uint32_t discriminator{};
    // The row that ends a sequence: its address is one past the sequence.
    bool end_sequence{};
};

// [begin, end) address ranges.
using DwarfRanges = std::vector<std::pair<std::uint64_t, std::uint64_t>>;

struct DwarfInlined {
    DwarfRanges ranges;
    std::uint32_t call_line{};
    // The inlined function's name (through its abstract origin).
    std::string name;
    std::vector<DwarfInlined> children;
};

struct DwarfSubprogram {
    // The name (through its abstract origin or specification).
    std::string name;
    DwarfRanges ranges;
    std::vector<DwarfInlined> inlined;
};

struct DwarfLines {
    // Every sequence's rows in program order (each ending with its
    // end_sequence row).
    std::vector<DwarfLineRow> rows;
    // The concrete subprograms (those with code).
    std::vector<DwarfSubprogram> subprograms;
};

// The line rows and subprograms of `object`; empty when it has no DWARF.
DwarfLines read_dwarf_lines(const ObjectFile& object);

} // namespace quidra::toolchain
