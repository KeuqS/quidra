#pragma once

// ObjectFile: the sections, symbols and relocations of one relocatable
// object that the C++ driver compiled, as the call-site table step reads
// them (toolchain/call_site_table.hpp): 64-bit Mach-O (arm64, x86-64), ELF
// (AArch64, x86-64) and COFF (x86-64, arm64).
//
// Addresses: every section has an address in one address space for the
// whole object, so that the DWARF of all code sections, the symbols and the
// line rows compare directly. Mach-O objects have such addresses already
// (the section addresses of the object), and their DWARF holds them in
// place. ELF and COFF sections all start at 0; the reader lays the
// allocated (ELF) or non-discardable (COFF) sections out one after the
// other, and dwarf_section() applies the relocations of a DWARF section,
// which hold zeros (ELF, RELA) or an addend (COFF, REL) in place: only the
// kinds LLVM uses in DWARF, the 64-bit absolute address and the 32-bit
// section-relative offset.
//
// Errors: a malformed or unsupported object, or a relocation kind outside
// that set in a DWARF section, throws std::runtime_error naming the object.

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace quidra::toolchain {

enum class ObjectFormat { macho, elf, coff };
enum class ObjectMachine { arm64, x86_64 };

struct ObjectRelocation {
    // The offset of the field in its section.
    std::uint64_t offset{};
    // The format's relocation type.
    std::uint32_t type{};
    // The symbol (an index into ObjectFile::symbols), or none: a Mach-O
    // relocation against a section (`section`).
    std::optional<std::size_t> symbol;
    std::optional<std::size_t> section;
    // ELF RELA's or Mach-O ARM64_RELOC_ADDEND's signed addend.
    // Other formats keep the addend in place.
    std::int64_t addend{};
    bool pc_relative{};
    // The field's size in bytes.
    std::uint8_t size{};
};

struct ObjectSection {
    // Mach-O: the section name ("__text", "__debug_info") and its segment
    // ("__TEXT", "__DWARF"); ELF and COFF: the name (".text",
    // ".debug_info") and no segment.
    std::string name;
    std::string segment;
    std::uint64_t address{};
    std::uint64_t size{};
    // Where its bytes are in the file (none for zero-fill sections).
    std::optional<std::uint64_t> file_offset;
    bool code{};
    std::vector<ObjectRelocation> relocations;
};

struct ObjectSymbol {
    std::string name;
    // The defining section, or none (undefined, absolute, common).
    std::optional<std::size_t> section;
    // A defined symbol's address (in the object's address space); 0
    // otherwise.
    std::uint64_t address{};
    bool global{};
    // A section symbol (ELF STT_SECTION, COFF static section symbols).
    bool section_symbol{};
    // The symbol's size where the format records one (ELF); 0 otherwise.
    std::uint64_t size{};
};

class ObjectFile {
public:
    // Reads and parses `path`.
    static ObjectFile read(const std::filesystem::path& path);
    // Parses an object image; `name` is the object's name in messages.
    static ObjectFile parse(std::vector<std::uint8_t> bytes, std::string name);

    ObjectFormat format() const { return format_; }
    ObjectMachine machine() const { return machine_; }
    const std::string& name() const { return name_; }
    const std::vector<ObjectSection>& sections() const { return sections_; }
    const std::vector<ObjectSymbol>& symbols() const { return symbols_; }

    // A section by its name (Mach-O: in any segment).
    const ObjectSection* section(std::string_view name) const;
    // The bytes of a section (empty for a zero-fill one).
    std::vector<std::uint8_t> section_bytes(const ObjectSection& section) const;
    // The DWARF section `name` (".debug_info" or, on Mach-O, its "__debug_info"
    // spelling is found from the same name) with its relocations applied;
    // none if the object has no such section.
    std::optional<std::vector<std::uint8_t>> dwarf_section(std::string_view name) const;

    // Throws std::runtime_error: "<object>: <message>".
    [[noreturn]] void fail(const std::string& message) const;

private:
    void parse_macho();
    void parse_elf();
    void parse_coff();

    std::string name_;
    std::vector<std::uint8_t> bytes_;
    ObjectFormat format_{ObjectFormat::macho};
    ObjectMachine machine_{ObjectMachine::arm64};
    std::vector<ObjectSection> sections_;
    std::vector<ObjectSymbol> symbols_;
};

} // namespace quidra::toolchain
