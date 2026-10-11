#include "toolchain/object_file.hpp"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iterator>
#include <stdexcept>

namespace fs = std::filesystem;

namespace quidra::toolchain {

namespace {

// Little-endian reads with bounds checks (every supported object is
// little-endian).
class Bytes {
public:
    Bytes(const std::vector<std::uint8_t>& bytes, const ObjectFile& object)
        : bytes_(bytes), object_(object) {}

    void need(std::uint64_t offset, std::uint64_t size) const {
        if (offset > bytes_.size() || size > bytes_.size() - offset)
            object_.fail("truncated object (" + std::to_string(size) + " bytes at offset " +
                         std::to_string(offset) + ")");
    }
    std::uint8_t u8(std::uint64_t offset) const {
        need(offset, 1);
        return bytes_[offset];
    }
    std::uint16_t u16(std::uint64_t offset) const {
        need(offset, 2);
        return static_cast<std::uint16_t>(bytes_[offset] | (bytes_[offset + 1] << 8));
    }
    std::uint32_t u32(std::uint64_t offset) const {
        need(offset, 4);
        std::uint32_t value = 0;
        for (int i = 3; i >= 0; --i) value = (value << 8) | bytes_[offset + i];
        return value;
    }
    std::uint64_t u64(std::uint64_t offset) const {
        need(offset, 8);
        std::uint64_t value = 0;
        for (int i = 7; i >= 0; --i) value = (value << 8) | bytes_[offset + i];
        return value;
    }
    // A fixed-size name field: up to its first NUL.
    std::string fixed_name(std::uint64_t offset, std::size_t size) const {
        need(offset, size);
        const auto* begin = reinterpret_cast<const char*>(bytes_.data() + offset);
        return std::string(begin, strnlen(begin, size));
    }
    // A NUL-terminated string at `offset` of a string table of `size` bytes
    // at `table`.
    std::string table_string(std::uint64_t table, std::uint64_t size, std::uint64_t offset) const {
        if (offset >= size) object_.fail("string table offset out of range");
        need(table, size);
        const auto* begin = reinterpret_cast<const char*>(bytes_.data() + table + offset);
        return std::string(begin, strnlen(begin, static_cast<std::size_t>(size - offset)));
    }

private:
    const std::vector<std::uint8_t>& bytes_;
    const ObjectFile& object_;
};

void put_u32(std::vector<std::uint8_t>& out, std::uint64_t offset, std::uint32_t value) {
    for (int i = 0; i < 4; ++i) out[offset + i] = static_cast<std::uint8_t>(value >> (8 * i));
}
void put_u64(std::vector<std::uint8_t>& out, std::uint64_t offset, std::uint64_t value) {
    for (int i = 0; i < 8; ++i) out[offset + i] = static_cast<std::uint8_t>(value >> (8 * i));
}
std::uint64_t get_u32(const std::vector<std::uint8_t>& in, std::uint64_t offset) {
    std::uint64_t value = 0;
    for (int i = 3; i >= 0; --i) value = (value << 8) | in[offset + i];
    return value;
}
std::uint64_t get_u64(const std::vector<std::uint8_t>& in, std::uint64_t offset) {
    std::uint64_t value = 0;
    for (int i = 7; i >= 0; --i) value = (value << 8) | in[offset + i];
    return value;
}

std::uint64_t align_up(std::uint64_t value, std::uint64_t alignment) {
    if (alignment <= 1) return value;
    return (value + alignment - 1) / alignment * alignment;
}

// Where the laid-out sections of an ELF or COFF object start: never 0, so
// that no code address is 0.
constexpr std::uint64_t layout_base = 0x1000;

// Mach-O.
constexpr std::uint32_t mh_magic_64 = 0xfeedfacf;
constexpr std::uint32_t cpu_type_arm64 = 0x0100000c;
constexpr std::uint32_t cpu_type_x86_64 = 0x01000007;
constexpr std::uint32_t lc_segment_64 = 0x19;
constexpr std::uint32_t lc_symtab = 0x2;

// ELF.
constexpr std::uint16_t em_x86_64 = 62;
constexpr std::uint16_t em_aarch64 = 183;
constexpr std::uint32_t sht_symtab = 2;
constexpr std::uint32_t sht_rela = 4;
constexpr std::uint32_t sht_nobits = 8;
constexpr std::uint32_t sht_rel = 9;
constexpr std::uint64_t shf_alloc = 0x2;
constexpr std::uint64_t shf_execinstr = 0x4;
constexpr std::uint32_t r_x86_64_64 = 1;
constexpr std::uint32_t r_x86_64_32 = 10;
constexpr std::uint32_t r_aarch64_abs64 = 257;
constexpr std::uint32_t r_aarch64_abs32 = 258;

// COFF.
constexpr std::uint16_t image_file_machine_amd64 = 0x8664;
constexpr std::uint16_t image_file_machine_arm64 = 0xaa64;
constexpr std::uint32_t image_scn_cnt_code = 0x20;
constexpr std::uint32_t image_scn_cnt_uninitialized_data = 0x80;
constexpr std::uint32_t image_scn_lnk_nreloc_ovfl = 0x01000000;
constexpr std::uint32_t image_scn_mem_discardable = 0x02000000;
constexpr std::uint16_t image_rel_amd64_addr64 = 0x1;
constexpr std::uint16_t image_rel_amd64_secrel = 0xb;
constexpr std::uint16_t image_rel_arm64_secrel = 0x8;
constexpr std::uint16_t image_rel_arm64_addr64 = 0xe;

} // namespace

ObjectFile ObjectFile::read(const fs::path& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) throw std::runtime_error(path.string() + ": cannot read the object");
    std::vector<std::uint8_t> bytes((std::istreambuf_iterator<char>(in)),
                                    std::istreambuf_iterator<char>());
    if (in.bad()) throw std::runtime_error(path.string() + ": cannot read the object");
    return parse(std::move(bytes), path.string());
}

ObjectFile ObjectFile::parse(std::vector<std::uint8_t> bytes, std::string name) {
    ObjectFile object;
    object.name_ = std::move(name);
    object.bytes_ = std::move(bytes);
    const auto& b = object.bytes_;
    if (b.size() >= 4 && b[0] == 0xcf && b[1] == 0xfa && b[2] == 0xed && b[3] == 0xfe) {
        object.format_ = ObjectFormat::macho;
        object.parse_macho();
    } else if (b.size() >= 4 && b[0] == 0x7f && b[1] == 'E' && b[2] == 'L' && b[3] == 'F') {
        object.format_ = ObjectFormat::elf;
        object.parse_elf();
    } else if (b.size() >= 2 && ((b[0] == 0x64 && b[1] == 0x86) || (b[0] == 0x64 && b[1] == 0xaa))) {
        object.format_ = ObjectFormat::coff;
        object.parse_coff();
    } else {
        object.fail("not a 64-bit Mach-O, ELF or COFF object");
    }
    return object;
}

void ObjectFile::fail(const std::string& message) const {
    throw std::runtime_error(name_ + ": " + message);
}

const ObjectSection* ObjectFile::section(std::string_view name) const {
    for (const auto& section : sections_)
        if (section.name == name) return &section;
    return nullptr;
}

std::vector<std::uint8_t> ObjectFile::section_bytes(const ObjectSection& section) const {
    if (!section.file_offset) return {};
    Bytes(bytes_, *this).need(*section.file_offset, section.size);
    const auto begin = bytes_.begin() + static_cast<std::ptrdiff_t>(*section.file_offset);
    return std::vector<std::uint8_t>(begin, begin + static_cast<std::ptrdiff_t>(section.size));
}

void ObjectFile::parse_macho() {
    const Bytes b(bytes_, *this);
    if (b.u32(0) != mh_magic_64) fail("not a 64-bit little-endian Mach-O object");
    const auto cpu = b.u32(4);
    if (cpu == cpu_type_arm64) machine_ = ObjectMachine::arm64;
    else if (cpu == cpu_type_x86_64) machine_ = ObjectMachine::x86_64;
    else fail("unsupported Mach-O CPU type " + std::to_string(cpu));
    const auto commands = b.u32(16);
    std::uint64_t offset = 32;
    std::uint32_t symbol_offset = 0, symbol_count = 0, string_offset = 0, string_size = 0;
    bool has_symtab = false;
    for (std::uint32_t i = 0; i < commands; ++i) {
        const auto command = b.u32(offset);
        const auto size = b.u32(offset + 4);
        if (size < 8) fail("malformed load command");
        if (command == lc_segment_64) {
            const auto count = b.u32(offset + 64);
            for (std::uint32_t s = 0; s < count; ++s) {
                const auto at = offset + 72 + std::uint64_t{80} * s;
                ObjectSection section;
                section.name = b.fixed_name(at, 16);
                section.segment = b.fixed_name(at + 16, 16);
                section.address = b.u64(at + 32);
                section.size = b.u64(at + 40);
                const auto file_offset = b.u32(at + 48);
                const auto relocation_offset = b.u32(at + 56);
                const auto relocation_count = b.u32(at + 60);
                const auto flags = b.u32(at + 64);
                const auto type = flags & 0xff;
                // S_ZEROFILL, S_GB_ZEROFILL, S_THREAD_LOCAL_ZEROFILL
                if (type != 0x1 && type != 0xc && type != 0x12) section.file_offset = file_offset;
                section.code = (flags & 0x80000000u) || (flags & 0x400u);
                for (std::uint32_t r = 0; r < relocation_count; ++r) {
                    const auto entry = relocation_offset + std::uint64_t{8} * r;
                    const auto address = b.u32(entry);
                    if (address & 0x80000000u) fail("scattered relocations are not supported");
                    const auto bits = b.u32(entry + 4);
                    ObjectRelocation relocation;
                    relocation.offset = address;
                    relocation.type = bits >> 28;
                    relocation.pc_relative = (bits >> 24) & 1;
                    relocation.size = static_cast<std::uint8_t>(1u << ((bits >> 25) & 3));
                    const bool external = (bits >> 27) & 1;
                    const auto index = bits & 0x00ffffffu;
                    if (machine_ == ObjectMachine::arm64 && relocation.type == 10) {
                        // ARM64_RELOC_ADDEND encodes a signed 24-bit addend,
                        // rather than a symbol or section ordinal.
                        relocation.addend = index & 0x00800000u
                            ? static_cast<std::int64_t>(index) - 0x01000000
                            : static_cast<std::int64_t>(index);
                    } else if (external) relocation.symbol = index;
                    else if (index != 0) relocation.section = index - 1;
                    section.relocations.push_back(relocation);
                }
                sections_.push_back(std::move(section));
            }
        } else if (command == lc_symtab) {
            symbol_offset = b.u32(offset + 8);
            symbol_count = b.u32(offset + 12);
            string_offset = b.u32(offset + 16);
            string_size = b.u32(offset + 20);
            has_symtab = true;
        }
        offset += size;
    }
    if (!has_symtab) return;
    for (std::uint32_t i = 0; i < symbol_count; ++i) {
        const auto at = symbol_offset + std::uint64_t{16} * i;
        ObjectSymbol symbol;
        const auto name = b.u32(at);
        const auto type = b.u8(at + 4);
        const auto section = b.u8(at + 5);
        symbol.name = name < string_size ? b.table_string(string_offset, string_size, name) : "";
        const bool stab = (type & 0xe0) != 0;
        if (!stab && (type & 0x0e) == 0x0e && section != 0 && section <= sections_.size()) {
            symbol.section = section - 1u;
            symbol.address = b.u64(at + 8);
        }
        symbol.global = (type & 0x01) != 0;
        symbols_.push_back(std::move(symbol));
    }
}

void ObjectFile::parse_elf() {
    const Bytes b(bytes_, *this);
    if (b.u8(4) != 2 || b.u8(5) != 1) fail("not a 64-bit little-endian ELF object");
    const auto machine = b.u16(18);
    if (machine == em_x86_64) machine_ = ObjectMachine::x86_64;
    else if (machine == em_aarch64) machine_ = ObjectMachine::arm64;
    else fail("unsupported ELF machine " + std::to_string(machine));
    const auto section_offset = b.u64(40);
    const auto entry_size = b.u16(58);
    const auto count = b.u16(60);
    const auto names_index = b.u16(62);
    if (entry_size != 64) fail("unexpected ELF section header size");
    struct Header {
        std::uint32_t name, type;
        std::uint64_t flags, offset, size;
        std::uint32_t link, info;
        std::uint64_t alignment, entry;
    };
    std::vector<Header> headers(count);
    for (std::uint16_t i = 0; i < count; ++i) {
        const auto at = section_offset + std::uint64_t{64} * i;
        headers[i] = Header{b.u32(at), b.u32(at + 4), b.u64(at + 8), b.u64(at + 24),
                            b.u64(at + 32), b.u32(at + 40), b.u32(at + 44), b.u64(at + 48),
                            b.u64(at + 56)};
    }
    if (names_index >= count) fail("malformed ELF section name table index");
    const auto& names = headers[names_index];
    std::uint64_t next = layout_base;
    for (std::uint16_t i = 0; i < count; ++i) {
        const auto& header = headers[i];
        ObjectSection section;
        section.name = i == 0 ? "" : b.table_string(names.offset, names.size, header.name);
        section.size = header.size;
        if (header.type != sht_nobits && i != 0) section.file_offset = header.offset;
        section.code = (header.flags & shf_execinstr) != 0;
        if (header.flags & shf_alloc) {
            section.address = align_up(next, header.alignment);
            next = section.address + header.size;
        }
        sections_.push_back(std::move(section));
    }
    // Symbols: the one symbol table, by index (index 0 is the null symbol).
    for (std::uint16_t i = 0; i < count; ++i) {
        const auto& header = headers[i];
        if (header.type != sht_symtab) continue;
        if (header.link >= count) fail("malformed ELF symbol table");
        const auto& strings = headers[header.link];
        const auto symbols = header.size / 24;
        for (std::uint64_t s = 0; s < symbols; ++s) {
            const auto at = header.offset + 24 * s;
            ObjectSymbol symbol;
            const auto name = b.u32(at);
            const auto info = b.u8(at + 4);
            const auto index = b.u16(at + 6);
            const auto value = b.u64(at + 8);
            symbol.name = b.table_string(strings.offset, strings.size, name);
            symbol.global = (info >> 4) != 0;
            symbol.section_symbol = (info & 0xf) == 3;
            if (index == 0xffff) fail("extended ELF section indices are not supported");
            if (index != 0 && index < count) {
                symbol.section = index;
                symbol.address = sections_[index].address + value;
            }
            symbol.size = b.u64(at + 16);
            // STT_FILE names no code.
            if ((info & 0xf) == 4) symbol.section.reset();
            symbols_.push_back(std::move(symbol));
        }
        break;
    }
    // Relocations: RELA sections, attached to the section they apply to.
    for (std::uint16_t i = 0; i < count; ++i) {
        const auto& header = headers[i];
        if (header.type == sht_rel) fail("ELF REL relocations are not supported");
        if (header.type != sht_rela) continue;
        if (header.info >= count) fail("malformed ELF relocation section");
        auto& target = sections_[header.info];
        const auto entries = header.size / 24;
        for (std::uint64_t r = 0; r < entries; ++r) {
            const auto at = header.offset + 24 * r;
            ObjectRelocation relocation;
            relocation.offset = b.u64(at);
            const auto info = b.u64(at + 8);
            relocation.type = static_cast<std::uint32_t>(info & 0xffffffffu);
            relocation.symbol = static_cast<std::size_t>(info >> 32);
            relocation.addend = static_cast<std::int64_t>(b.u64(at + 16));
            // R_X86_64_64, R_X86_64_PC64, R_AARCH64_ABS64, R_AARCH64_PREL64:
            // 8 bytes; the other kinds 4 (or an instruction).
            const bool wide = machine_ == ObjectMachine::x86_64
                                  ? relocation.type == 1 || relocation.type == 24
                                  : relocation.type == 257 || relocation.type == 260;
            relocation.size = wide ? 8 : 4;
            target.relocations.push_back(relocation);
        }
    }
}

void ObjectFile::parse_coff() {
    const Bytes b(bytes_, *this);
    const auto machine = b.u16(0);
    if (machine == image_file_machine_amd64) machine_ = ObjectMachine::x86_64;
    else if (machine == image_file_machine_arm64) machine_ = ObjectMachine::arm64;
    else fail("unsupported COFF machine");
    const auto count = b.u16(2);
    const auto symbol_table = b.u32(8);
    const auto symbol_count = b.u32(12);
    const auto optional_size = b.u16(16);
    const std::uint64_t string_table = symbol_table + std::uint64_t{18} * symbol_count;
    const std::uint32_t string_size = symbol_count != 0 ? b.u32(string_table) : 0;
    const auto long_name = [&](std::uint64_t offset) {
        return b.table_string(string_table, string_size, offset);
    };
    std::uint64_t next = layout_base;
    std::vector<std::uint32_t> characteristics;
    for (std::uint16_t i = 0; i < count; ++i) {
        const auto at = 20 + std::uint64_t{optional_size} + std::uint64_t{40} * i;
        ObjectSection section;
        auto name = b.fixed_name(at, 8);
        if (!name.empty() && name[0] == '/') {
            std::uint64_t offset = 0;
            for (std::size_t c = 1; c < name.size(); ++c) {
                if (name[c] < '0' || name[c] > '9') fail("malformed COFF section name");
                offset = offset * 10 + static_cast<std::uint64_t>(name[c] - '0');
            }
            name = long_name(offset);
        }
        section.name = name;
        section.size = b.u32(at + 16);
        const auto raw = b.u32(at + 20);
        const auto relocations = b.u32(at + 24);
        const auto relocation_count = b.u16(at + 32);
        const auto flags = b.u32(at + 36);
        characteristics.push_back(flags);
        if (!(flags & image_scn_cnt_uninitialized_data) && raw != 0) section.file_offset = raw;
        section.code = (flags & image_scn_cnt_code) != 0;
        if (!(flags & image_scn_mem_discardable)) {
            // The alignment is encoded in bits 20-23 (IMAGE_SCN_ALIGN_*).
            const auto encoded = (flags >> 20) & 0xf;
            const std::uint64_t alignment = encoded == 0 ? 16 : (std::uint64_t{1} << (encoded - 1));
            section.address = align_up(next, alignment);
            next = section.address + section.size;
        }
        if (flags & image_scn_lnk_nreloc_ovfl) fail("COFF relocation count overflow is not supported");
        for (std::uint32_t r = 0; r < relocation_count; ++r) {
            const auto entry = relocations + std::uint64_t{10} * r;
            ObjectRelocation relocation;
            relocation.offset = b.u32(entry);
            relocation.symbol = b.u32(entry + 4);
            relocation.type = b.u16(entry + 8);
            const bool wide = machine_ == ObjectMachine::x86_64 ? relocation.type == image_rel_amd64_addr64
                                                                : relocation.type == image_rel_arm64_addr64;
            relocation.size = wide ? 8 : 4;
            section.relocations.push_back(relocation);
        }
        sections_.push_back(std::move(section));
    }
    // Symbols by their raw index: an auxiliary record keeps its slot (an
    // empty symbol), so that relocations index the table directly.
    for (std::uint32_t i = 0; i < symbol_count; ++i) {
        const auto at = symbol_table + std::uint64_t{18} * i;
        ObjectSymbol symbol;
        if (b.u32(at) == 0) symbol.name = long_name(b.u32(at + 4));
        else symbol.name = b.fixed_name(at, 8);
        const auto value = b.u32(at + 8);
        const auto section = static_cast<std::int16_t>(b.u16(at + 12));
        const auto storage = b.u8(at + 16);
        const auto aux = b.u8(at + 17);
        symbol.global = storage == 2;  // IMAGE_SYM_CLASS_EXTERNAL
        if (section > 0 && static_cast<std::size_t>(section) <= sections_.size()) {
            symbol.section = static_cast<std::size_t>(section - 1);
            symbol.address = sections_[*symbol.section].address + value;
            symbol.section_symbol = storage == 3 && value == 0 && aux != 0;
        }
        symbols_.push_back(std::move(symbol));
        for (std::uint8_t a = 0; a < aux; ++a) symbols_.push_back(ObjectSymbol{});
        i += aux;
    }
}

std::optional<std::vector<std::uint8_t>> ObjectFile::dwarf_section(std::string_view name) const {
    std::string spelled(name);
    if (format_ == ObjectFormat::macho && spelled.size() > 1 && spelled[0] == '.')
        spelled = "__" + spelled.substr(1);
    const ObjectSection* found = nullptr;
    for (const auto& section : sections_) {
        if (section.name != spelled) continue;
        if (format_ == ObjectFormat::macho && section.segment != "__DWARF") continue;
        found = &section;
        break;
    }
    if (!found) return std::nullopt;
    auto bytes = section_bytes(*found);
    if (format_ == ObjectFormat::macho) return bytes;
    for (const auto& relocation : found->relocations) {
        if (!relocation.symbol || *relocation.symbol >= symbols_.size())
            fail("a relocation of " + std::string(name) + " names no symbol");
        const auto& symbol = symbols_[*relocation.symbol];
        // The symbol's address, and its offset in its own section for the
        // section-relative kinds.
        const auto address = symbol.address;
        const auto relative =
            symbol.section ? symbol.address - sections_[*symbol.section].address : 0;
        bool wide = false;
        bool section_relative = false;
        if (format_ == ObjectFormat::elf) {
            if (relocation.type == (machine_ == ObjectMachine::x86_64 ? r_x86_64_64 : r_aarch64_abs64))
                wide = true;
            else if (relocation.type == (machine_ == ObjectMachine::x86_64 ? r_x86_64_32 : r_aarch64_abs32))
                section_relative = true;
            else
                fail("unexpected relocation type " + std::to_string(relocation.type) + " in " +
                     std::string(name));
        } else {
            const auto addr64 = machine_ == ObjectMachine::x86_64 ? image_rel_amd64_addr64
                                                                  : image_rel_arm64_addr64;
            const auto secrel = machine_ == ObjectMachine::x86_64 ? image_rel_amd64_secrel
                                                                  : image_rel_arm64_secrel;
            if (relocation.type == addr64) wide = true;
            else if (relocation.type == secrel) section_relative = true;
            else
                fail("unexpected relocation type " + std::to_string(relocation.type) + " in " +
                     std::string(name));
        }
        const std::uint64_t size = wide ? 8 : 4;
        if (relocation.offset > bytes.size() || size > bytes.size() - relocation.offset)
            fail("a relocation of " + std::string(name) + " lies outside the section");
        // ELF: the addend is the relocation's; COFF: it is in place.
        const std::int64_t addend =
            format_ == ObjectFormat::elf
                ? relocation.addend
                : static_cast<std::int64_t>(wide ? get_u64(bytes, relocation.offset)
                                                 : get_u32(bytes, relocation.offset));
        // A 32-bit field of DWARF is an offset into a debug section: the
        // offset of the symbol in its section (a debug section's address is
        // 0 on ELF, so both formats agree).
        const auto base = section_relative ? relative : address;
        const auto value = base + static_cast<std::uint64_t>(addend);
        if (wide) put_u64(bytes, relocation.offset, value);
        else put_u32(bytes, relocation.offset, static_cast<std::uint32_t>(value));
    }
    return bytes;
}

} // namespace quidra::toolchain
