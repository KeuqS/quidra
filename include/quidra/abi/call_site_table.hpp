#pragma once

// The call-site table's layout in a linked image, which the table module of
// a native build writes (toolchain/call_site_table.hpp) and the runtime's
// walk reads (runtime_trace.cpp). Little-endian, every part 4-byte aligned.
//
// The shared table, one per image (section quidra_sites):
//   SharedHeader, then function_count SharedFunction, then site_count
//   SharedSite (site 0 is the unknown site), then string_bytes of
//   NUL-terminated function names.
//
// The entries, one per kept function (section quidra_calls), one after the
// other; a zero word between them is padding:
//   u32 size        the entry's bytes, header included, a multiple of 4
//   i32 reference   the referenced function's address minus this field's
//   u32 code_size   the bytes of the entry's function
//   u32 identity    the function id (identity_function_mask), the symbol
//                   class (identity_class_shift), identity_absolute_bit
//                   (x86-64 Mach-O, whose assembler cannot subtract a
//                   symbol of another object: `reference` is 0 and the
//                   referenced function's address follows as an 8-byte
//                   pointer, the entry 8-aligned) and, for a local function,
//                   identity_branch_bit: a word follows with the offset of a
//                   branch to it in the referenced function
//   [u64 address]
//   [u32 branch_offset]
//   u32 row_bytes
//   u32 chain_bytes
//   rows            row_bytes of ULEB128 pairs: the row's offset from the
//                   previous row's (the first's from the function's start),
//                   its chain's byte offset in the chains
//   chains          chain_bytes: per chain a ULEB128 count, then that many
//                   ULEB128 pairs (site id, inline callee id + 1), innermost
//                   first; 0 encodes an unknown callee. The first callee
//                   is unknown; later callees preserve
//                   DWARF inline identities even when a merged site is 0
//   zero padding to a multiple of 4.
//
// Std-only.

#include <cstdint>

namespace quidra::abi::call_site_table {

inline constexpr std::uint32_t magic = 0x54534351;  // "QCST"
inline constexpr std::uint32_t version = 2;

namespace shared_flags {
// Site ids are the discriminators of a --debug build.
inline constexpr std::uint32_t debug = 1;
} // namespace shared_flags

struct SharedHeader {
    std::uint32_t magic;
    std::uint32_t version;
    std::uint32_t function_count;
    std::uint32_t site_count;
    std::uint32_t string_bytes;
    std::uint32_t flags;
};
static_assert(sizeof(SharedHeader) == 24);

struct SharedFunction {
    // The display name's offset in the strings.
    std::uint32_t name;
    // The function's sites: [first_site, first_site + site_count).
    std::uint32_t first_site;
    std::uint32_t site_count;
    // quidra::CallSiteFunctionKind and call_site_function_flags.
    std::uint8_t kind;
    std::uint8_t flags;
    std::uint16_t reserved;
};
static_assert(sizeof(SharedFunction) == 16);

struct SharedSite {
    std::uint32_t line;
    // The user file's index in the source table (0 without a position).
    std::uint32_t file;
    // The byte column, with the full source-position width.
    std::uint32_t column;
    // The callee's function id (a function call).
    std::uint32_t callee;
    // quidra::CallSiteCallee and call_site_flags.
    std::uint8_t callee_kind;
    std::uint8_t flags;
    std::uint16_t reserved;
};
static_assert(sizeof(SharedSite) == 20);

inline constexpr std::uint32_t identity_function_mask = 0x0fffffffu;
inline constexpr std::uint32_t identity_class_shift = 28;
inline constexpr std::uint32_t identity_class_mask = 0x3u;
inline constexpr std::uint32_t identity_branch_bit = 0x40000000u;
inline constexpr std::uint32_t identity_absolute_bit = 0x80000000u;
// The function id of an entry of class unknown.
inline constexpr std::uint32_t no_function = identity_function_mask;

// Symbol classes (toolchain::CallSiteSymbolClass).
inline constexpr std::uint32_t class_function = 0;
inline constexpr std::uint32_t class_fragment = 1;
inline constexpr std::uint32_t class_clone = 2;
inline constexpr std::uint32_t class_unknown = 3;

} // namespace quidra::abi::call_site_table
