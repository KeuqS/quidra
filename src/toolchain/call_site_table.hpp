#pragma once

// The call-site table of a native artifact (docs/spec/architecture.md, "The
// call path of plain code"): built from the compiled module object and the
// backend's CallSiteInfo, written as an LLVM module (calls.ll) that the
// link compiles beside the object.
//
// Entries. One per function of the object that DWARF describes: its rows
// map an offset in the function's code to a chain of site ids, the site of
// the call the code belongs to and then the call site of each enclosing
// inlined function, innermost first. A row of line 0 (calls LLVM merged)
// keeps its place with the unknown site 0, preserving the DWARF
// inline callee identity separately. Each function's symbol is
// classified:
//   function  its DWARF name is one of CallSiteInfo's symbols;
//   fragment  <symbol>.cold.<N> of such a symbol (hot/cold splitting);
//   clone     <symbol>.<suffix> of such a symbol (a specialization);
//   unknown   anything else (an outlined function).
// An entry refers to its function by a 32-bit PC-relative offset (by its
// address on x86-64 Mach-O, which cannot relocate that difference). A local
// symbol (a fragment, a clone) cannot be named from another object: its
// entry refers to a global function that calls or branches to it and
// records the offset of that branch, which the walk decodes.
//
// Sections. Entries live in a section that the linker keeps exactly when
// it keeps the function: __DATA,__quidra_calls with the live_support
// attribute on Mach-O (and only `llvm.compiler.used`, so an entry keeps
// nothing alive); quidra_calls on ELF and .qcalls$m on COFF (whose
// functions all live in one kept text section). The shared table (the
// sites, the functions and their names) is one constant in its own kept
// section (__DATA,__quidra_sites, quidra_sites, .qsites$m). A library
// build's table module also defines the anchor its module references.
//
// Layout (all little-endian, 4-byte aligned): see abi/call_site_table.hpp.

#include "quidra/call_site_info.hpp"
#include "toolchain/dwarf_lines.hpp"
#include "toolchain/object_file.hpp"

#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace quidra::toolchain {

enum class CallSiteSymbolClass : std::uint8_t { function = 0, fragment = 1, clone = 2, unknown = 3 };

struct CallSiteTableRow {
    std::uint64_t offset{};
    // Site ids, innermost first.
    std::vector<std::uint32_t> chain;
    // Parallel to chain; no_function for the first (non-inline) site.
    std::vector<std::uint32_t> inline_callees;
};

struct CallSiteTableEntry {
    // The DWARF name and the symbol the entry refers to (its IR spelling).
    std::string name;
    std::string reference;
    // A local function: the offset in `reference`'s code of the branch to
    // it.
    std::optional<std::uint64_t> branch_offset;
    std::uint64_t code_size{};
    CallSiteSymbolClass symbol_class{CallSiteSymbolClass::unknown};
    // The function id (classes function, fragment and clone).
    std::uint32_t function{};
    std::vector<CallSiteTableRow> rows;
};

// The entries of an object's functions. Throws std::runtime_error naming
// the object when a row names a site the backend never recorded.
std::vector<CallSiteTableEntry> call_site_table_entries(const ObjectFile& object,
                                                        const DwarfLines& lines,
                                                        const CallSiteInfo& info);

// The table module's LLVM text.
std::string call_site_table_module(const std::vector<CallSiteTableEntry>& entries,
                                   const CallSiteInfo& info, ObjectFormat format,
                                   ObjectMachine machine);

// The table step of a native build: reads `object`, writes the table module
// to `output`.
void write_call_site_table(const std::filesystem::path& object, const CallSiteInfo& info,
                           const std::filesystem::path& output);

} // namespace quidra::toolchain
