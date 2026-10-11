// The native code identity gates read code, code relocations and inline
// trees with the same object readers used by the native link recipe.
#include "toolchain/dwarf_lines.hpp"
#include "toolchain/object_file.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace quidra::toolchain;

std::string json(std::string_view text) {
    std::string result = "\"";
    for (unsigned char c : text) {
        if (c == '"' || c == '\\') { result += '\\'; result += c; }
        else if (c < 32) {
            constexpr char digits[] = "0123456789abcdef";
            result += "\\u00"; result += digits[c >> 4]; result += digits[c & 15];
        } else result += c;
    }
    return result + '"';
}

std::string hex(const std::vector<std::uint8_t>& bytes, std::size_t start, std::size_t end) {
    constexpr char digits[] = "0123456789abcdef";
    std::string result;
    for (auto i = start; i < end; ++i) {
        result += digits[bytes[i] >> 4]; result += digits[bytes[i] & 15];
    }
    return result;
}

void relocations(const ObjectFile& object, const ObjectSection& section,
                 std::uint64_t begin, std::uint64_t end) {
    std::vector<std::string> rows;
    for (const auto& relocation : section.relocations) {
        if (relocation.offset < begin || relocation.offset >= end) continue;
        std::string target;
        if (relocation.symbol) {
            const auto& symbol = object.symbols().at(*relocation.symbol);
            target = symbol.name;
            if (symbol.section_symbol && symbol.section)
                target = object.sections().at(*symbol.section).name;
        } else if (relocation.section) target = object.sections().at(*relocation.section).name;
        std::ostringstream row;
        row << '[' << relocation.offset - begin << ',' << relocation.type << ','
            << unsigned(relocation.size) << ',' << relocation.pc_relative << ','
            << relocation.addend << ',' << json(target) << ']';
        rows.push_back(row.str());
    }
    std::sort(rows.begin(), rows.end());
    std::cout << '[';
    for (std::size_t i = 0; i < rows.size(); ++i) std::cout << (i ? "," : "") << rows[i];
    std::cout << ']';
}

void inline_names(const std::vector<DwarfInlined>& tree, std::vector<std::string>& names) {
    for (const auto& node : tree) {
        names.push_back(node.name);
        inline_names(node.children, names);
    }
}
} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 2) throw std::runtime_error("usage: quidra_native_code_info OBJECT");
        const auto object = ObjectFile::read(argv[1]);
        const auto dwarf = read_dwarf_lines(object);
        std::cout << "{\"format\":" << json(object.format() == ObjectFormat::macho ? "macho" :
                    object.format() == ObjectFormat::elf ? "elf" : "coff") << ",\"machine\":" << json(object.machine() == ObjectMachine::arm64 ? "arm64" : "x86_64")
                  << ",\"sections\":{\n";
        bool first = true;
        for (const auto& section : object.sections()) {
            if (!section.code) continue;
            const auto bytes = object.section_bytes(section);
            std::cout << (first ? "" : ",\n") << json(section.name) << ":["
                      << json(hex(bytes, 0, bytes.size())) << ',';
            relocations(object, section, 0, section.size);
            std::cout << ']';
            first = false;
        }
        std::cout << "},\"functions\":{\n";
        first = true;
        for (const auto& symbol : object.symbols()) {
            if (!symbol.section || symbol.section_symbol || symbol.name.empty()) continue;
            const auto& section = object.sections().at(*symbol.section);
            if (!section.code || symbol.address < section.address) continue;
            // Assembler-local labels are not function boundaries.
            if (symbol.name.starts_with("ltmp") || symbol.name.starts_with("L") ||
                symbol.name.starts_with("$")) continue;
            const auto begin = symbol.address - section.address;
            auto end = section.size;
            if (symbol.size) end = std::min(end, begin + symbol.size);
            else for (const auto& next : object.symbols()) {
                if (next.section == symbol.section && !next.section_symbol &&
                    next.address > symbol.address && !next.name.starts_with("L") &&
                    !next.name.starts_with("ltmp") && !next.name.starts_with("$"))
                    end = std::min(end, next.address - section.address);
            }
            for (const auto& function : dwarf.subprograms)
                for (const auto& range : function.ranges)
                    if (range.first == symbol.address)
                        end = std::min(end, range.second - section.address);
            const auto bytes = object.section_bytes(section);
            if (begin > end || end > bytes.size()) throw std::runtime_error("invalid code symbol range");
            std::vector<std::string> inlined;
            std::string logical;
            for (const auto& function : dwarf.subprograms)
                for (const auto& range : function.ranges)
                    if (symbol.address >= range.first && symbol.address < range.second) {
                        logical = function.name;
                        inline_names(function.inlined, inlined);
                    }
            std::sort(inlined.begin(), inlined.end());
            inlined.erase(std::unique(inlined.begin(), inlined.end()), inlined.end());
            std::cout << (first ? "" : ",\n") << json(symbol.name) << ":{\"code\":"
                      << json(hex(bytes, begin, end)) << ",\"relocations\":";
            relocations(object, section, begin, end);
            std::cout << ",\"logical\":" << json(logical) << ",\"inlined\":[";
            for (std::size_t i = 0; i < inlined.size(); ++i)
                std::cout << (i ? "," : "") << json(inlined[i]);
            std::cout << "]}";
            first = false;
        }
        std::cout << "}}\n";
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
