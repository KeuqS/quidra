#include "runtime_tail_path.hpp"
#include "quidra/call_site_info.hpp"

#include <algorithm>
#include <array>
#include <limits>

namespace quidra::runtime_tail {
namespace {
constexpr std::size_t max_static_hops = 128;
constexpr std::size_t max_search_steps = 100000;

struct ForwardingPath {
    std::uint32_t first_site{};
    bool reaches{};
    bool valid{};
};

// Only the compiler's declared wrappers authorize this relation. An
// ordinary synthesized call, or an arbitrary user call, proves no edge.
// Validate the whole chain, including beyond `target`, so a cyclic or
// malformed wrapper cannot accidentally establish a route to its prefix.
ForwardingPath forwarding_path(const Graph& graph, std::uint32_t from,
                               std::uint32_t target) noexcept {
    ForwardingPath result;
    std::array<std::uint32_t, max_static_hops> active{};
    for (std::size_t depth = 0; depth < active.size(); ++depth) {
        if (from >= graph.function_count) return result;
        if (from == target) result.reaches = true;
        const auto function = graph.function(graph.context, from);
        if (!(function.flags & call_site_function_flags::transparent_forwarder)) {
            result.valid = true;
            return result;
        }
        for (std::size_t i = 0; i < depth; ++i)
            if (active[i] == from) return result;
        active[depth] = from;
        const auto end = std::uint64_t{function.first_site} + function.site_count;
        if (end > graph.site_count) return result;
        std::uint32_t forward = 0;
        for (auto id = function.first_site; id < end; ++id) {
            const auto site = graph.site(graph.context, id);
            if (site.callee_kind != static_cast<std::uint8_t>(CallSiteCallee::function) ||
                !(site.flags & call_site_flags::synthesized)) continue;
            if (!id || forward || (site.flags & call_site_flags::user)) return result;
            forward = id;
        }
        if (!forward) return result;
        if (!result.first_site) result.first_site = forward;
        from = graph.site(graph.context, forward).callee;
    }
    return result;
}

// This search only rejects a source-entry guess. An ordinary function may
// have been inlined before LLVM erased a merged call's location, so its
// route to the physical target competes with a declared forwarder even
// though that route cannot be recovered without inline or tail evidence.
class PossibleCallPath {
public:
    PossibleCallPath(const Graph& graph, std::uint32_t target) : graph_(graph), target_(target) {}

    bool through(const table::SharedSite& site) noexcept { return through(site, 0); }

private:
    bool through(const table::SharedSite& site, std::size_t depth) noexcept {
        if (++steps_ > max_search_steps) return true;
        switch (static_cast<CallSiteCallee>(site.callee_kind)) {
            case CallSiteCallee::function: return visit(site.callee, depth);
            case CallSiteCallee::indirect: case CallSiteCallee::unknown: return true;
            case CallSiteCallee::extern_function:
                return site.flags & call_site_flags::extern_callback;
            case CallSiteCallee::runtime: return false;
        }
        return true;
    }

    bool visit(std::uint32_t function, std::size_t depth) noexcept {
        if (++steps_ > max_search_steps || depth == active_.size() || function >= graph_.function_count)
            return true;
        if (function == target_) return true;
        for (std::size_t i = 0; i < depth; ++i)
            if (active_[i] == function) return false;
        active_[depth] = function;
        const auto source = graph_.function(graph_.context, function);
        const auto end = std::uint64_t{source.first_site} + source.site_count;
        if (end > graph_.site_count) return true;
        for (auto id = source.first_site; id < end; ++id)
            if (through(graph_.site(graph_.context, id), depth + 1)) return true;
        return false;
    }

    const Graph& graph_;
    std::uint32_t target_{};
    std::array<std::uint32_t, max_static_hops> active_{};
    std::size_t steps_{};
};

struct Route {
    std::array<Hop, max_static_hops> hops{};
    std::size_t count{};
    unsigned matches{};
};

// A bounded search for a unique route through unrecorded tail edges,
// declared transparent forwarders and the inline edges the row proves.
// Other recorded edges require a log entry.
class Search {
public:
    Search(const Graph& graph, std::span<const std::uint32_t> inlined, std::uint32_t inline_target,
           std::span<const InlineEdge> merged_inline)
        : graph_(graph), inlined_(inlined), inline_target_(inline_target), merged_inline_(merged_inline) {}

    Route route(std::uint32_t from, std::uint32_t to) noexcept {
        result_ = {};
        steps_ = 0;
        visit(from, to, 0);
        return result_;
    }

private:
    void visit(std::uint32_t from, std::uint32_t to, std::size_t depth) noexcept {
        if (result_.matches > 1) return;
        if (++steps_ > max_search_steps || depth == max_static_hops || from >= graph_.function_count) {
            result_.matches = 2;
            return;
        }
        if (from == to) {
            if (++result_.matches == 1) {
                result_.count = depth;
                std::copy_n(path_.begin(), depth, result_.hops.begin());
            }
            return;
        }
        for (std::size_t i = 0; i < depth; ++i) if (active_[i] == from) return;
        active_[depth] = from;
        const auto function = graph_.function(graph_.context, from);
        if (function.flags & call_site_function_flags::tail_unusable) { result_.matches = 2; return; }
        const auto end = std::uint64_t{function.first_site} + function.site_count;
        if (end > graph_.site_count) { result_.matches = 2; return; }
        const auto forwarding = forwarding_path(graph_, from, table::no_function);
        if (!forwarding.valid) { result_.matches = 2; return; }
        for (std::uint32_t id = function.first_site; id < end; ++id) {
            const auto site = graph_.site(graph_.context, id);
            const auto inline_at = std::find(inlined_.begin(), inlined_.end(), id);
            bool inlined = inline_at != inlined_.end();
            std::uint32_t callee = site.callee;
            if (site.callee_kind != static_cast<std::uint8_t>(CallSiteCallee::function)) {
                if (!inlined) continue;
                const auto next = inline_at + 1;
                callee = next == inlined_.end() ? inline_target_ : graph_.owner(graph_.context, *next);
            }
            const bool merged = !inlined && std::any_of(merged_inline_.begin(),merged_inline_.end(),
                [&](const InlineEdge& edge){return edge.owner==from && edge.callee==callee;});
            if(merged) {
                // All sites here have the same proven logical edge. Their
                // positions form one merged hop, not different routes.
                bool earlier=false;
                for(auto prior=function.first_site;prior<id;++prior) {
                    const auto candidate=graph_.site(graph_.context,prior);
                    if(candidate.callee_kind==static_cast<std::uint8_t>(CallSiteCallee::function) &&
                       candidate.callee==callee){earlier=true;break;}
                }
                if(earlier)continue;
                inlined=true;
            }
            if (!inlined && (site.flags & call_site_flags::recorded_tail)) continue;
            if (!inlined && !(site.flags & call_site_flags::tail) && id != forwarding.first_site) continue;
            path_[depth] = {id, callee, 1, inlined, from, merged};
            visit(callee, to, depth + 1);
        }
    }
    const Graph& graph_;
    std::span<const std::uint32_t> inlined_;
    std::uint32_t inline_target_;
    std::span<const InlineEdge> merged_inline_;
    Route result_;
    std::array<Hop, max_static_hops> path_{};
    std::array<std::uint32_t, max_static_hops> active_{};
    std::size_t steps_{};
};

bool self_function(const Graph& graph, std::uint32_t function) noexcept {
    return function < graph.function_count &&
           (graph.function(graph.context, function).flags & call_site_function_flags::self_tail);
}
} // namespace

CallEntry logical_call_entry(const Graph& graph, std::uint32_t owner,
                             std::uint32_t target) noexcept {
    if (target >= graph.function_count) return {};
    if (owner >= graph.function_count) return {target, false};
    const auto function = graph.function(graph.context, owner);
    const auto end = std::uint64_t{function.first_site} + function.site_count;
    if (end > graph.site_count) return {table::no_function, true};
    std::uint32_t entry = table::no_function;
    for (auto id = function.first_site; id < end; ++id) {
        const auto site = graph.site(graph.context, id);
        if (site.callee_kind != static_cast<std::uint8_t>(CallSiteCallee::function)) continue;
        const auto forwarding = forwarding_path(graph, site.callee, target);
        if (!forwarding.valid) return {table::no_function, true};
        if (!forwarding.reaches) continue;
        if (entry != table::no_function && entry != site.callee)
            return {table::no_function, true};
        entry = site.callee;
    }
    if (entry != table::no_function) {
        PossibleCallPath alternatives(graph, target);
        for (auto id = function.first_site; id < end; ++id) {
            const auto site = graph.site(graph.context, id);
            if (site.callee_kind == static_cast<std::uint8_t>(CallSiteCallee::function) &&
                site.callee == entry) continue;
            if (alternatives.through(site)) return {table::no_function, true};
        }
    }
    return {entry == table::no_function ? target : entry, false};
}

Recovery recover(const Graph& graph, Snapshot log, std::uintptr_t cfa,
                 std::uint32_t start, std::uint32_t target, std::uint32_t start_depth,
                 std::span<const std::uint32_t> inline_sites, std::uint32_t kept_site,
                 std::span<Hop> output, std::span<const InlineEdge> merged_inline) noexcept {
    if (start >= graph.function_count || target >= graph.function_count || start_depth == 0) return {};
    // Without a canonical frame address, a row can still prove an acyclic
    // inline route. It cannot establish how many self activations ran.
    const auto needs_cfa = [&](std::uint32_t function) {
        if (function >= graph.function_count) return true;
        return (graph.function(graph.context, function).flags & call_site_function_flags::self_tail) != 0;
    };
    if (!cfa && (needs_cfa(start) || needs_cfa(target))) return {};
    if ((graph.function(graph.context, start).flags | graph.function(graph.context, target).flags) &
        call_site_function_flags::tail_unusable) return {};
    std::size_t begin = 0;
    while (begin < log.entries.size() && log.entries[begin].cfa > cfa) ++begin;
    std::size_t end = begin;
    while (end < log.entries.size() && log.entries[end].cfa == cfa) ++end;
    if (kept_site && kept_site < graph.site_count &&
        (graph.site(graph.context, kept_site).flags & call_site_flags::recorded_tail) &&
        (begin == end || log.entries[end - 1].site != kept_site)) return {};
    Search search(graph, inline_sites, target, merged_inline);
    // The longest consistent suffix is live. R1/R2/R3 discard ended self
    // runs; stale non-self entries cannot extend the unique active route.
    for (std::size_t first = begin; first <= end; ++first) {
        std::uint32_t position = start;
        std::uint32_t depth = start_depth;
        std::size_t count = 0;
        bool valid = true;
        const auto append = [&](const Hop& hop) {
            if (count == output.size()) return false;
            output[count++] = hop;
            return true;
        };
        const auto follow = [&](std::uint32_t destination) {
            const auto route = search.route(position, destination);
            if (route.matches != 1) return false;
            for (std::size_t i = 0; i < route.count; ++i) {
                const auto& hop = route.hops[i];
                if (!cfa && needs_cfa(hop.callee)) return false;
                if (!append(hop)) return false;
                // A direct self call within a proved inline level increments
                // the depth; every other entry goes through the public ABI.
                depth = hop.callee == position ? depth + 1 : 1;
                position = hop.callee;
            }
            return true;
        };
        for (std::size_t i = first; valid && i < end; ++i) {
            auto entry = log.entries[i];
            if (entry.site == 0 || entry.site >= graph.site_count) { valid = false; break; }
            const auto site = graph.site(graph.context, entry.site);
            if (!(site.flags & call_site_flags::recorded_tail)) { valid = false; break; }
            const auto owner = graph.owner(graph.context, entry.site);
            if (owner >= graph.function_count ||
                (graph.function(graph.context, owner).flags & call_site_function_flags::tail_unusable)) {
                valid = false; break;
            }
            if (!follow(owner)) { valid = false; break; }
            const bool self = site.flags & call_site_flags::self_tail;
            const bool kept = i + 1 == end && entry.site == kept_site;
            if (self) {
                // The newest self record includes a call whose physical
                // frame was kept. It is reported separately by the walker.
                if (kept) {
                    if (!entry.depth) { valid = false; break; }
                    --entry.depth;
                }
                if (entry.depth == std::numeric_limits<std::uint32_t>::max() || entry.depth + 1 < depth) {
                    valid = false; break;
                }
                const auto repeats = entry.depth + 1 - depth;
                if (repeats && !append({entry.site, owner, repeats, false})) { valid = false; break; }
                depth = entry.depth + 1;
                position = owner;
            } else {
                if (self_function(graph, owner) && entry.depth != depth) { valid = false; break; }
                if (kept) continue;
                if (site.callee_kind != static_cast<std::uint8_t>(CallSiteCallee::function)) {
                    // Today's indirect targets have a stack guard and no
                    // potential tails, so the physical target is the target.
                    if (i + 1 != end) { valid = false; break; }
                    if (!append({entry.site, target, 1, false})) { valid = false; break; }
                    position = target;
                    depth = 1;
                } else {
                    if (!append({entry.site, site.callee, 1, false})) { valid = false; break; }
                    position = site.callee;
                    depth = 1;
                }
            }
        }
        if (valid && follow(target)) {
            // A discarded outer record cannot be silently treated as an
            // absent self run. Retained inner CFAs remain complete.
            if (log.lost_at(cfa)) return {count, depth, false};
            return {count, depth, true};
        }
    }
    return {};
}
} // namespace quidra::runtime_tail
