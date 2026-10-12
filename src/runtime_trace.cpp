// The user call path of a runtime failure; see runtime_trace.hpp.

#include "runtime_trace.hpp"
#include "runtime_tail_path.hpp"

#include "platform/unwind.hpp"
#include "quidra/abi/call_site_table.hpp"
#include "quidra/call_site_info.hpp"

#include <cstring>
#include <limits>

#if defined(__APPLE__)
#include <dlfcn.h>
#include <mach-o/getsect.h>
#include <mach-o/loader.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

namespace table = quidra::abi::call_site_table;

namespace {

// --- The image's table sections.

struct Sections {
    const std::uint8_t* calls{};
    std::size_t calls_size{};
    const std::uint8_t* sites{};
    std::size_t sites_size{};
};

#if defined(__APPLE__)

Sections image_sections() {
    Dl_info info{};
    if (!dladdr(reinterpret_cast<const void*>(&image_sections), &info) || !info.dli_fbase) return {};
    const auto* header = static_cast<const struct mach_header_64*>(info.dli_fbase);
    Sections out;
    unsigned long size = 0;
    out.calls = getsectiondata(header, "__DATA", "__quidra_calls", &size);
    out.calls_size = out.calls ? size : 0;
    size = 0;
    out.sites = getsectiondata(header, "__DATA", "__quidra_sites", &size);
    out.sites_size = out.sites ? size : 0;
    return out;
}

#elif defined(_WIN32)

// The grouped sections .qcalls and .qsites: the table module's parts sort
// between these markers ($a before $m before $z).
#pragma section(".qcalls$a", read)
#pragma section(".qcalls$z", read)
#pragma section(".qsites$a", read)
#pragma section(".qsites$z", read)
__declspec(allocate(".qcalls$a")) const std::uint32_t quidra_calls_begin = 0;
__declspec(allocate(".qcalls$z")) const std::uint32_t quidra_calls_end = 0;
__declspec(allocate(".qsites$a")) const std::uint32_t quidra_sites_begin = 0;
__declspec(allocate(".qsites$z")) const std::uint32_t quidra_sites_end = 0;

Sections image_sections() {
    Sections out;
    const auto* calls_begin = reinterpret_cast<const std::uint8_t*>(&quidra_calls_begin) + 4;
    const auto* calls_end = reinterpret_cast<const std::uint8_t*>(&quidra_calls_end);
    const auto* sites_begin = reinterpret_cast<const std::uint8_t*>(&quidra_sites_begin) + 4;
    const auto* sites_end = reinterpret_cast<const std::uint8_t*>(&quidra_sites_end);
    if (calls_end > calls_begin) {
        out.calls = calls_begin;
        out.calls_size = static_cast<std::size_t>(calls_end - calls_begin);
    }
    if (sites_end > sites_begin) {
        // Padding before the shared table: it starts at its magic.
        while (sites_begin + 4 <= sites_end && std::memcmp(sites_begin, &table::magic, 4) != 0)
            sites_begin += 4;
        out.sites = sites_begin;
        out.sites_size = static_cast<std::size_t>(sites_end - sites_begin);
    }
    return out;
}

#else

extern "C" {
// Defined by the linker when the image has the sections.
extern const std::uint8_t __start_quidra_calls[] __attribute__((weak, visibility("hidden")));
extern const std::uint8_t __stop_quidra_calls[] __attribute__((weak, visibility("hidden")));
extern const std::uint8_t __start_quidra_sites[] __attribute__((weak, visibility("hidden")));
extern const std::uint8_t __stop_quidra_sites[] __attribute__((weak, visibility("hidden")));
}

Sections image_sections() {
    Sections out;
    if (__start_quidra_calls && +__stop_quidra_calls > +__start_quidra_calls) {
        out.calls = __start_quidra_calls;
        out.calls_size = static_cast<std::size_t>(__stop_quidra_calls - __start_quidra_calls);
    }
    if (__start_quidra_sites && +__stop_quidra_sites > +__start_quidra_sites) {
        out.sites = __start_quidra_sites;
        out.sites_size = static_cast<std::size_t>(__stop_quidra_sites - __start_quidra_sites);
    }
    return out;
}

#endif

std::uint32_t load_u32(const std::uint8_t* p) {
    std::uint32_t value;
    std::memcpy(&value, p, 4);
    return value;
}

// ULEB128 within [p, end); false at a truncated value.
bool read_uleb(const std::uint8_t*& p, const std::uint8_t* end, std::uint64_t& value) {
    value = 0;
    unsigned shift = 0;
    while (p < end) {
        const auto byte = *p++;
        if (shift < 64) value |= static_cast<std::uint64_t>(byte & 0x7f) << shift;
        shift += 7;
        if (!(byte & 0x80)) return true;
    }
    return false;
}

// --- The shared table: functions and sites.

class Shared {
public:
    bool open(const Sections& sections) {
        if (!sections.sites || sections.sites_size < sizeof(table::SharedHeader)) return false;
        std::memcpy(&header_, sections.sites, sizeof header_);
        if (header_.magic != table::magic || header_.version != table::version) return false;
        const std::size_t functions = std::size_t{header_.function_count} * sizeof(table::SharedFunction);
        const std::size_t sites = std::size_t{header_.site_count} * sizeof(table::SharedSite);
        if (sections.sites_size < sizeof header_ + functions + sites + header_.string_bytes) return false;
        functions_ = sections.sites + sizeof header_;
        sites_ = functions_ + functions;
        strings_ = reinterpret_cast<const char*>(sites_ + sites);
        return true;
    }

    std::uint32_t function_count() const { return header_.function_count; }
    std::uint32_t site_count() const { return header_.site_count; }

    table::SharedFunction function(std::uint32_t id) const {
        table::SharedFunction out{};
        if (id < header_.function_count)
            std::memcpy(&out, functions_ + std::size_t{id} * sizeof out, sizeof out);
        return out;
    }
    table::SharedSite site(std::uint32_t id) const {
        table::SharedSite out{};
        if (id < header_.site_count) std::memcpy(&out, sites_ + std::size_t{id} * sizeof out, sizeof out);
        return out;
    }
    std::string_view name(std::uint32_t function) const {
        if (function >= header_.function_count) return "?";
        const auto offset = this->function(function).name;
        if (offset >= header_.string_bytes) return "?";
        const char* begin = strings_ + offset;
        return std::string_view(begin, strnlen(begin, header_.string_bytes - offset));
    }
    bool user_function(std::uint32_t function) const {
        return function < header_.function_count &&
               this->function(function).kind == static_cast<std::uint8_t>(quidra::CallSiteFunctionKind::user);
    }
    // The function whose sites include `site`.
    std::uint32_t owner(std::uint32_t site) const {
        for (std::uint32_t id = 0; id < header_.function_count; ++id) {
            const auto f = function(id);
            if (site >= f.first_site && site < f.first_site + f.site_count) return id;
        }
        return table::no_function;
    }

private:
    table::SharedHeader header_{};
    const std::uint8_t* functions_{};
    const std::uint8_t* sites_{};
    const char* strings_{};
};

// --- One frame's entry and row.

constexpr std::size_t max_chain = 64;

struct Frame {
    std::uint32_t function{table::no_function};
    std::uint32_t symbol_class{table::class_unknown};
    std::uint32_t chain[max_chain]{};
    std::uint32_t inline_callees[max_chain]{};
    std::size_t chain_size{};
    bool truncated{};
};

// The start of a local function from the branch to it at `branch`.
std::uintptr_t branch_target(std::uintptr_t branch) {
#if defined(__aarch64__) || defined(_M_ARM64)
    std::uint32_t word;
    std::memcpy(&word, reinterpret_cast<const void*>(branch), 4);
    if ((word & 0x7c000000u) != 0x14000000u) return 0;
    std::int64_t displacement = static_cast<std::int64_t>(word & 0x03ffffffu);
    if (displacement & 0x02000000) displacement -= 0x04000000;
    return branch + static_cast<std::uintptr_t>(displacement * 4);
#elif defined(__x86_64__) || defined(_M_X64)
    std::uint8_t opcode;
    std::memcpy(&opcode, reinterpret_cast<const void*>(branch), 1);
    if (opcode != 0xe8 && opcode != 0xe9) return 0;
    std::int32_t displacement;
    std::memcpy(&displacement, reinterpret_cast<const void*>(branch + 1), 4);
    return branch + 5 + static_cast<std::uintptr_t>(static_cast<std::intptr_t>(displacement));
#else
    (void)branch;
    return 0;
#endif
}

bool lookup(const Sections& sections, std::uintptr_t pc, Frame& out, std::uintptr_t* function_start = nullptr) {
    const auto* p = sections.calls;
    const auto* end = p + sections.calls_size;
    while (p && p + 16 <= end) {
        const auto size = load_u32(p);
        if (size == 0) {
            p += 4;  // padding between entries
            continue;
        }
        if (size < 16 || size % 4 != 0 || size > static_cast<std::size_t>(end - p)) return false;
        std::int32_t reference;
        std::memcpy(&reference, p + 4, 4);
        const auto code_size = load_u32(p + 8);
        const auto identity = load_u32(p + 12);
        const auto* q = p + 16;
        std::uintptr_t target = reinterpret_cast<std::uintptr_t>(p + 4) +
                                static_cast<std::uintptr_t>(static_cast<std::intptr_t>(reference));
        if (identity & table::identity_absolute_bit) {
            if (size < 24) return false;
            std::uint64_t address;
            std::memcpy(&address, q, 8);
            target = static_cast<std::uintptr_t>(address);
            q += 8;
        }
        std::uintptr_t start = target;
        if (identity & table::identity_branch_bit) {
            if (q + 4 > p + size) return false;
            start = branch_target(target + load_u32(q));
            q += 4;
        }
        if (start != 0 && pc >= start && pc - start < code_size) {
            if (function_start) *function_start = start;
            if (q + 8 > p + size) return false;
            const auto row_bytes = load_u32(q);
            const auto chain_bytes = load_u32(q + 4);
            q += 8;
            const auto* rows = q;
            const auto* rows_end = rows + row_bytes;
            const auto* chains = rows_end;
            const auto* chains_end = chains + chain_bytes;
            if (chains_end > p + size) return false;
            const auto offset = pc - start;
            std::uint64_t at = 0;
            std::uint64_t chain = ~std::uint64_t{0};
            while (rows < rows_end) {
                std::uint64_t delta = 0, which = 0;
                if (!read_uleb(rows, rows_end, delta) || !read_uleb(rows, rows_end, which)) return false;
                at += delta;
                if (at > offset) break;
                chain = which;
            }
            out = Frame{};
            out.function = identity & table::identity_function_mask;
            out.symbol_class = (identity >> table::identity_class_shift) & table::identity_class_mask;
            if (chain == ~std::uint64_t{0} || chain >= chain_bytes) {
                // Before the first row: no call of the function's.
                out.chain[0] = 0;
                out.inline_callees[0] = table::no_function;
                out.chain_size = 1;
                return true;
            }
            const auto* c = chains + chain;
            std::uint64_t count = 0;
            if (!read_uleb(c, chains_end, count) || count == 0) return false;
            for (std::uint64_t i = 0; i < count; ++i) {
                std::uint64_t site = 0, callee = 0;
                if (!read_uleb(c, chains_end, site) || !read_uleb(c, chains_end, callee) ||
                    site > std::numeric_limits<std::uint32_t>::max() || callee > table::no_function) return false;
                if (out.chain_size < max_chain) {
                    out.chain[out.chain_size] = static_cast<std::uint32_t>(site);
                    out.inline_callees[out.chain_size++] = callee
                        ? static_cast<std::uint32_t>(callee - 1) : table::no_function;
                }
                else out.truncated = true;
            }
            return true;
        }
        p += size;
    }
    return false;
}

bool consistent_chain(const Frame& frame, const Shared& shared) {
    for (std::size_t i = 0; i < frame.chain_size; ++i) {
        const auto site = frame.chain[i];
        const auto callee = frame.inline_callees[i];
        if (site >= shared.site_count()) return false;
        if (!i) {
            if (callee != table::no_function) return false;
            continue;
        }
        if (callee == table::no_function) continue;
        if (callee >= shared.function_count()) return false;
        const auto position = shared.site(site);
        if (site && position.callee_kind == static_cast<std::uint8_t>(quidra::CallSiteCallee::function) &&
            position.callee != callee) return false;
    }
    return true;
}

bool starts_at(const Sections& sections, std::uintptr_t address) {
    Frame frame;
    std::uintptr_t start = 0;
    return lookup(sections, address, frame, &start) && start == address;
}

// --- The walk.

constexpr std::size_t max_items = 16384;
constexpr std::size_t max_candidates = 1024;

thread_local quidra::runtime::PathItem items[max_items];
thread_local quidra::runtime::PathCandidate candidates[max_candidates];

// Collect before reporting so mixed physical and collapsed self calls can
// derive each inner frame's starting depth from its physical caller.
constexpr std::size_t max_frames = 8192;
constexpr std::size_t max_tail_hops = 1024;
struct CollectedFrame {
    Frame frame;
    quidra::platform::StackFrame raw;
    std::uint32_t entered{table::no_function};
    std::uint32_t start_depth{1};
    std::uint32_t depth{1};
    bool uncertain{};
};
thread_local CollectedFrame frames[max_frames];
thread_local quidra::runtime_tail::Hop tail_hops[max_tail_hops];
thread_local const void* node_trace_body{};


class Walker {
public:
    Walker(const Sections& sections, const Shared& shared) : sections_(sections), shared_(shared) {
        Frame boundary;
        if(node_trace_body && lookup(sections,reinterpret_cast<std::uintptr_t>(node_trace_body),boundary) &&
           boundary.symbol_class==table::class_function && starts_at(sections,reinterpret_cast<std::uintptr_t>(node_trace_body)))
            node_function_=boundary.function;
    }

    static bool visit(const quidra::platform::StackFrame& frame, void* context) {
        return static_cast<Walker*>(context)->step(frame);
    }

    void finish(quidra::platform::StackWalkEnd end) {
        if (!any_frame_) return;
        prepare_depths();
        for (std::size_t i = 0; i < frame_count_; ++i) report_frame(i);

        const bool reached_top =
            stopped_ || (last_outer_ < shared_.function_count() &&
                         shared_.function(last_outer_).kind ==
                             static_cast<std::uint8_t>(quidra::CallSiteFunctionKind::entry));
        if (truncated_frames_ || !reached_top || end != quidra::platform::StackWalkEnd::complete) marker();
    }

    quidra::runtime::CallPath path() const {
        return quidra::runtime::CallPath{items, count_, candidates, complete_};
    }

private:
    bool step(const quidra::platform::StackFrame& raw) {
        if (stopped_) return false;
        const auto pc = raw.ip_before_instruction ? raw.ip : raw.ip - 1;
        Frame frame;
        if (!lookup(sections_, pc, frame)) return true;
        if (!consistent_chain(frame, shared_)) frame.symbol_class = table::class_unknown;
        if (!any_frame_) {
            any_frame_ = true;
            // A failure of the prologue's depth guard: the report names the
            // call, so the failing frame is the caller.
            const auto c0 = frame.chain[0];
            if (c0 != 0 && (shared_.site(c0).flags & quidra::call_site_flags::prologue)) {
                return true;
            }
        }
        // A fragment's parent, suspended at its call into the fragment, adds
        // nothing: the fragment's rows stood for it.
        if (fragment_of_ != table::no_function && frame.function == fragment_of_ &&
            frame.symbol_class != table::class_fragment) {
            fragment_of_ = table::no_function;
            return true;
        }
        fragment_of_ = table::no_function;
        if (frame_count_ == max_frames) {
            truncated_frames_ = true;
            stopped_ = true;
            return false;
        }
        frames[frame_count_++] = CollectedFrame{frame, raw};
        if (frame.symbol_class == table::class_fragment) fragment_of_ = frame.function;
        if(node_function_!=table::no_function && frame.function==node_function_){
            stopped_=true;return false;
        }
        if (frame.function < shared_.function_count() &&
            (shared_.function(frame.function).kind == static_cast<std::uint8_t>(quidra::CallSiteFunctionKind::entry) ||
             (shared_.function(frame.function).flags & quidra::call_site_function_flags::export_entry))) {
            stopped_ = true;
            return false;
        }
        return true;
    }

    static std::uint32_t innermost(const Frame& frame, const Shared& shared) {
        if (frame.chain_size < 2) return frame.function;
        if (frame.inline_callees[1] < shared.function_count()) return frame.inline_callees[1];
        const auto site = shared.site(frame.chain[1]);
        if (frame.chain[1] && site.callee_kind == static_cast<std::uint8_t>(quidra::CallSiteCallee::function))
            return site.callee;
        return frame.chain[0] ? shared.owner(frame.chain[0]) : table::no_function;
    }

    quidra::runtime_tail::Graph graph() const {
        return {&shared_, shared_.function_count(), shared_.site_count(),
            [](const void* context, std::uint32_t id) { return static_cast<const Shared*>(context)->function(id); },
            [](const void* context, std::uint32_t id) { return static_cast<const Shared*>(context)->site(id); },
            [](const void* context, std::uint32_t id) { return static_cast<const Shared*>(context)->owner(id); }};
    }

    quidra::runtime_tail::CallEntry direct_target(const CollectedFrame& caller) const {
        if (caller.raw.ip_before_instruction) return {};
#if defined(__aarch64__) || defined(_M_ARM64)
        const auto address = branch_target(caller.raw.ip - 4);
#elif defined(__x86_64__) || defined(_M_X64)
        const auto address = branch_target(caller.raw.ip - 5);
#else
        const std::uintptr_t address = 0;
#endif
        Frame target;
        if (!address || !lookup(sections_, address, target) || target.symbol_class == table::class_unknown ||
            !consistent_chain(target, shared_))
            return {};
        return quidra::runtime_tail::logical_call_entry(
            graph(), innermost(caller.frame, shared_), target.function);
    }

    std::uint32_t kept_site(CollectedFrame& current) const {
        const auto site = current.frame.chain[0];
        if (site) return site;
        const auto resolved = direct_target(current);
        if (resolved.ambiguous) { current.uncertain = true; return 0; }
        const auto target = resolved.function;
        const auto scope = innermost(current.frame, shared_);
        if (target == table::no_function || scope >= shared_.function_count()) return 0;
        const auto function = shared_.function(scope);
        bool any_recorded = false;
        bool any_unrecorded = false;
        for (auto id = function.first_site; id < function.first_site + function.site_count; ++id) {
            const auto candidate = shared_.site(id);
            if (candidate.callee_kind != static_cast<std::uint8_t>(quidra::CallSiteCallee::function) ||
                candidate.callee != target) continue;
            if (candidate.flags & quidra::call_site_flags::recorded_tail) any_recorded = true;
            else any_unrecorded = true;
        }
        if (!any_recorded) return 0;
        // A merged call can use the record only when every candidate writes
        // one. Otherwise a stale record from an earlier kept call would
        // falsely identify this call, so use the incomplete marker.
        if (any_unrecorded) { current.uncertain = true; return 0; }
        const auto log = quidra::runtime_tail::snapshot();
        for (std::size_t i = log.entries.size(); i > 0; --i) {
            const auto entry = log.entries[i - 1];
            if (entry.cfa != current.raw.cfa) continue;
            const auto candidate = shared_.site(entry.site);
            if (shared_.owner(entry.site) == scope && candidate.callee == target &&
                (candidate.flags & quidra::call_site_flags::recorded_tail)) return entry.site;
            break;
        }
        current.uncertain = true;
        return 0;
    }

    quidra::runtime_tail::Recovery recover_frame(std::size_t index) {
        auto& current = frames[index];
        const auto& frame = current.frame;
        std::uint32_t inlined[max_chain];
        quidra::runtime_tail::InlineEdge merged_inline[max_chain];
        std::size_t count = 0;
        std::size_t merged_count = 0;
        for (std::size_t i = frame.chain_size; i > 1; --i) inlined[count++] = frame.chain[i - 1];
        for(std::size_t i=1;i<frame.chain_size;++i) {
            if(frame.chain[i])continue;
            const auto callee=frame.inline_callees[i]<shared_.function_count()
                ?frame.inline_callees[i]
                :frame.chain[i-1]?shared_.owner(frame.chain[i-1]):table::no_function;
            std::uint32_t owner=frame.truncated?table::no_function:frame.function;
            if(i+1<frame.chain_size) {
                const auto outer=shared_.site(frame.chain[i+1]);
                owner=frame.inline_callees[i+1]<shared_.function_count()?frame.inline_callees[i+1]
                    :frame.chain[i+1] && outer.callee_kind==static_cast<std::uint8_t>(quidra::CallSiteCallee::function)
                    ?outer.callee:table::no_function;
            }
            // Unknown inline identities cannot establish an edge.
            // Self activations also need their dynamic record.
            if(owner>=shared_.function_count() || callee>=shared_.function_count() || owner==callee)
                current.uncertain=true;
            else merged_inline[merged_count++]={owner,callee};
        }
        if (frame.truncated) current.uncertain = true;
        const auto kept = kept_site(current);
        return quidra::runtime_tail::recover(graph(), quidra::runtime_tail::snapshot(), current.raw.cfa,
            current.entered, innermost(frame, shared_), current.start_depth, {inlined, count}, kept,
            tail_hops,{merged_inline,merged_count});
    }

    void prepare_depths() {
        for (std::size_t i = frame_count_; i > 0; --i) {
            auto& current = frames[i - 1];
            current.entered = current.frame.function;
            if (i < frame_count_) {
                const auto& caller = frames[i];
                const auto site = shared_.site(caller.frame.chain[0]);
                if (caller.frame.chain[0] &&
                    site.callee_kind == static_cast<std::uint8_t>(quidra::CallSiteCallee::function)) {
                    current.entered = site.callee;
                } else if (!caller.frame.chain[0]) {
                    const auto target = direct_target(caller);
                    if (target.ambiguous) {
                        // The physical body does not identify which source
                        // callee was entered. Do not let the next frame use
                        // it to select a falsely precise merged-call site.
                        current.entered = table::no_function;
                        current.uncertain = true;
                    } else if (target.function != table::no_function) current.entered = target.function;
                    else if (!(shared_.function(current.frame.function).flags &
                               quidra::call_site_function_flags::address_taken)) current.uncertain = true;
                }
                if (current.entered == innermost(caller.frame, shared_)) {
                    if (caller.depth == std::numeric_limits<std::uint32_t>::max()) current.uncertain = true;
                    else current.start_depth = caller.depth + 1;
                }
                if (caller.frame.symbol_class == table::class_unknown) current.uncertain = true;
            }
            const auto recovery = recover_frame(i - 1);
            current.depth = recovery.depth;
            if (!recovery.complete) current.uncertain = true;
        }
    }

    void report_frame(std::size_t index) {
        auto& current = frames[index];
        const auto& frame = current.frame;
        const bool failing = index == 0;
        if (frame.truncated) marker();
        if (frame.symbol_class == table::class_unknown) {
            // An outlined function the table cannot attribute.
            marker();
            prev_outer_ = table::no_function;
            pending_ = table::no_function;
            return;
        }
        // The logical functions of the frame's levels, innermost first; the
        // outermost is the frame's own.
        const auto n = frame.chain_size - 1;
        std::uint32_t levels[max_chain];
        levels[n] = frame.truncated ? table::no_function : frame.function;
        for (std::size_t i = 0; i < n; ++i) {
            const auto inlined_at = shared_.site(frame.chain[i + 1]);
            if (frame.inline_callees[i + 1] < shared_.function_count())
                levels[i] = frame.inline_callees[i + 1];
            else if (frame.chain[i + 1] != 0 &&
                inlined_at.callee_kind == static_cast<std::uint8_t>(quidra::CallSiteCallee::function))
                levels[i] = inlined_at.callee;
            else if (frame.chain[i] != 0)
                levels[i] = shared_.owner(frame.chain[i]);
            else
                levels[i] = table::no_function;
        }
        if (!failing) link(frame.chain[0], levels[0]);
        const auto recovered = recover_frame(index);
        if (recovered.complete && !current.uncertain) {
            for (std::size_t i = recovered.count; i > 0; --i) {
                const auto& hop = tail_hops[i - 1];
                if(hop.merged)merged_pair(hop.callee,hop.owner);
                else pair(hop.callee, hop.site, hop.inlined ? quidra::runtime::PathVia::inline_call
                                                         : quidra::runtime::PathVia::call, hop.repeat);
            }
        } else {
            // The row still proves its inline levels even when an outer
            // tail prefix is unavailable. Never invent that missing prefix.
            for (std::size_t i = 0; i < n; ++i) {
                if (!frame.chain[i + 1] && levels[i] < shared_.function_count() &&
                    levels[i + 1] < shared_.function_count() && levels[i] != levels[i + 1])
                    merged_pair(levels[i], levels[i + 1]);
                else pair(levels[i], frame.chain[i + 1], quidra::runtime::PathVia::inline_call);
            }
            marker();
        }
        prev_outer_ = current.entered;
        last_outer_ = frame.function;
        return;
    }

    void merged_pair(std::uint32_t callee,std::uint32_t owner) {
        if(owner>=shared_.function_count()){marker();pending_=table::no_function;return;}
        const auto function=shared_.function(owner);
        const auto first_candidate=static_cast<std::uint32_t>(candidate_count_);
        std::uint32_t first=0,found=0;
        bool user=false;
        for(auto id=function.first_site;id<function.first_site+function.site_count;++id) {
            const auto site=shared_.site(id);
            if(site.callee_kind!=static_cast<std::uint8_t>(quidra::CallSiteCallee::function) || site.callee!=callee)continue;
            const bool candidate_user=site.flags & quidra::call_site_flags::user;
            if(found && candidate_user!=user){candidate_count_=first_candidate;marker();pending_=table::no_function;return;}
            if(!found){first=id;user=candidate_user;}
            ++found;
            if(candidate_count_==max_candidates){candidate_count_=first_candidate;marker();pending_=table::no_function;return;}
            candidates[candidate_count_++]={encoded_line(site),site.column};
        }
        if(!found){marker();pending_=table::no_function;return;}
        if(found==1){candidate_count_=first_candidate;pair(callee,first,quidra::runtime::PathVia::inline_call);return;}
        if(shared_.user_function(callee))pending_=callee;
        if(user && pending_!=table::no_function) {
            quidra::runtime::PathItem item;
            item.kind=quidra::runtime::PathItemKind::merged;
            item.via=quidra::runtime::PathVia::inline_call;
            item.function=shared_.name(pending_);
            item.first_candidate=first_candidate;
            item.candidate_count=static_cast<std::uint32_t>(candidate_count_-first_candidate);
            add(item);pending_=table::no_function;
        }else candidate_count_=first_candidate;
    }

    // The frame's call into the previous frame's function.
    void link(std::uint32_t site, std::uint32_t scope) {
        const auto entered = prev_outer_;
        if (entered == table::no_function) {
            pending_ = table::no_function;
            return;
        }
        if (site == 0) {
            // A call LLVM merged: the calls of the entered function in the
            // row's scope.
            std::uint32_t found = 0;
            std::uint32_t first = 0;
            const auto first_candidate = static_cast<std::uint32_t>(candidate_count_);
            if (scope < shared_.function_count()) {
                const auto f = shared_.function(scope);
                for (std::uint32_t id = f.first_site; id < f.first_site + f.site_count; ++id) {
                    const auto s = shared_.site(id);
                    if (s.callee_kind != static_cast<std::uint8_t>(quidra::CallSiteCallee::function) ||
                        s.callee != entered)
                        continue;
                    if (found == 0) first = id;
                    ++found;
                    if (candidate_count_ < max_candidates)
                        candidates[candidate_count_++] =
                            quidra::runtime::PathCandidate{encoded_line(s), s.column};
                }
            }
            if (found == 0) {
                candidate_count_ = first_candidate;
                marker();
                pending_ = table::no_function;
                return;
            }
            if (found == 1) {
                candidate_count_ = first_candidate;
                pair(entered, first, quidra::runtime::PathVia::call);
                return;
            }
            if (shared_.user_function(entered)) pending_ = entered;
            const bool user = shared_.site(first).flags & quidra::call_site_flags::user;
            if (user && pending_ != table::no_function) {
                quidra::runtime::PathItem item;
                item.kind = quidra::runtime::PathItemKind::merged;
                item.function = shared_.name(pending_);
                item.first_candidate = first_candidate;
                item.candidate_count = static_cast<std::uint32_t>(candidate_count_ - first_candidate);
                add(item);
                pending_ = table::no_function;
            } else {
                candidate_count_ = first_candidate;
            }
            return;
        }
        const auto s = shared_.site(site);
        if (s.callee_kind == static_cast<std::uint8_t>(quidra::CallSiteCallee::function) && s.callee != entered) {
            // The call named another function: frames between them are
            // missing (tail calls), which the path cannot prove.
            marker();
            pending_ = table::no_function;
            pair(s.callee, site, quidra::runtime::PathVia::call);
            return;
        }
        pair(entered, site, quidra::runtime::PathVia::call);
    }

    // A function left at a call site: a user function waits for the next
    // user site, which prints its line.
    void pair(std::uint32_t function, std::uint32_t site, quidra::runtime::PathVia via,
              std::uint32_t repeat = 1) {
        if (shared_.user_function(function)) pending_ = function;
        if (site == 0 || pending_ == table::no_function) return;
        const auto s = shared_.site(site);
        if (!(s.flags & quidra::call_site_flags::user)) return;
        quidra::runtime::PathItem item;
        item.kind = quidra::runtime::PathItemKind::call;
        item.via = via;
        item.repeat = repeat;
        item.function = shared_.name(pending_);
        item.line = encoded_line(s);
        item.column = s.column;
        add(item);
        pending_ = table::no_function;
    }

    static unsigned long long encoded_line(const table::SharedSite& site) {
        return (static_cast<unsigned long long>(site.file) << 32) | site.line;
    }

    void marker() {
        complete_ = false;
        quidra::runtime::PathItem item;
        item.kind = quidra::runtime::PathItemKind::marker;
        add(item);
    }

    void add(const quidra::runtime::PathItem& item) {
        if (count_ != 0) {
            auto& last = items[count_ - 1];
            const bool same = last.kind == item.kind && last.via == item.via && last.function == item.function &&
                              last.line == item.line && last.column == item.column &&
                              last.candidate_count == item.candidate_count &&
                              (item.kind != quidra::runtime::PathItemKind::merged ||
                               std::memcmp(&candidates[last.first_candidate],
                                           &candidates[item.first_candidate],
                                           sizeof(quidra::runtime::PathCandidate) * item.candidate_count) == 0);
            if (same) {
                last.repeat += item.repeat;
                if (item.kind == quidra::runtime::PathItemKind::merged)
                    candidate_count_ = item.first_candidate;
                return;
            }
        }
        if (count_ == max_items) {
            complete_ = false;
            stopped_ = true;
            return;
        }
        items[count_++] = item;
    }

    const Sections& sections_;
    const Shared& shared_;
    std::size_t frame_count_{};
    bool truncated_frames_{};
    std::size_t count_{};
    std::size_t candidate_count_{};
    bool complete_{true};
    bool any_frame_{};
    bool stopped_{};
    std::uint32_t node_function_{table::no_function};
    std::uint32_t prev_outer_{table::no_function};
    std::uint32_t last_outer_{table::no_function};
    std::uint32_t pending_{table::no_function};
    std::uint32_t fragment_of_{table::no_function};
};

} // namespace

namespace quidra::runtime {

const void* set_node_trace_body(const void* address) noexcept {
    const auto previous=node_trace_body;node_trace_body=address;return previous;
}



std::string_view function_at(const void* address) {
    const auto sections = image_sections();
    Shared shared;
    if (!address || !sections.calls || !shared.open(sections)) return {};
    const auto target = reinterpret_cast<std::uintptr_t>(address);
    Frame frame;
    if (!lookup(sections, target, frame) || frame.symbol_class != table::class_function) return {};
    // Only the function's own start: an `func` value is a function's address.
    if (!starts_at(sections, target)) return {};
    return shared.name(frame.function);
}

CallPath walk_call_path() {
    const auto sections = image_sections();
    Shared shared;
    if (!sections.calls || !shared.open(sections)) return CallPath{items, 0, candidates, true};
    Walker walker(sections, shared);
    const auto end = platform::walk_stack(&Walker::visit, &walker);
    walker.finish(end);
    return walker.path();
}

} // namespace quidra::runtime
