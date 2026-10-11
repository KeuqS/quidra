#include "toolchain/call_site_table.hpp"

#include "quidra/abi/call_site_table.hpp"

#include <algorithm>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

namespace fs = std::filesystem;

namespace quidra::toolchain {

namespace {

namespace table = abi::call_site_table;

// The IR spelling of an object symbol's name: Mach-O prefixes C names with
// '_'.
std::string ir_name(const ObjectFile& object, const std::string& symbol) {
    if (object.format() == ObjectFormat::macho && !symbol.empty() && symbol[0] == '_')
        return symbol.substr(1);
    return symbol;
}

// An assembler-local name, which never names a function.
bool temporary(const ObjectFile& object, const std::string& symbol) {
    if (symbol.empty()) return true;
    if (object.format() == ObjectFormat::macho) return symbol[0] == 'l' || symbol[0] == 'L';
    return symbol.rfind(".L", 0) == 0 || symbol.rfind("$", 0) == 0;
}

bool digits(std::string_view text) {
    return !text.empty() &&
           std::all_of(text.begin(), text.end(), [](char c) { return c >= '0' && c <= '9'; });
}

struct Classified {
    CallSiteSymbolClass symbol_class{CallSiteSymbolClass::unknown};
    std::uint32_t function{table::no_function};
};

Classified classify(const std::string& name,
                    const std::unordered_map<std::string, std::uint32_t>& functions) {
    if (const auto found = functions.find(name); found != functions.end())
        return {CallSiteSymbolClass::function, found->second};
    if (const auto cold = name.rfind(".cold."); cold != std::string::npos &&
                                                digits(std::string_view(name).substr(cold + 6))) {
        if (const auto found = functions.find(name.substr(0, cold)); found != functions.end())
            return {CallSiteSymbolClass::fragment, found->second};
    }
    for (auto dot = name.rfind('.'); dot != std::string::npos && dot != 0; dot = name.rfind('.', dot - 1)) {
        if (const auto found = functions.find(name.substr(0, dot)); found != functions.end())
            return {CallSiteSymbolClass::clone, found->second};
    }
    return {};
}

// A branch to `target` in a function's code, found through the object's
// relocations or (AArch64) its branch instructions: the function's symbol
// and the branch's offset in it.
struct Branch {
    std::size_t symbol{};
    std::uint64_t offset{};
};

class BranchFinder {
public:
    explicit BranchFinder(const ObjectFile& object) : object_(object) {
        // The global functions of each code section, by address, to find
        // the function a branch is in.
        for (std::size_t i = 0; i < object.symbols().size(); ++i) {
            const auto& symbol = object.symbols()[i];
            if (!symbol.global || !symbol.section || symbol.section_symbol) continue;
            if (!object.sections()[*symbol.section].code) continue;
            globals_[*symbol.section].emplace(symbol.address, i);
        }
    }

    std::optional<Branch> find(std::size_t target_symbol, std::uint64_t target) const {
        const auto& sections = object_.sections();
        for (std::size_t s = 0; s < sections.size(); ++s) {
            const auto& section = sections[s];
            if (!section.code) continue;
            std::vector<std::uint8_t> bytes;
            for (const auto& relocation : section.relocations) {
                const auto instruction = branch_instruction(section, s, relocation, target_symbol,
                                                            target, bytes);
                if (!instruction) continue;
                if (const auto branch = containing(s, section.address + *instruction)) return branch;
            }
            // Branches the assembler resolved in place (ELF and COFF keep a
            // section whole, so the linker never moves them apart; a Mach-O
            // branch between functions always has a relocation). The walk
            // decodes the same bytes in the linked image, so only bytes no
            // relocation touches are taken.
            if (object_.format() == ObjectFormat::macho) continue;
            if (bytes.empty()) bytes = object_.section_bytes(section);
            if (object_.machine() == ObjectMachine::arm64) {
                for (std::uint64_t at = 0; at + 4 <= bytes.size(); at += 4) {
                    const std::uint32_t word = static_cast<std::uint32_t>(
                        bytes[at] | (bytes[at + 1] << 8) | (bytes[at + 2] << 16) |
                        (static_cast<std::uint32_t>(bytes[at + 3]) << 24));
                    if ((word & 0x7c000000u) != 0x14000000u) continue;  // B, BL
                    std::int64_t displacement = static_cast<std::int64_t>(word & 0x03ffffffu);
                    if (displacement & 0x02000000) displacement -= 0x04000000;
                    const auto address = section.address + at;
                    if (address + static_cast<std::uint64_t>(displacement * 4) != target) continue;
                    if (relocated(section, at, 4)) continue;
                    if (const auto branch = containing(s, address)) return branch;
                }
            } else {
                for (std::uint64_t at = 0; at + 5 <= bytes.size(); ++at) {
                    if (bytes[at] != 0xe8 && bytes[at] != 0xe9) continue;  // CALL, JMP rel32
                    const auto displacement = static_cast<std::int32_t>(
                        bytes[at + 1] | (bytes[at + 2] << 8) | (bytes[at + 3] << 16) |
                        (static_cast<std::uint32_t>(bytes[at + 4]) << 24));
                    const auto address = section.address + at;
                    if (address + 5 + static_cast<std::uint64_t>(static_cast<std::int64_t>(displacement)) !=
                        target)
                        continue;
                    if (relocated(section, at, 5)) continue;
                    if (const auto branch = containing(s, address)) return branch;
                }
            }
        }
        return std::nullopt;
    }

private:
    // Whether a relocation of `section` touches [offset, offset + size).
    bool relocated(const ObjectSection& section, std::uint64_t offset, std::uint64_t size) const {
        return std::any_of(section.relocations.begin(), section.relocations.end(),
                           [&](const ObjectRelocation& r) {
                               const std::uint64_t field = r.size != 0 ? r.size : 8;
                               return r.offset < offset + size && offset < r.offset + field;
                           });
    }

    // The offset of the branch instruction a relocation of `section`
    // resolves to `target`, if it is one.
    std::optional<std::uint64_t> branch_instruction(const ObjectSection& section, std::size_t,
                                                    const ObjectRelocation& relocation,
                                                    std::size_t target_symbol, std::uint64_t target,
                                                    std::vector<std::uint8_t>& bytes) const {
        if (!relocation.symbol || *relocation.symbol >= object_.symbols().size()) return std::nullopt;
        const auto& symbol = object_.symbols()[*relocation.symbol];
        const bool arm = object_.machine() == ObjectMachine::arm64;
        switch (object_.format()) {
            case ObjectFormat::macho:
                // ARM64_RELOC_BRANCH26, X86_64_RELOC_BRANCH: an external
                // relocation against the function's symbol.
                if (relocation.type != 2 || *relocation.symbol != target_symbol) return std::nullopt;
                break;
            case ObjectFormat::elf: {
                // R_AARCH64_JUMP26/CALL26 (S + A); R_X86_64_PC32/PLT32
                // (S + A + 4: the field's end).
                if (arm) {
                    if (relocation.type != 282 && relocation.type != 283) return std::nullopt;
                    if (symbol.address + static_cast<std::uint64_t>(relocation.addend) != target)
                        return std::nullopt;
                } else {
                    if (relocation.type != 2 && relocation.type != 4) return std::nullopt;
                    if (symbol.address + static_cast<std::uint64_t>(relocation.addend) + 4 != target)
                        return std::nullopt;
                }
                break;
            }
            case ObjectFormat::coff:
                // IMAGE_REL_ARM64_BRANCH26 against the symbol; AMD64 REL32
                // (the target is S + the in-place addend: the field holds
                // S + A - (P + 4)).
                if (arm) {
                    if (relocation.type != 0x3 || *relocation.symbol != target_symbol) return std::nullopt;
                } else {
                    if (relocation.type != 0x4) return std::nullopt;
                    if (bytes.empty()) bytes = object_.section_bytes(section);
                    if (relocation.offset + 4 > bytes.size()) return std::nullopt;
                    const auto addend = static_cast<std::int32_t>(
                        bytes[relocation.offset] | (bytes[relocation.offset + 1] << 8) |
                        (bytes[relocation.offset + 2] << 16) |
                        (static_cast<std::uint32_t>(bytes[relocation.offset + 3]) << 24));
                    if (symbol.address + static_cast<std::uint64_t>(static_cast<std::int64_t>(addend)) != target)
                        return std::nullopt;
                }
                break;
        }
        if (arm) return relocation.offset;
        // x86-64: CALL or JMP rel32, the field one byte after the opcode.
        if (bytes.empty()) bytes = object_.section_bytes(section);
        if (relocation.offset == 0 || relocation.offset > bytes.size()) return std::nullopt;
        const auto opcode = bytes[relocation.offset - 1];
        if (opcode != 0xe8 && opcode != 0xe9) return std::nullopt;
        return relocation.offset - 1;
    }

    std::optional<Branch> containing(std::size_t section, std::uint64_t address) const {
        const auto found = globals_.find(section);
        if (found == globals_.end()) return std::nullopt;
        auto it = found->second.upper_bound(address);
        if (it == found->second.begin()) return std::nullopt;
        --it;
        return Branch{it->second, address - it->first};
    }

    const ObjectFile& object_;
    std::map<std::size_t, std::map<std::uint64_t, std::size_t>> globals_;
};

// The rows of one function: the line rows and inline ranges that cover
// [begin, end), as chains of site ids.
class RowBuilder {
public:
    RowBuilder(const ObjectFile& object, const DwarfLines& lines, const CallSiteInfo& info,
               const std::unordered_map<std::string, std::uint32_t>& functions)
        : object_(object), lines_(lines), info_(info), functions_(functions) {
        if (info.debug) {
            for (std::uint32_t id = 1; id < info.sites.size(); ++id) {
                const auto& site = info.sites[id];
                debug_sites_[{site.owner, site.line}].push_back(id);
            }
        }
    }

    std::vector<CallSiteTableRow> rows(const DwarfSubprogram* subprogram, std::uint32_t function,
                                       std::uint64_t begin, std::uint64_t end) const {
        static const std::vector<DwarfInlined> none;
        const auto& inlined = subprogram ? subprogram->inlined : none;
        // Line segments [start, next) in the function.
        struct Segment {
            std::uint64_t start{};
            std::uint32_t site{};
        };
        std::vector<Segment> segments;
        for (std::size_t i = 0; i + 1 < lines_.rows.size(); ++i) {
            const auto& row = lines_.rows[i];
            if (row.end_sequence) continue;
            const auto next = lines_.rows[i + 1].address;
            if (next <= begin || row.address >= end || next <= row.address) continue;
            segments.push_back(Segment{std::max(row.address, begin), row_site(row)});
        }
        std::sort(segments.begin(), segments.end(),
                  [](const Segment& a, const Segment& b) { return a.start < b.start; });
        std::set<std::uint64_t> boundaries;
        for (const auto& segment : segments) boundaries.insert(segment.start);
        add_inline_boundaries(inlined, begin, end, boundaries);
        std::vector<CallSiteTableRow> out;
        for (const auto boundary : boundaries) {
            auto segment = std::upper_bound(segments.begin(), segments.end(), boundary,
                                            [](std::uint64_t value, const Segment& s) {
                                                return value < s.start;
                                            });
            std::uint32_t site = 0;
            if (segment != segments.begin()) site = std::prev(segment)->site;
            CallSiteTableRow row;
            row.offset = boundary - begin;
            row.chain.push_back(site);
            row.inline_callees.push_back(table::no_function);
            inline_chain(inlined, boundary, function, row.chain, row.inline_callees);
            if (!out.empty() && out.back().chain == row.chain &&
                out.back().inline_callees == row.inline_callees) continue;
            out.push_back(std::move(row));
        }
        return out;
    }

private:
    std::uint32_t row_site(const DwarfLineRow& row) const {
        const auto site = info_.debug ? row.discriminator : row.line;
        if (site >= info_.sites.size())
            object_.fail("the line table names call site " + std::to_string(site) +
                         ", which the module does not have");
        return site;
    }

    void add_inline_boundaries(const std::vector<DwarfInlined>& nodes, std::uint64_t begin,
                               std::uint64_t end, std::set<std::uint64_t>& boundaries) const {
        for (const auto& node : nodes) {
            for (const auto& [low, high] : node.ranges) {
                if (low > begin && low < end) boundaries.insert(low);
                if (high > begin && high < end) boundaries.insert(high);
            }
            add_inline_boundaries(node.children, begin, end, boundaries);
        }
    }

    // Appends, innermost first, the call site of every inlined function
    // whose ranges contain `address`.
    void inline_chain(const std::vector<DwarfInlined>& nodes, std::uint64_t address,
                      std::uint32_t caller, std::vector<std::uint32_t>& chain,
                      std::vector<std::uint32_t>& callees) const {
        for (const auto& node : nodes) {
            const bool inside = std::any_of(node.ranges.begin(), node.ranges.end(), [&](const auto& r) {
                return address >= r.first && address < r.second;
            });
            if (!inside) continue;
            const auto callee = function_of(node.name);
            std::vector<std::uint32_t> inner, inner_callees;
            inline_chain(node.children, address, callee, inner, inner_callees);
            chain.insert(chain.end(), inner.begin(), inner.end());
            callees.insert(callees.end(), inner_callees.begin(), inner_callees.end());
            const auto site = call_site(node.call_line, caller, callee);
            if (site && callee != table::no_function &&
                info_.sites[site].callee_kind == CallSiteCallee::function &&
                info_.sites[site].callee != callee)
                object_.fail("an inline identity disagrees with its call site");
            chain.push_back(site);
            callees.push_back(callee);
            return;
        }
    }

    std::uint32_t function_of(const std::string& name) const {
        const auto found = functions_.find(name);
        return found == functions_.end() ? table::no_function : found->second;
    }

    // The site of an inlined call: its call line (release), or the one call
    // of `callee` on that line of `caller` (--debug).
    std::uint32_t call_site(std::uint32_t line, std::uint32_t caller, std::uint32_t callee) const {
        if (!info_.debug) {
            if (line >= info_.sites.size())
                object_.fail("an inlined call names call site " + std::to_string(line) +
                             ", which the module does not have");
            return line;
        }
        const auto found = debug_sites_.find({caller, line});
        if (found == debug_sites_.end()) return 0;
        std::uint32_t match = 0;
        for (const auto id : found->second) {
            const auto& site = info_.sites[id];
            if (site.callee_kind != CallSiteCallee::function || site.callee != callee) continue;
            if (match != 0) return 0;
            match = id;
        }
        return match;
    }

    const ObjectFile& object_;
    const DwarfLines& lines_;
    const CallSiteInfo& info_;
    const std::unordered_map<std::string, std::uint32_t>& functions_;
    std::map<std::pair<std::uint32_t, std::uint32_t>, std::vector<std::uint32_t>> debug_sites_;
};

void append_uleb(std::vector<std::uint8_t>& out, std::uint64_t value) {
    do {
        auto byte = static_cast<std::uint8_t>(value & 0x7f);
        value >>= 7;
        if (value != 0) byte |= 0x80;
        out.push_back(byte);
    } while (value != 0);
}
void append_u32(std::vector<std::uint8_t>& out, std::uint32_t value) {
    for (int i = 0; i < 4; ++i) out.push_back(static_cast<std::uint8_t>(value >> (8 * i)));
}
void append_u16(std::vector<std::uint8_t>& out, std::uint16_t value) {
    out.push_back(static_cast<std::uint8_t>(value));
    out.push_back(static_cast<std::uint8_t>(value >> 8));
}

// An LLVM byte-array constant: c"..." with every byte outside printable
// ASCII (and '"', '\\') escaped.
std::string byte_string(const std::vector<std::uint8_t>& bytes) {
    static constexpr char hex[] = "0123456789ABCDEF";
    std::string out = "c\"";
    for (const auto byte : bytes) {
        if (byte >= 0x20 && byte < 0x7f && byte != '"' && byte != '\\') {
            out.push_back(static_cast<char>(byte));
        } else {
            out.push_back('\\');
            out.push_back(hex[byte >> 4]);
            out.push_back(hex[byte & 0xf]);
        }
    }
    out.push_back('"');
    return out;
}

// An LLVM global name, quoted when it is not a plain identifier.
std::string global_name(const std::string& name) {
    const bool plain = !name.empty() && std::all_of(name.begin(), name.end(), [](char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') ||
               c == '_' || c == '.' || c == '$';
    }) && !(name[0] >= '0' && name[0] <= '9');
    if (plain) return "@" + name;
    std::string out = "@\"";
    for (const char c : name) {
        if (c == '"' || c == '\\' || static_cast<unsigned char>(c) < 0x20) {
            static constexpr char hex[] = "0123456789ABCDEF";
            out.push_back('\\');
            out.push_back(hex[static_cast<unsigned char>(c) >> 4]);
            out.push_back(hex[static_cast<unsigned char>(c) & 0xf]);
        } else {
            out.push_back(c);
        }
    }
    out.push_back('"');
    return out;
}

struct Sections {
    std::string entries;
    std::string shared;
};

Sections sections_of(ObjectFormat format) {
    switch (format) {
        case ObjectFormat::macho:
            return {"__DATA,__quidra_calls,regular,live_support", "__DATA,__quidra_sites"};
        case ObjectFormat::elf: return {"quidra_calls", "quidra_sites"};
        case ObjectFormat::coff: return {".qcalls$m", ".qsites$m"};
    }
    return {};
}

} // namespace

std::vector<CallSiteTableEntry> call_site_table_entries(const ObjectFile& object,
                                                        const DwarfLines& lines,
                                                        const CallSiteInfo& info) {
    std::unordered_map<std::string, std::uint32_t> functions;
    for (std::uint32_t id = 0; id < info.functions.size(); ++id)
        for (const auto& symbol : info.functions[id].symbols) functions.emplace(symbol, id);
    const RowBuilder builder(object, lines, info, functions);
    const BranchFinder branches(object);
    // The functions of the object: its code symbols, one per address (the
    // one DWARF names, else a global one). DWARF describes only some of
    // them (outside Darwin, line-tables-only DWARF has a subprogram only
    // for a function with inlined calls), so the symbols decide what is a
    // function; a subprogram gives its exact end and its inline tree.
    std::map<std::uint64_t, const DwarfSubprogram*> subprograms;
    for (const auto& subprogram : lines.subprograms)
        if (!subprogram.ranges.empty()) subprograms.emplace(subprogram.ranges.front().first, &subprogram);
    std::map<std::pair<std::size_t, std::uint64_t>, std::size_t> chosen;
    for (std::size_t i = 0; i < object.symbols().size(); ++i) {
        const auto& candidate = object.symbols()[i];
        if (!candidate.section || candidate.section_symbol) continue;
        if (!object.sections()[*candidate.section].code || temporary(object, candidate.name)) continue;
        const auto key = std::make_pair(*candidate.section, candidate.address);
        const auto existing = chosen.find(key);
        if (existing == chosen.end()) {
            chosen.emplace(key, i);
            continue;
        }
        const auto& current = object.symbols()[existing->second];
        const auto described = subprograms.find(candidate.address);
        const auto named = [&](const ObjectSymbol& symbol) {
            return described != subprograms.end() && ir_name(object, symbol.name) == described->second->name;
        };
        if ((named(candidate) && !named(current)) || (!named(current) && candidate.global && !current.global))
            existing->second = i;
    }
    std::set<std::uint64_t> row_starts;
    for (const auto& row : lines.rows)
        if (!row.end_sequence) row_starts.insert(row.address);
    std::vector<CallSiteTableEntry> out;
    for (auto it = chosen.begin(); it != chosen.end(); ++it) {
        const auto [section, begin] = it->first;
        const auto& found = object.symbols()[it->second];
        const auto described = subprograms.find(begin);
        const DwarfSubprogram* subprogram = described != subprograms.end() ? described->second : nullptr;
        // The end: the subprogram's, the symbol's size, or the next
        // function or the section's end.
        std::uint64_t end = 0;
        if (subprogram) end = subprogram->ranges.front().second;
        else if (found.size != 0) end = begin + found.size;
        else {
            const auto next = std::next(it);
            const auto& code = object.sections()[section];
            end = next != chosen.end() && next->first.first == section ? next->first.second
                                                                       : code.address + code.size;
        }
        if (end <= begin) continue;
        CallSiteTableEntry entry;
        entry.name = subprogram && !subprogram->name.empty() ? subprogram->name : ir_name(object, found.name);
        const auto classified = classify(entry.name, functions);
        entry.symbol_class = classified.symbol_class;
        entry.function = classified.function;
        entry.code_size = end - begin;
        // A function compiled without debug information (the prelude's
        // helpers) has no row of its own: the row before it continues
        // over its code. Every function with a subprogram has a row at its
        // start.
        if (!subprogram && !row_starts.contains(begin)) continue;
        entry.rows = builder.rows(subprogram, entry.function, begin, end);
        if (found.global) {
            entry.reference = ir_name(object, found.name);
        } else {
            const auto branch = branches.find(it->second, begin);
            if (!branch) continue;
            entry.reference = ir_name(object, object.symbols()[branch->symbol].name);
            entry.branch_offset = branch->offset;
        }
        out.push_back(std::move(entry));
    }
    return out;
}

std::string call_site_table_module(const std::vector<CallSiteTableEntry>& entries,
                                   const CallSiteInfo& info, ObjectFormat format,
                                   ObjectMachine machine) {
    const auto sections = sections_of(format);
    // x86-64 Mach-O cannot relocate a difference with a symbol of another
    // object: those entries hold the function's address.
    const bool absolute = format == ObjectFormat::macho && machine == ObjectMachine::x86_64;
    std::ostringstream out;
    out << "; The call-site table of a Quidra module.\n";
    if (info.library) out << "@__quidra_calls_anchor = constant i8 0\n";
    // A record reached from a cold fragment uses that fragment's CFA,
    // which is not its logical owner's frame. Mark only those owners.
    std::vector<bool> unusable_tail(info.functions.size(), false);
    for (const auto& entry : entries) {
        if (entry.symbol_class != CallSiteSymbolClass::fragment) continue;
        for (const auto& row : entry.rows)
            for (const auto id : row.chain) {
                if (!id || id >= info.sites.size()) continue;
                const auto& site = info.sites[id];
                if ((site.flags & call_site_flags::tail_record_helper) && site.owner < unusable_tail.size())
                    unusable_tail[site.owner] = true;
            }
    }
    // The shared table.
    std::vector<std::uint8_t> shared;
    std::vector<std::uint8_t> strings;
    std::vector<std::uint32_t> name_offsets;
    for (const auto& function : info.functions) {
        name_offsets.push_back(static_cast<std::uint32_t>(strings.size()));
        strings.insert(strings.end(), function.display.begin(), function.display.end());
        strings.push_back(0);
    }
    while (strings.size() % 4 != 0) strings.push_back(0);
    std::vector<std::uint32_t> first_site(info.functions.size(), 0);
    std::vector<std::uint32_t> site_count(info.functions.size(), 0);
    for (std::uint32_t id = 1; id < info.sites.size(); ++id) {
        const auto owner = info.sites[id].owner;
        if (owner >= info.functions.size()) continue;
        if (site_count[owner] == 0) first_site[owner] = id;
        ++site_count[owner];
    }
    append_u32(shared, table::magic);
    append_u32(shared, table::version);
    append_u32(shared, static_cast<std::uint32_t>(info.functions.size()));
    append_u32(shared, static_cast<std::uint32_t>(info.sites.size()));
    append_u32(shared, static_cast<std::uint32_t>(strings.size()));
    append_u32(shared, info.debug ? table::shared_flags::debug : 0);
    for (std::size_t i = 0; i < info.functions.size(); ++i) {
        append_u32(shared, name_offsets[i]);
        append_u32(shared, first_site[i]);
        append_u32(shared, site_count[i]);
        shared.push_back(static_cast<std::uint8_t>(info.functions[i].kind));
        shared.push_back(info.functions[i].flags |
                         (unusable_tail[i] ? call_site_function_flags::tail_unusable : 0));
        append_u16(shared, 0);
    }
    for (const auto& site : info.sites) {
        append_u32(shared, site.line);
        append_u32(shared, site.file);
        append_u32(shared, site.column);
        append_u32(shared, site.callee_kind == CallSiteCallee::function ? site.callee : table::no_function);
        shared.push_back(static_cast<std::uint8_t>(site.callee_kind));
        shared.push_back(site.flags);
        append_u16(shared, 0);
    }
    shared.insert(shared.end(), strings.begin(), strings.end());
    out << "@.quidra.sites = private constant [" << shared.size() << " x i8] " << byte_string(shared)
        << ", section \"" << sections.shared << "\", align 4\n";

    // The entries.
    std::set<std::string> declared;
    std::vector<std::string> names;
    for (std::size_t index = 0; index < entries.size(); ++index) {
        const auto& entry = entries[index];
        if (declared.insert(entry.reference).second)
            out << "declare void " << global_name(entry.reference) << "()\n";
        std::vector<std::uint8_t> chains;
        std::map<std::vector<std::uint32_t>, std::uint32_t> chain_offsets;
        std::vector<std::uint8_t> rows;
        std::uint64_t previous = 0;
        for (const auto& row : entry.rows) {
            if (row.inline_callees.size() != row.chain.size())
                throw std::runtime_error("call-site chain has mismatched inline identities");
            std::vector<std::uint32_t> key;
            for (std::size_t i = 0; i < row.chain.size(); ++i) {
                key.push_back(row.chain[i]);
                key.push_back(row.inline_callees[i]);
            }
            auto [it, inserted] = chain_offsets.emplace(key, static_cast<std::uint32_t>(chains.size()));
            if (inserted) {
                append_uleb(chains, row.chain.size());
                for (std::size_t i = 0; i < row.chain.size(); ++i) {
                    append_uleb(chains, row.chain[i]);
                    append_uleb(chains, row.inline_callees[i] == table::no_function
                        ? 0 : std::uint64_t{row.inline_callees[i]} + 1);
                }
            }
            append_uleb(rows, row.offset - previous);
            append_uleb(rows, it->second);
            previous = row.offset;
        }
        std::vector<std::uint8_t> tail;
        if (entry.branch_offset) append_u32(tail, static_cast<std::uint32_t>(*entry.branch_offset));
        append_u32(tail, static_cast<std::uint32_t>(rows.size()));
        append_u32(tail, static_cast<std::uint32_t>(chains.size()));
        tail.insert(tail.end(), rows.begin(), rows.end());
        tail.insert(tail.end(), chains.begin(), chains.end());
        const std::size_t header = absolute ? 24 : 16;
        const std::size_t alignment = absolute ? 8 : 4;
        while ((header + tail.size()) % alignment != 0) tail.push_back(0);
        const auto size = header + tail.size();
        std::uint32_t identity = (entry.function & table::identity_function_mask) |
                                 (static_cast<std::uint32_t>(entry.symbol_class) << table::identity_class_shift);
        if (entry.branch_offset) identity |= table::identity_branch_bit;
        if (absolute) identity |= table::identity_absolute_bit;
        const auto name = "@.quidra.calls." + std::to_string(index);
        names.push_back(name);
        if (absolute) {
            out << name << " = private constant <{ i32, i32, i32, i32, ptr, [" << tail.size()
                << " x i8] }> <{ i32 " << size << ", i32 0, i32 " << entry.code_size << ", i32 " << identity
                << ", ptr " << global_name(entry.reference) << ", [" << tail.size() << " x i8] "
                << byte_string(tail) << " }>, section \"" << sections.entries << "\", align 8\n";
        } else {
            out << name << " = private constant <{ i32, i32, i32, i32, [" << tail.size()
                << " x i8] }> <{ i32 " << size << ", i32 trunc (i64 sub (i64 ptrtoint (ptr "
                << global_name(entry.reference) << " to i64), i64 ptrtoint (ptr getelementptr (i8, ptr "
                << name << ", i64 4) to i64)) to i32), i32 " << entry.code_size << ", i32 " << identity
                << ", [" << tail.size() << " x i8] " << byte_string(tail) << " }>, section \""
                << sections.entries << "\", align 4\n";
        }
    }
    // Mach-O: an entry must not keep its function alive, so the compiler
    // keeps it but the linker may drop it (live_support keeps it with its
    // function). ELF and COFF: the linker keeps every entry; their functions
    // share one kept text section. The shared table is always kept.
    const bool macho = format == ObjectFormat::macho;
    std::vector<std::string> used{"@.quidra.sites"};
    std::vector<std::string> compiler_used;
    for (const auto& name : names) (macho ? compiler_used : used).push_back(name);
    const auto list = [&](const char* list_name, const std::vector<std::string>& globals) {
        if (globals.empty()) return;
        out << list_name << " = appending global [" << globals.size() << " x ptr] [";
        for (std::size_t i = 0; i < globals.size(); ++i) out << (i ? ", ptr " : "ptr ") << globals[i];
        out << "], section \"llvm.metadata\"\n";
    };
    list("@llvm.used", used);
    list("@llvm.compiler.used", compiler_used);
    return out.str();
}

void write_call_site_table(const fs::path& object_path, const CallSiteInfo& info,
                           const fs::path& output) {
    const auto object = ObjectFile::read(object_path);
    const auto lines = read_dwarf_lines(object);
    const auto entries = call_site_table_entries(object, lines, info);
    const auto text = call_site_table_module(entries, info, object.format(), object.machine());
    std::ofstream out(output, std::ios::binary | std::ios::trunc);
    out << text;
    out.close();
    if (!out) throw std::runtime_error("cannot write the call-site table: " + output.string());
}

} // namespace quidra::toolchain
