#include "platform/process.hpp"
#include "platform/temporary_directory.hpp"
#include "quidra/abi/call_site_table.hpp"
#include "quidra/call_site_info.hpp"
#include "toolchain/call_site_table.hpp"
#include "toolchain/dwarf_lines.hpp"
#include "toolchain/llvm_discovery.hpp"
#include "toolchain/object_file.hpp"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

// The call-site table step (src/toolchain/call_site_table.hpp) on objects
// the host's Clang compiles from a small LLVM module: the object reader,
// the DWARF decoder and the table's entries for every object format the
// driver can target here (the host's always; Mach-O, ELF and COFF for
// arm64 and x86-64 where the driver has the target):
// - line rows whose lines are site ids, and an inlined call's chain;
// - DW_AT_name through .debug_str (relocated in ELF and COFF objects);
// - the symbol classes: a function, a fragment (<name>.cold.<N>), a clone
//   (<name>.<suffix>) and an unknown outlined function, the local ones
//   located through the branch to them;
// - the table module compiles;
// - an object whose line table names a site the module does not have is
//   refused.

namespace fs = std::filesystem;
using namespace quidra;
using namespace quidra::toolchain;

namespace {

int failures = 0;

void expect(bool condition, const std::string& what) {
    if (!condition) {
        std::fprintf(stderr, "call-site table test failed: %s\n", what.c_str());
        ++failures;
    }
}

void signed_arm64_addend() {
    std::vector<std::uint8_t> image(196);
    const auto word = [&](std::size_t offset, std::uint32_t value) {
        for (unsigned i = 0; i < 4; ++i) image[offset + i] = (value >> (8 * i)) & 255;
    };
    // One Mach-O arm64 code section, one ADDEND relocation, no symbols.
    word(0, 0xfeedfacf); word(4, 0x100000c); word(12, 1);
    word(16, 1); word(20, 152); word(32, 0x19); word(36, 152);
    std::memcpy(image.data() + 40, "__TEXT", 6);
    word(64, 4); word(72, 184); word(80, 4);
    word(88, 7); word(92, 7); word(96, 1);
    std::memcpy(image.data() + 104, "__text", 6);
    std::memcpy(image.data() + 120, "__TEXT", 6);
    word(144, 4); word(152, 184); word(156, 2);
    word(160, 188); word(164, 1); word(168, 0x80000400);
    word(184, 0xd65f03c0); word(192, (10u << 28) | (2u << 25) | 0xfffffc);
    auto object = ObjectFile::parse(image, "signed-addend");
    const auto& negative = object.sections().at(0).relocations.at(0);
    expect(negative.addend == -4 && !negative.symbol && !negative.section,
           "a negative arm64 addend is not a section ordinal");
    word(192, (10u << 28) | (2u << 25) | 4);
    object = ObjectFile::parse(std::move(image), "positive-addend");
    const auto& positive = object.sections().at(0).relocations.at(0);
    expect(positive.addend == 4 && !positive.symbol && !positive.section,
           "a positive arm64 addend is not a section ordinal");
}

void write_text(const fs::path& path, const std::string& text) {
    std::ofstream out(path, std::ios::binary);
    out << text;
    if (!out) throw std::runtime_error("cannot write " + path.string());
}

// Sites (lines): 1 n_pick -> n_pick.cold.1, 2 n_pick.cold.1 -> fail,
// 3 n_sum -> n_pick, 4 n_sum -> n_twice (inlined), 5 n_twice -> ext,
// 6 n_sum -> ext, 7 OUTLINED_FUNCTION_0 -> ext, 8 n_sum ->
// OUTLINED_FUNCTION_0, 9 n_sum -> n_scale.specialized.1, 10
// n_scale.specialized.1 -> ext.
const char* fixture = R"(declare void @fail(i64) noreturn
declare void @ext(i64)

define internal void @"n_pick.cold.1"(i64 %i) noinline cold noreturn !dbg !20 {
  call void @fail(i64 %i), !dbg !21
  unreachable
}

define i64 @n_pick(ptr %a, i64 %i) noinline !dbg !10 {
entry:
  %c = icmp ugt i64 %i, 3
  br i1 %c, label %bad, label %ok
bad:
  call void @"n_pick.cold.1"(i64 %i), !dbg !11
  unreachable
ok:
  %p = getelementptr i64, ptr %a, i64 %i
  %v = load i64, ptr %p
  ret i64 %v
}

define internal i64 @n_twice(i64 %x) alwaysinline !dbg !30 {
  call void @ext(i64 %x), !dbg !31
  %y = mul i64 %x, 2
  ret i64 %y
}

define internal void @OUTLINED_FUNCTION_0(i64 %x) noinline !dbg !40 {
  call void @ext(i64 %x), !dbg !41
  ret void
}

define internal void @"n_scale.specialized.1"(i64 %x) noinline !dbg !50 {
  call void @ext(i64 %x), !dbg !51
  ret void
}

define i64 @n_sum(ptr %a, i64 %n) !dbg !12 {
entry:
  %x = call i64 @n_pick(ptr %a, i64 %n), !dbg !13
  %t = call i64 @n_twice(i64 %x), !dbg !14
  call void @ext(i64 %t), !dbg !15
  call void @OUTLINED_FUNCTION_0(i64 %t), !dbg !16
  call void @"n_scale.specialized.1"(i64 %x), !dbg !17
  call void @ext(i64 %x), !dbg !15
  ret i64 %t
}

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3}
!0 = distinct !DICompileUnit(language: DW_LANG_C11, file: !1, producer: "Quidra", isOptimized: true, runtimeVersion: 0, emissionKind: LineTablesOnly)
!1 = !DIFile(filename: "quidra-call-sites", directory: "")
!2 = !{i32 2, !"Dwarf Version", i32 4}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !DISubroutineType(types: !5)
!5 = !{}
!10 = distinct !DISubprogram(name: "n_pick", scope: !1, file: !1, type: !4, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0)
!11 = !DILocation(line: 1, scope: !10)
!12 = distinct !DISubprogram(name: "n_sum", scope: !1, file: !1, type: !4, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0)
!13 = !DILocation(line: 3, scope: !12)
!14 = !DILocation(line: 4, scope: !12)
!15 = !DILocation(line: 6, scope: !12)
!16 = !DILocation(line: 8, scope: !12)
!17 = !DILocation(line: 9, scope: !12)
!20 = distinct !DISubprogram(name: "n_pick.cold.1", scope: !1, file: !1, type: !4, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0)
!21 = !DILocation(line: 2, scope: !20)
!30 = distinct !DISubprogram(name: "n_twice", scope: !1, file: !1, type: !4, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0)
!31 = !DILocation(line: 5, scope: !30)
!40 = distinct !DISubprogram(name: "OUTLINED_FUNCTION_0", scope: !1, file: !1, type: !4, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0)
!41 = !DILocation(line: 7, scope: !40)
!50 = distinct !DISubprogram(name: "n_scale.specialized.1", scope: !1, file: !1, type: !4, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0)
!51 = !DILocation(line: 10, scope: !50)
)";

CallSiteInfo fixture_info() {
    CallSiteInfo info;
    const auto function = [&](const char* display, const char* symbol) {
        CallSiteFunction f;
        f.display = display;
        f.symbols.push_back(symbol);
        info.functions.push_back(std::move(f));
    };
    function("pick()", "n_pick");   // 0
    function("sum()", "n_sum");     // 1
    function("twice()", "n_twice"); // 2
    function("scale()", "n_scale"); // 3
    const auto site = [&](std::uint32_t owner, CallSiteCallee kind, std::uint32_t callee) {
        CallSite s;
        s.owner = owner;
        s.callee_kind = kind;
        s.callee = callee;
        s.flags = call_site_flags::user;
        s.line = static_cast<std::uint32_t>(info.sites.size());
        info.sites.push_back(s);
    };
    site(0, CallSiteCallee::runtime, 0);   // 1
    site(0, CallSiteCallee::runtime, 0);   // 2
    site(1, CallSiteCallee::function, 0);  // 3
    site(1, CallSiteCallee::function, 2);  // 4
    site(2, CallSiteCallee::runtime, 0);   // 5
    site(1, CallSiteCallee::runtime, 0);   // 6
    site(1, CallSiteCallee::runtime, 0);   // 7
    site(1, CallSiteCallee::runtime, 0);   // 8
    site(1, CallSiteCallee::function, 3);  // 9
    site(3, CallSiteCallee::runtime, 0);   // 10
    return info;
}

// Decode the shared constant to inspect the serialized ABI flags, rather
// than searching for an escape sequence that could also be a site field.
std::vector<std::uint8_t> constant_bytes(const std::string& module, const std::string& name) {
    const auto declaration = module.find(name + " = ");
    const auto start = module.find("c\"", declaration);
    if (declaration == std::string::npos || start == std::string::npos)
        throw std::runtime_error("missing call-site constant");
    std::vector<std::uint8_t> bytes;
    for (auto i = start + 2; i < module.size() && module[i] != '\"'; ++i) {
        if (module[i] == '\\') {
            bytes.push_back(static_cast<std::uint8_t>(std::stoul(module.substr(i + 1, 2), nullptr, 16)));
            i += 2;
        } else bytes.push_back(static_cast<std::uint8_t>(module[i]));
    }
    return bytes;
}

bool compile(const fs::path& source, const fs::path& object, const std::string& target) {
    const std::vector<std::string> arguments{"--target=" + target, "-O2", "-Wno-override-module",
                                             "-c", "-x", "ir", source.string(), "-o", object.string()};
    try {
        return platform::run_program(fs::path(clang_driver()), arguments) == 0 &&
               fs::is_regular_file(object);
    } catch (const std::exception&) {
        return false;
    }
}

const CallSiteTableEntry* entry_named(const std::vector<CallSiteTableEntry>& entries,
                                      const std::string& name) {
    for (const auto& entry : entries)
        if (entry.name == name) return &entry;
    return nullptr;
}

bool has_chain(const CallSiteTableEntry& entry, const std::vector<std::uint32_t>& chain) {
    return std::any_of(entry.rows.begin(), entry.rows.end(),
                       [&](const CallSiteTableRow& row) { return row.chain == chain; });
}

void check_target(const fs::path& root, const std::string& target, bool required) {
    const auto source = root / "fixture.ll";
    const auto object = root / (target + ".o");
    if (!compile(source, object, target)) {
        expect(!required, target + ": the host target compiles");
        if (!required) std::printf("skip %s (the driver cannot target it)\n", target.c_str());
        return;
    }
    const auto file = ObjectFile::read(object);
    const auto lines = read_dwarf_lines(file);
    expect(!lines.rows.empty(), target + ": line rows");
    const auto names = [&]() {
        std::vector<std::string> out;
        for (const auto& subprogram : lines.subprograms) out.push_back(subprogram.name);
        return out;
    }();
    // Line-tables-only DWARF has a subprogram for every function on Darwin,
    // and elsewhere only for one with inlined calls.
    const bool darwin = target.find("apple") != std::string::npos;
    for (const auto* name : {"n_pick", "n_sum", "n_pick.cold.1", "OUTLINED_FUNCTION_0",
                             "n_scale.specialized.1"}) {
        if (!darwin && std::string(name) != "n_sum") continue;
        expect(std::find(names.begin(), names.end(), name) != names.end(),
               target + ": a subprogram named " + name);
    }
    const auto sum = std::find_if(lines.subprograms.begin(), lines.subprograms.end(),
                                  [](const DwarfSubprogram& s) { return s.name == "n_sum"; });
    if (sum != lines.subprograms.end()) {
        expect(sum->inlined.size() == 1 && sum->inlined.front().call_line == 4 &&
                   sum->inlined.front().name == "n_twice",
               target + ": n_twice inlined into n_sum at site 4");
    }

    auto info = fixture_info();
    info.sites[1].file = 65536;
    info.sites[1].column = 70000;
    const auto entries = call_site_table_entries(file, lines, info);
    const auto* pick = entry_named(entries, "n_pick");
    const auto* sum_entry = entry_named(entries, "n_sum");
    const auto* cold = entry_named(entries, "n_pick.cold.1");
    const auto* outlined = entry_named(entries, "OUTLINED_FUNCTION_0");
    const auto* clone = entry_named(entries, "n_scale.specialized.1");
    expect(pick && pick->symbol_class == CallSiteSymbolClass::function && pick->function == 0 &&
               !pick->branch_offset && pick->reference == "n_pick" && has_chain(*pick, {1}),
           target + ": n_pick is a function with its call of the fragment");
    expect(sum_entry && sum_entry->function == 1 && has_chain(*sum_entry, {3}) &&
               has_chain(*sum_entry, {5, 4}) && has_chain(*sum_entry, {6}) && has_chain(*sum_entry, {8}),
           target + ": n_sum's rows, with the inlined call's chain");
    expect(cold && cold->symbol_class == CallSiteSymbolClass::fragment && cold->function == 0 &&
               cold->branch_offset && cold->reference == "n_pick" && has_chain(*cold, {2}),
           target + ": the fragment is located through n_pick's branch to it");
    expect(outlined && outlined->symbol_class == CallSiteSymbolClass::unknown &&
               outlined->branch_offset && outlined->reference == "n_sum" && has_chain(*outlined, {7}),
           target + ": the outlined function is unknown, located through n_sum");
    expect(clone && clone->symbol_class == CallSiteSymbolClass::clone && clone->function == 3 &&
               clone->branch_offset && has_chain(*clone, {10}),
           target + ": the specialization is a clone of n_scale");

    // Merged line rows can erase both the failing site and an inlined
    // call's position. DWARF still proves the inline function identities,
    // including consecutive unknown positions; keep those independently.
    auto merged_lines = lines;
    for (auto& row : merged_lines.rows) row.line = row.discriminator = 0;
    for (auto& subprogram : merged_lines.subprograms) {
        if (subprogram.name != "n_sum" || subprogram.inlined.empty()) continue;
        auto& outer = subprogram.inlined.front();
        outer.call_line = 0;
        DwarfInlined inner;
        inner.ranges = outer.ranges;
        inner.name = "n_pick";
        outer.children.push_back(std::move(inner));
    }
    const auto merged_entries = call_site_table_entries(file, merged_lines, info);
    const auto* merged_sum = entry_named(merged_entries, "n_sum");
    expect(merged_sum && std::any_of(merged_sum->rows.begin(), merged_sum->rows.end(),
        [](const CallSiteTableRow& row) {
            return row.chain == std::vector<std::uint32_t>{0, 0, 0} &&
                row.inline_callees == std::vector<std::uint32_t>{abi::call_site_table::no_function, 0, 2};
        }), target + ": merged nested rows preserve the proven inline identities");
    const auto merged_module = call_site_table_module(merged_entries, info, file.format(), file.machine());
    if (merged_sum) {
        const auto index = static_cast<std::size_t>(merged_sum - merged_entries.data());
        const auto bytes = constant_bytes(merged_module, "@.quidra.calls." + std::to_string(index));
        std::uint32_t row_bytes = 0, chain_bytes = 0;
        if (bytes.size() >= 8) {
            std::memcpy(&row_bytes, bytes.data(), 4);
            std::memcpy(&chain_bytes, bytes.data() + 4, 4);
        }
        const std::vector<std::uint8_t> encoded{3, 0, 0, 0, 1, 0, 3};
        const auto begin = std::size_t{8} + row_bytes;
        const auto end = begin + chain_bytes;
        expect(end <= bytes.size() && begin <= end &&
            std::search(bytes.begin() + std::min(begin, bytes.size()),
                        bytes.begin() + std::min(end, bytes.size()), encoded.begin(), encoded.end()) !=
                bytes.begin() + std::min(end, bytes.size()),
            target + ": serialized merged chain preserves unknown positions and inline identities");
    }
    write_text(root / (target + "-merged-calls.ll"), merged_module);
    expect(compile(root / (target + "-merged-calls.ll"), root / (target + "-merged-calls.o"), target),
           target + ": the merged table module compiles");

    // The table module compiles for the target.
    const auto module = call_site_table_module(entries, info, file.format(), file.machine());
    expect(module.find("@.quidra.sites") != std::string::npos, target + ": the shared table");
    expect(module.find(R"(\01\00\00\00\00\00\01\00p\11\01\00)") != std::string::npos,
           target + ": source indices and columns retain their full width");
    write_text(root / (target + "-calls.ll"), module);
    expect(compile(root / (target + "-calls.ll"), root / (target + "-calls.o"), target),
           target + ": the table module compiles");

    // A tail helper lowered into a cold fragment uses the fragment's CFA,
    // so only its logical owner is refused by tail recovery. An ordinary
    // inline level containing a helper remains usable.
    auto helper_info = info;
    helper_info.sites[2].flags |= call_site_flags::tail_record_helper;
    helper_info.sites[5].flags |= call_site_flags::tail_record_helper;
    const auto helper_module = call_site_table_module(entries, helper_info, file.format(), file.machine());
    const auto bytes = constant_bytes(helper_module, "@.quidra.sites");
    for (std::size_t i = 0; i < helper_info.functions.size(); ++i) {
        abi::call_site_table::SharedFunction function{};
        const auto offset = sizeof(abi::call_site_table::SharedHeader) + i * sizeof function;
        expect(offset + sizeof function <= bytes.size(), target + ": shared function record exists");
        if (offset + sizeof function > bytes.size()) continue;
        std::memcpy(&function, bytes.data() + offset, sizeof function);
        expect(bool(function.flags & call_site_function_flags::tail_unusable) == (i == 0),
               target + ": only the cold helper's owner has an unusable tail path");
    }

    auto conflicting_info = info;
    conflicting_info.sites[4].callee = 0;
    bool conflicting_refused = false;
    try {
        (void)call_site_table_entries(file, lines, conflicting_info);
    } catch (const std::runtime_error& error) {
        conflicting_refused = std::string(error.what()).find("inline identity disagrees") != std::string::npos;
    }
    expect(conflicting_refused, target + ": conflicting known inline identities are refused");

    // A line the module does not have is refused.
    auto short_info = info;
    short_info.sites.resize(3);
    bool refused = false;
    try {
        (void)call_site_table_entries(file, lines, short_info);
    } catch (const std::runtime_error& error) {
        refused = std::string(error.what()).find("call site") != std::string::npos;
    }
    expect(refused, target + ": a row naming an unknown site is refused");
}

std::string host_target() {
#if defined(__APPLE__) && defined(__aarch64__)
    return "arm64-apple-macos11";
#elif defined(__APPLE__)
    return "x86_64-apple-macos11";
#elif defined(_WIN32) && defined(_M_ARM64)
    return "aarch64-pc-windows-msvc";
#elif defined(_WIN32)
    return "x86_64-pc-windows-msvc";
#elif defined(__aarch64__)
    return "aarch64-unknown-linux-gnu";
#else
    return "x86_64-unknown-linux-gnu";
#endif
}

} // namespace

int main() {
    try {
        signed_arm64_addend();
        platform::TemporaryDirectory work("quidra-call-site-table-tests-", "cannot create a directory");
        write_text(work.path() / "fixture.ll", fixture);
        const auto host = host_target();
        check_target(work.path(), host, true);
        // Full debug information gives a user-facing DW_AT_name and a
        // separate linkage identity, including inlined abstract origins.
        std::string debug_fixture = fixture;
        const auto emission = debug_fixture.find("emissionKind: LineTablesOnly");
        debug_fixture.replace(emission, std::string("emissionKind: LineTablesOnly").size(),
                              "emissionKind: FullDebug");
        for (const auto* name : {"n_pick", "n_sum", "n_twice", "n_pick.cold.1",
                                 "OUTLINED_FUNCTION_0", "n_scale.specialized.1"}) {
            const auto spelling = std::string("name: \"") + name + "\"";
            const auto at = debug_fixture.find(spelling);
            debug_fixture.replace(at, spelling.size(), std::string("name: \"user ") + name +
                                  "\", linkageName: \"" + name + "\"");
        }
        write_text(work.path() / "fixture.ll", debug_fixture);
        check_target(work.path(), host, true);
        write_text(work.path() / "fixture.ll", fixture);

        for (const char* target : {"arm64-apple-macos11", "x86_64-apple-macos11", "x86_64-unknown-linux-gnu",
                                   "aarch64-unknown-linux-gnu", "x86_64-pc-windows-msvc",
                                   "aarch64-pc-windows-msvc"}) {
            if (target != host) check_target(work.path(), target, false);
        }
    } catch (const std::exception& error) {
        std::fprintf(stderr, "call-site table test failed: %s\n", error.what());
        return 1;
    }
    if (failures != 0) return 1;
    std::puts("call-site table tests passed");
    return 0;
}
