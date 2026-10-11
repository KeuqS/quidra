#include "toolchain/dwarf_lines.hpp"

#include <map>
#include <optional>
#include <stdexcept>
#include <unordered_map>

namespace quidra::toolchain {

namespace {

// DWARF constants of the subset.
constexpr std::uint64_t tag_compile_unit = 0x11;
constexpr std::uint64_t tag_subprogram = 0x2e;
constexpr std::uint64_t tag_inlined_subroutine = 0x1d;

constexpr std::uint64_t at_name = 0x03;
constexpr std::uint64_t at_linkage_name = 0x6e;
constexpr std::uint64_t at_mips_linkage_name = 0x2007;
constexpr std::uint64_t at_low_pc = 0x11;
constexpr std::uint64_t at_high_pc = 0x12;
constexpr std::uint64_t at_abstract_origin = 0x31;
constexpr std::uint64_t at_specification = 0x47;
constexpr std::uint64_t at_ranges = 0x55;
constexpr std::uint64_t at_call_line = 0x59;
constexpr std::uint64_t at_stmt_list = 0x10;

enum Form : std::uint64_t {
    form_addr = 0x01,
    form_block2 = 0x03,
    form_block4 = 0x04,
    form_data2 = 0x05,
    form_data4 = 0x06,
    form_data8 = 0x07,
    form_string = 0x08,
    form_block = 0x09,
    form_block1 = 0x0a,
    form_data1 = 0x0b,
    form_flag = 0x0c,
    form_sdata = 0x0d,
    form_strp = 0x0e,
    form_udata = 0x0f,
    form_ref_addr = 0x10,
    form_ref1 = 0x11,
    form_ref2 = 0x12,
    form_ref4 = 0x13,
    form_ref8 = 0x14,
    form_ref_udata = 0x15,
    form_indirect = 0x16,
    form_sec_offset = 0x17,
    form_exprloc = 0x18,
    form_flag_present = 0x19,
    form_ref_sig8 = 0x20,
};

// A cursor over one section's bytes.
class Reader {
public:
    Reader(const std::vector<std::uint8_t>& bytes, const ObjectFile& object, const char* section)
        : bytes_(bytes), object_(object), section_(section) {}

    std::uint64_t offset() const { return offset_; }
    void seek(std::uint64_t offset) {
        if (offset > bytes_.size()) fail("offset out of range");
        offset_ = offset;
    }
    bool at_end(std::uint64_t end) const { return offset_ >= end; }
    std::uint64_t size() const { return bytes_.size(); }

    std::uint64_t fixed(unsigned size) {
        need(size);
        std::uint64_t value = 0;
        for (unsigned i = size; i-- > 0;) value = (value << 8) | bytes_[offset_ + i];
        offset_ += size;
        return value;
    }
    std::uint8_t u8() { return static_cast<std::uint8_t>(fixed(1)); }
    std::uint16_t u16() { return static_cast<std::uint16_t>(fixed(2)); }
    std::uint32_t u32() { return static_cast<std::uint32_t>(fixed(4)); }
    std::uint64_t u64() { return fixed(8); }
    std::uint64_t uleb() {
        std::uint64_t value = 0;
        unsigned shift = 0;
        for (;;) {
            const auto byte = u8();
            if (shift < 64) value |= std::uint64_t{byte & 0x7fu} << shift;
            shift += 7;
            if (!(byte & 0x80)) return value;
        }
    }
    std::int64_t sleb() {
        std::int64_t value = 0;
        unsigned shift = 0;
        std::uint8_t byte = 0;
        do {
            byte = u8();
            if (shift < 64) value |= static_cast<std::int64_t>(std::uint64_t{byte & 0x7fu} << shift);
            shift += 7;
        } while (byte & 0x80);
        if (shift < 64 && (byte & 0x40)) value |= -(std::int64_t{1} << shift);
        return value;
    }
    std::string cstring() {
        std::string out;
        for (;;) {
            const auto c = u8();
            if (c == 0) return out;
            out.push_back(static_cast<char>(c));
        }
    }
    void skip(std::uint64_t size) {
        need(size);
        offset_ += size;
    }

    [[noreturn]] void fail(const std::string& message) const {
        object_.fail(std::string(section_) + ": " + message);
    }

private:
    void need(std::uint64_t size) const {
        if (offset_ > bytes_.size() || size > bytes_.size() - offset_) fail("truncated");
    }

    const std::vector<std::uint8_t>& bytes_;
    const ObjectFile& object_;
    const char* section_;
    std::uint64_t offset_{};
};

struct Abbreviation {
    std::uint64_t tag{};
    bool children{};
    std::vector<std::pair<std::uint64_t, std::uint64_t>> attributes;
};

std::unordered_map<std::uint64_t, Abbreviation> read_abbreviations(Reader& in) {
    std::unordered_map<std::uint64_t, Abbreviation> out;
    for (;;) {
        const auto code = in.uleb();
        if (code == 0) return out;
        Abbreviation abbreviation;
        abbreviation.tag = in.uleb();
        abbreviation.children = in.u8() != 0;
        for (;;) {
            const auto attribute = in.uleb();
            const auto form = in.uleb();
            if (attribute == 0 && form == 0) break;
            abbreviation.attributes.emplace_back(attribute, form);
        }
        out.emplace(code, std::move(abbreviation));
    }
}

// What a DIE of the subset holds.
struct Die {
    std::uint64_t tag{};
    std::optional<std::string> name;
    std::optional<std::string> linkage_name;
    std::optional<std::uint64_t> low_pc;
    std::optional<std::uint64_t> high_pc;
    bool high_pc_is_offset{};
    std::optional<std::uint64_t> ranges;
    std::uint32_t call_line{};
    std::optional<std::uint64_t> origin;
    std::optional<std::uint64_t> specification;
    std::optional<std::uint64_t> stmt_list;
};

struct Unit {
    std::uint64_t base_address{};
};

// One parsed DIE tree node of the subset (subprograms and inlined
// subroutines, with lexical blocks flattened away).
struct Node {
    std::uint64_t offset{};
    Die die;
    std::vector<Node> children;
};

class InfoReader {
public:
    InfoReader(const ObjectFile& object, const std::vector<std::uint8_t>& info,
               const std::vector<std::uint8_t>& abbrev, const std::vector<std::uint8_t>* str,
               const std::vector<std::uint8_t>* ranges)
        : object_(object), info_(info, object, ".debug_info"), abbrev_(abbrev, object, ".debug_abbrev"),
          str_(str), ranges_(ranges) {}

    void read(DwarfLines& out, std::vector<std::uint64_t>& line_offsets) {
        while (!info_.at_end(info_.size())) {
            const auto unit_start = info_.offset();
            const auto length = info_.u32();
            if (length == 0xffffffffu) info_.fail("64-bit DWARF is not supported");
            const auto unit_end = info_.offset() + length;
            const auto version = info_.u16();
            if (version < 2 || version > 4)
                info_.fail("unexpected DWARF version " + std::to_string(version));
            const auto abbrev_offset = info_.u32();
            const auto address_size = info_.u8();
            if (address_size != 8) info_.fail("unexpected address size " + std::to_string(address_size));
            version_ = version;
            unit_start_ = unit_start;
            abbrev_.seek(abbrev_offset);
            abbreviations_ = read_abbreviations(abbrev_);
            // The DIEs of the unit as a tree of the kept ones, read with a
            // stack of the open DIEs that have children.
            std::vector<Node> roots;
            std::vector<Open> open;
            while (info_.offset() < unit_end) {
                const auto offset = info_.offset();
                const auto code = info_.uleb();
                if (code == 0) {
                    if (open.empty()) continue;
                    close(open, roots);
                    continue;
                }
                const auto found = abbreviations_.find(code);
                if (found == abbreviations_.end())
                    info_.fail("unknown abbreviation code " + std::to_string(code));
                const auto& abbreviation = found->second;
                Die die;
                die.tag = abbreviation.tag;
                for (const auto& [attribute, form] : abbreviation.attributes)
                    read_attribute(die, attribute, form);
                if (die.name) names_[offset] = *die.name;
                if (die.linkage_name) linkage_names_[offset] = *die.linkage_name;
                if (die.origin) origins_[offset] = *die.origin;
                if (die.specification) origins_[offset] = *die.specification;
                if (die.tag == tag_compile_unit) {
                    unit_.base_address = die.low_pc.value_or(0);
                    if (die.stmt_list) line_offsets.push_back(*die.stmt_list);
                }
                const bool keep = die.tag == tag_subprogram || die.tag == tag_inlined_subroutine;
                Node node{offset, std::move(die), {}};
                if (node.die.tag != tag_compile_unit && keep) node_ranges_[offset] = ranges_of(node.die);
                if (abbreviation.children) {
                    open.push_back(Open{std::move(node), keep});
                } else if (keep) {
                    attach(open, roots, std::move(node));
                }
            }
            while (!open.empty()) close(open, roots);
            for (auto& root : roots) collect(root, out);
            info_.seek(unit_end);
        }
    }

private:
    struct Open {
        Node node;
        bool keep{};
    };

    void attach(std::vector<Open>& open, std::vector<Node>& roots, Node node) {
        // Into the innermost kept ancestor; a lexical block or another
        // DIE in between is transparent.
        for (auto it = open.rbegin(); it != open.rend(); ++it) {
            if (it->keep) {
                it->node.children.push_back(std::move(node));
                return;
            }
        }
        roots.push_back(std::move(node));
    }
    void close(std::vector<Open>& open, std::vector<Node>& roots) {
        auto last = std::move(open.back());
        open.pop_back();
        if (last.keep) {
            attach(open, roots, std::move(last.node));
        } else {
            // A transparent DIE: its kept children move up.
            for (auto& child : last.node.children) attach(open, roots, std::move(child));
        }
    }

    void read_attribute(Die& die, std::uint64_t attribute, std::uint64_t form) {
        if (form == form_indirect) form = info_.uleb();
        std::uint64_t value = 0;
        std::optional<std::string> text;
        bool reference = false;
        switch (form) {
            case form_addr: value = info_.u64(); break;
            case form_data1: case form_ref1: case form_flag: value = info_.u8(); break;
            case form_data2: case form_ref2: value = info_.u16(); break;
            case form_data4: case form_ref4: value = info_.u32(); break;
            case form_data8: case form_ref8: case form_ref_sig8: value = info_.u64(); break;
            case form_sdata: value = static_cast<std::uint64_t>(info_.sleb()); break;
            case form_udata: case form_ref_udata: value = info_.uleb(); break;
            case form_strp: case form_sec_offset: value = info_.u32(); break;
            case form_ref_addr: value = version_ <= 2 ? info_.u64() : info_.u32(); break;
            case form_string: text = info_.cstring(); break;
            case form_block1: info_.skip(info_.u8()); break;
            case form_block2: info_.skip(info_.u16()); break;
            case form_block4: info_.skip(info_.u32()); break;
            case form_block: case form_exprloc: info_.skip(info_.uleb()); break;
            case form_flag_present: value = 1; break;
            default: info_.fail("unexpected attribute form " + std::to_string(form));
        }
        reference = form == form_ref1 || form == form_ref2 || form == form_ref4 ||
                    form == form_ref8 || form == form_ref_udata;
        switch (attribute) {
            case at_name:
                if (form == form_strp) die.name = string_at(value);
                else if (text) die.name = *text;
                break;
            case at_linkage_name: case at_mips_linkage_name:
                if (form == form_strp) die.linkage_name = string_at(value);
                else if (text) die.linkage_name = *text;
                break;
            case at_low_pc:
                if (form == form_addr) die.low_pc = value;
                break;
            case at_high_pc:
                die.high_pc = value;
                die.high_pc_is_offset = form != form_addr;
                break;
            case at_ranges: die.ranges = value; break;
            case at_call_line: die.call_line = static_cast<std::uint32_t>(value); break;
            case at_stmt_list: die.stmt_list = value; break;
            case at_abstract_origin:
                if (reference) die.origin = unit_start_ + value;
                else if (form == form_ref_addr) die.origin = value;
                break;
            case at_specification:
                if (reference) die.specification = unit_start_ + value;
                else if (form == form_ref_addr) die.specification = value;
                break;
            default: break;
        }
    }

    std::string string_at(std::uint64_t offset) const {
        if (!str_) object_.fail(".debug_str: missing");
        if (offset >= str_->size()) object_.fail(".debug_str: offset out of range");
        std::string out;
        for (auto i = offset; i < str_->size() && (*str_)[i] != 0; ++i)
            out.push_back(static_cast<char>((*str_)[i]));
        return out;
    }

    DwarfRanges ranges_of(const Die& die) {
        DwarfRanges out;
        if (die.low_pc && die.high_pc) {
            const auto high = die.high_pc_is_offset ? *die.low_pc + *die.high_pc : *die.high_pc;
            if (high > *die.low_pc) out.emplace_back(*die.low_pc, high);
            return out;
        }
        if (!die.ranges) return out;
        if (!ranges_) object_.fail(".debug_ranges: missing");
        Reader in(*ranges_, object_, ".debug_ranges");
        in.seek(*die.ranges);
        auto base = unit_.base_address;
        for (;;) {
            const auto begin = in.u64();
            const auto end = in.u64();
            if (begin == 0 && end == 0) break;
            if (begin == ~std::uint64_t{0}) {
                base = end;
                continue;
            }
            if (end > begin) out.emplace_back(base + begin, base + end);
        }
        return out;
    }

    std::string resolved_name(std::uint64_t offset) const {
        // Full debug information separates the source spelling from the
        // linkage identity used by CallSiteInfo. Prefer that identity even
        // when it lives on an inlined abstract origin or specification.
        std::string fallback;
        for (int depth = 0; depth < 16; ++depth) {
            if (const auto name = linkage_names_.find(offset); name != linkage_names_.end())
                return name->second;
            if (fallback.empty())
                if (const auto name = names_.find(offset); name != names_.end()) fallback = name->second;
            const auto origin = origins_.find(offset);
            if (origin == origins_.end()) break;
            offset = origin->second;
        }
        return fallback;
    }

    DwarfInlined inlined_of(const Node& node) const {
        DwarfInlined out;
        out.ranges = node_ranges_.at(node.offset);
        out.call_line = node.die.call_line;
        out.name = resolved_name(node.offset);
        for (const auto& child : node.children)
            if (child.die.tag == tag_inlined_subroutine) out.children.push_back(inlined_of(child));
        return out;
    }

    void collect(const Node& node, DwarfLines& out) const {
        if (node.die.tag == tag_subprogram) {
            const auto& ranges = node_ranges_.at(node.offset);
            if (!ranges.empty()) {
                DwarfSubprogram subprogram;
                subprogram.name = resolved_name(node.offset);
                subprogram.ranges = ranges;
                for (const auto& child : node.children)
                    if (child.die.tag == tag_inlined_subroutine)
                        subprogram.inlined.push_back(inlined_of(child));
                out.subprograms.push_back(std::move(subprogram));
            }
        }
        // A nested subprogram (none in Quidra's output) is collected on its
        // own.
        for (const auto& child : node.children)
            if (child.die.tag == tag_subprogram) collect(child, out);
    }

    const ObjectFile& object_;
    Reader info_;
    Reader abbrev_;
    const std::vector<std::uint8_t>* str_;
    const std::vector<std::uint8_t>* ranges_;
    std::unordered_map<std::uint64_t, Abbreviation> abbreviations_;
    std::unordered_map<std::uint64_t, std::string> names_;
    std::unordered_map<std::uint64_t, std::string> linkage_names_;
    std::unordered_map<std::uint64_t, std::uint64_t> origins_;
    std::unordered_map<std::uint64_t, DwarfRanges> node_ranges_;
    Unit unit_;
    unsigned version_{};
    std::uint64_t unit_start_{};
};

void read_line_program(Reader& in, std::uint64_t offset, DwarfLines& out) {
    in.seek(offset);
    const auto length = in.u32();
    if (length == 0xffffffffu) in.fail("64-bit DWARF is not supported");
    const auto end = in.offset() + length;
    const auto version = in.u16();
    if (version < 2 || version > 4) in.fail("unexpected line table version " + std::to_string(version));
    const auto header_length = in.u32();
    const auto program = in.offset() + header_length;
    const auto minimum_instruction_length = in.u8();
    if (version >= 4) {
        const auto operations = in.u8();
        if (operations != 1) in.fail("VLIW line tables are not supported");
    }
    const bool default_is_stmt = in.u8() != 0;
    (void)default_is_stmt;
    const auto line_base = static_cast<std::int8_t>(in.u8());
    const auto line_range = in.u8();
    const auto opcode_base = in.u8();
    if (line_range == 0) in.fail("line_range is 0");
    std::vector<std::uint8_t> lengths(opcode_base > 0 ? opcode_base - 1 : 0);
    for (auto& length_of : lengths) length_of = in.u8();
    in.seek(program);

    DwarfLineRow state;
    const auto reset = [&] {
        state = DwarfLineRow{};
        state.line = 1;
    };
    reset();
    while (in.offset() < end) {
        const auto opcode = in.u8();
        if (opcode >= opcode_base) {
            const auto adjusted = static_cast<unsigned>(opcode - opcode_base);
            state.address += static_cast<std::uint64_t>(adjusted / line_range) * minimum_instruction_length;
            state.line = static_cast<std::uint32_t>(static_cast<std::int64_t>(state.line) + line_base +
                                                    static_cast<std::int64_t>(adjusted % line_range));
            out.rows.push_back(state);
            state.discriminator = 0;
            continue;
        }
        switch (opcode) {
            case 0: {
                const auto size = in.uleb();
                const auto start = in.offset();
                if (size == 0) break;
                const auto sub = in.u8();
                if (sub == 1) {
                    state.end_sequence = true;
                    out.rows.push_back(state);
                    reset();
                } else if (sub == 2) {
                    if (size != 9) in.fail("unexpected set_address size");
                    state.address = in.u64();
                } else if (sub == 4) {
                    state.discriminator = static_cast<std::uint32_t>(in.uleb());
                }
                in.seek(start + size);
                break;
            }
            case 1:  // copy
                out.rows.push_back(state);
                state.discriminator = 0;
                break;
            case 2: state.address += in.uleb() * minimum_instruction_length; break;
            case 3:
                state.line = static_cast<std::uint32_t>(static_cast<std::int64_t>(state.line) + in.sleb());
                break;
            case 4: (void)in.uleb(); break;  // file
            case 5: state.column = static_cast<std::uint32_t>(in.uleb()); break;
            case 6: case 7: case 10: case 11: break;  // negate_stmt, basic_block, prologue/epilogue
            case 8:
                state.address +=
                    static_cast<std::uint64_t>((255 - opcode_base) / line_range) * minimum_instruction_length;
                break;
            case 9: state.address += in.u16(); break;
            case 12: (void)in.uleb(); break;  // isa
            default:
                // An opcode this reader does not know: skip its operands.
                for (unsigned i = 0; i < lengths[opcode - 1]; ++i) (void)in.uleb();
                break;
        }
    }
}

} // namespace

DwarfLines read_dwarf_lines(const ObjectFile& object) {
    DwarfLines out;
    const auto info = object.dwarf_section(".debug_info");
    const auto abbrev = object.dwarf_section(".debug_abbrev");
    const auto line = object.dwarf_section(".debug_line");
    if (!info || !abbrev || !line) return out;
    const auto str = object.dwarf_section(".debug_str");
    const auto ranges = object.dwarf_section(".debug_ranges");
    std::vector<std::uint64_t> line_offsets;
    InfoReader(object, *info, *abbrev, str ? &*str : nullptr, ranges ? &*ranges : nullptr)
        .read(out, line_offsets);
    Reader lines(*line, object, ".debug_line");
    for (const auto offset : line_offsets) read_line_program(lines, offset, out);
    return out;
}

} // namespace quidra::toolchain
