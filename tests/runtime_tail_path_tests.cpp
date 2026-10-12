#include "runtime_tail_path.hpp"
#include "quidra/call_site_info.hpp"

#include <array>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace quidra;
using namespace quidra::runtime_tail;
namespace {
void expect(bool value, const char* message) {
    if (!value) { std::cerr << message << '\n'; std::exit(1); }
}
struct Fixture {
    std::vector<table::SharedFunction> functions;
    std::vector<table::SharedSite> sites{{}};
    std::vector<std::uint32_t> owners{table::no_function};
    explicit Fixture(std::size_t count) : functions(count) {}
    std::uint32_t edge(std::uint32_t owner, std::uint32_t callee, std::uint8_t flags) {
        const auto id = static_cast<std::uint32_t>(sites.size());
        auto& function = functions.at(owner);
        if (!function.site_count) function.first_site = id;
        expect(function.first_site + function.site_count == id, "fixture sites are grouped by owner");
        ++function.site_count;
        sites.push_back({id, 0, 1, callee, static_cast<std::uint8_t>(CallSiteCallee::function), flags, 0});
        owners.push_back(owner);
        return id;
    }
    Graph graph() const {
        return {this, static_cast<std::uint32_t>(functions.size()), static_cast<std::uint32_t>(sites.size()),
            [](const void* context, std::uint32_t id) { return static_cast<const Fixture*>(context)->functions.at(id); },
            [](const void* context, std::uint32_t id) { return static_cast<const Fixture*>(context)->sites.at(id); },
            [](const void* context, std::uint32_t id) { return static_cast<const Fixture*>(context)->owners.at(id); }};
    }
};
constexpr auto tail = call_site_flags::tail;
constexpr auto recorded = tail | call_site_flags::recorded_tail;
constexpr auto self = recorded | call_site_flags::self_tail;

void unique_and_ambiguous_paths() {
    Fixture f(3);
    const auto a = f.edge(0, 1, tail);
    const auto b = f.edge(1, 2, tail);
    std::array<Hop, 16> hops;
    const auto result = recover(f.graph(), {}, 1000, 0, 2, 1, {}, 0, hops);
    expect(result.complete && result.count == 2 && hops[0].site == a && hops[1].site == b,
           "a unique acyclic path is recovered without records");
    Fixture ambiguous(2);
    const auto first = ambiguous.edge(0, 1, recorded);
    const auto second = ambiguous.edge(0, 1, recorded);
    expect(!recover(ambiguous.graph(), {}, 1000, 0, 1, 1, {}, 0, hops).complete,
           "an ambiguous path with no record never guesses a site");
    const Entry entry{second, 0, 1000};
    const auto chosen = recover(ambiguous.graph(), {{&entry, 1}}, 1000, 0, 1, 1, {}, 0, hops);
    expect(chosen.complete && chosen.count == 1 && hops[0].site == second && hops[0].site != first,
           "the record chooses the branch that ran");
}

void self_runs_and_kept_calls() {
    Fixture f(2);
    f.functions[0].flags = call_site_function_flags::self_tail;
    const auto recursive = f.edge(0, 0, self);
    const auto exit = f.edge(0, 1, recorded);
    std::array<Hop, 16> hops;
    Entry run{recursive, 500, 1000};
    auto result = recover(f.graph(), {{&run, 1}}, 1000, 0, 0, 1, {}, 0, hops);
    expect(result.complete && result.count == 1 && hops[0].repeat == 500 && result.depth == 501,
           "a collapsed self run reports every logical call");
    run.depth = 10;
    result = recover(f.graph(), {{&run, 1}}, 1000, 0, 0, 6, {}, 0, hops);
    expect(result.complete && hops[0].repeat == 5 && result.depth == 11,
           "a physical self caller supplies the child's starting depth");
    result = recover(f.graph(), {{&run, 1}}, 1000, 0, 0, 6, {}, recursive, hops);
    expect(result.complete && hops[0].repeat == 4 && result.depth == 10,
           "a physically kept self call is subtracted exactly once");
    const Entry exited[]{{recursive, 7, 1000}, {exit, 8, 1000}};
    result = recover(f.graph(), {{exited, 2}}, 1000, 0, 1, 1, {}, 0, hops);
    expect(result.complete && result.count == 2 && hops[0].repeat == 7 && hops[1].site == exit,
           "a recorded exit follows the self run at the next depth");
    result = recover(f.graph(), {{exited, 2}}, 1000, 0, 0, 1, {}, 0, hops);
    expect(result.complete && result.count == 0 && result.depth == 1,
           "an earlier tail exit cannot become the next activation's self run");
    result = recover(f.graph(), {{exited, 2}}, 1000, 0, 0, 1, {}, exit, hops);
    expect(result.complete && result.count == 1 && hops[0].repeat == 7 && result.depth == 8,
           "a kept tail exit reports its physical call separately");
}

void inline_levels_and_lost_outer_entries() {
    Fixture f(2);
    const auto inline_site = f.edge(0, 1, 0);
    f.functions[1].flags = call_site_function_flags::self_tail;
    const auto recursive = f.edge(1, 1, self);
    const Entry run{recursive, 500, 900};
    const std::uint32_t inline_sites[]{inline_site};
    std::array<Hop, 16> hops;
    auto result = recover(f.graph(), {{&run, 1}}, 900, 0, 1, 1, inline_sites, 0, hops);
    expect(result.complete && result.count == 2 && hops[0].inlined && hops[1].repeat == 500,
           "a self run in an inlined copy uses the physical frame's CFA");
    Snapshot lost{{&run, 1}, 32, 1000, 1200, 1, 3};
    result = recover(f.graph(), lost, 900, 0, 1, 1, inline_sites, 0, hops);
    expect(result.complete, "lost outer records do not obscure a retained inner frame");
    result = recover(f.graph(), lost, 1000, 0, 1, 1, inline_sites, 0, hops);
    expect(!result.complete, "the discarded outer region is explicitly incomplete");
}
void unavailable_cfa_and_proved_inline_edges() {
    Fixture f(2);
    const auto call = f.edge(0, 1, recorded);
    const std::uint32_t inline_sites[]{call};
    std::array<Hop, 16> hops;
    auto result = recover(f.graph(), {}, 0, 0, 1, 1, inline_sites, 0, hops);
    expect(result.complete && result.count == 1 && hops[0].inlined,
           "a proved inline row needs no tail log to identify its edge");
    f.sites[call].callee_kind = static_cast<std::uint8_t>(CallSiteCallee::indirect);
    result = recover(f.graph(), {}, 0, 0, 1, 1, inline_sites, 0, hops);
    expect(result.complete && result.count == 1 && hops[0].callee == 1,
           "the inline hierarchy proves an indirect edge's actual target");
    expect(!recover(f.graph(), {}, 0, 0, 1, 1, {}, 0, hops).complete,
           "an unresolved indirect call cannot invent its target");
    f.functions[1].flags = call_site_function_flags::self_tail;
    expect(!recover(f.graph(), {}, 0, 0, 1, 1, inline_sites, 0, hops).complete,
           "an unavailable CFA cannot silently discard a possible self run");
    expect(!recover(f.graph(), {}, 0, 1, 1, 1, {}, 0, hops).complete,
           "a physical self frame also requires a valid CFA");
}
void merged_inline_requires_proved_endpoints() {
    Fixture f(3);
    const auto first=f.edge(0,1,0);
    f.edge(0,1,0);
    const auto suffix=f.edge(1,2,tail);
    const std::uint32_t unknown[]{0};
    const InlineEdge proof[]{ {0,1} };
    std::array<Hop,16> hops;
    expect(!recover(f.graph(),{},1000,0,2,1,unknown,0,hops).complete,
           "line zero alone cannot authorize a non-tail call");
    const auto result=recover(f.graph(),{},1000,0,2,1,unknown,0,hops,proof);
    expect(result.complete && result.count==2 && hops[0].site==first &&
           hops[0].merged && hops[0].inlined && hops[0].owner==0 && hops[1].site==suffix,
           "proved endpoints retain equivalent sites as one merged inline hop");
    const InlineEdge wrong[]{ {0,2} };
    expect(!recover(f.graph(),{},1000,0,2,1,unknown,0,hops,wrong).complete,
           "a different endpoint cannot authorize the missing inline edge");
    Fixture ambiguous(4);
    ambiguous.edge(0,1,0);
    ambiguous.edge(0,3,tail);
    ambiguous.edge(1,2,tail);
    ambiguous.edge(3,2,tail);
    expect(!recover(ambiguous.graph(),{},1000,0,2,1,unknown,0,hops,proof).complete,
           "different logical hop structures remain incomplete");
}

void transparent_wrapper_recovers_without_inline_metadata() {
    Fixture f(2);
    const auto forwarded = f.edge(0, 1, call_site_flags::synthesized);
    std::array<Hop, 16> hops;
    expect(!recover(f.graph(), {}, 1000, 0, 1, 1, {}, 0, hops).complete,
           "an ordinary synthesized call cannot invent a missing inline edge");

    f.functions[0].flags = call_site_function_flags::transparent_forwarder;
    const auto result = recover(f.graph(), {}, 1000, 0, 1, 1, {}, 0, hops);
    expect(result.complete && result.count == 1 && hops[0].site == forwarded && hops[0].callee == 1,
           "a declared forwarding wrapper reaches its body without inline metadata");
}

void merged_calls_retain_the_unique_source_wrapper() {
    Fixture f(3);
    f.edge(0, 1, call_site_flags::synthesized);
    f.edge(2, 0, call_site_flags::user);
    f.edge(2, 0, call_site_flags::user);

    const auto ordinary = logical_call_entry(f.graph(), 2, 1);
    expect(!ordinary.ambiguous && ordinary.function == 1,
           "an unflagged function cannot stand in for the observed physical callee");

    f.functions[0].flags = call_site_function_flags::transparent_forwarder;
    const auto merged = logical_call_entry(f.graph(), 2, 1);
    expect(!merged.ambiguous && merged.function == 0,
           "multiple merged source sites of one wrapper retain that wrapper as the logical callee");
    const auto direct = logical_call_entry(f.graph(), 2, 0);
    expect(!direct.ambiguous && direct.function == 0,
           "a physically retained wrapper keeps its direct source identity");
}

void nested_forwarding_wrappers_recover_one_route() {
    Fixture f(4);
    f.functions[0].flags = call_site_function_flags::transparent_forwarder;
    f.functions[1].flags = call_site_function_flags::transparent_forwarder;
    const auto outer = f.edge(0, 1, call_site_flags::synthesized);
    const auto inner = f.edge(1, 2, call_site_flags::synthesized);
    f.edge(3, 0, call_site_flags::user);
    const auto entry = logical_call_entry(f.graph(), 3, 2);
    expect(!entry.ambiguous && entry.function == 0,
           "a chain of declared wrappers resolves to its source-level entry");
    std::array<Hop, 16> hops;
    const auto result = recover(f.graph(), {}, 1000, 0, 2, 1, {}, 0, hops);
    expect(result.complete && result.count == 2 && hops[0].site == outer && hops[1].site == inner,
           "a declared wrapper chain preserves each forwarding edge without inline metadata");
}

void converging_source_wrappers_remain_ambiguous() {
    Fixture f(4);
    f.functions[0].flags = call_site_function_flags::transparent_forwarder;
    f.functions[1].flags = call_site_function_flags::transparent_forwarder;
    f.edge(0, 2, call_site_flags::synthesized);
    f.edge(1, 2, call_site_flags::synthesized);
    f.edge(3, 0, call_site_flags::user);
    const auto alternative = f.edge(3, 1, call_site_flags::user);
    const auto entry = logical_call_entry(f.graph(), 3, 2);
    expect(entry.ambiguous && entry.function == table::no_function,
           "different source wrappers reaching one physical body cannot select a logical callee");

    f.sites[alternative].callee = 2;
    const auto direct_or_wrapper = logical_call_entry(f.graph(), 3, 2);
    expect(direct_or_wrapper.ambiguous && direct_or_wrapper.function == table::no_function,
           "a direct call and a wrapper reaching the same body cannot select the direct call's site");
}

void ordinary_routes_make_wrapper_recovery_ambiguous() {
    // The caller invokes either wrapper W or ordinary user function U.
    // W forwards to body B; U calls W. LLVM may inline U and merge both
    // branches to a direct call of B, erasing the inline hierarchy.
    Fixture f(4);  // W=0, B=1, U=2, caller=3.
    f.functions[0].flags = call_site_function_flags::transparent_forwarder;
    f.edge(0, 1, call_site_flags::synthesized);
    const auto user_call = f.edge(2, 0, call_site_flags::user);
    f.edge(3, 0, call_site_flags::user);
    f.edge(3, 2, call_site_flags::user);
    std::array<Hop, 16> hops;
    expect(!recover(f.graph(), {}, 1000, 2, 1, 1, {}, 0, hops).complete,
           "a possible user-call route cannot authorize an unproved inline edge");
    const auto entry = logical_call_entry(f.graph(), 3, 1);
    expect(entry.ambiguous && entry.function == table::no_function,
           "an alternate ordinary user-call route prevents selecting the wrapper's source site");

    f.sites[user_call].flags |= call_site_flags::tail;
    const auto tail_entry = logical_call_entry(f.graph(), 3, 1);
    expect(tail_entry.ambiguous && tail_entry.function == table::no_function,
           "an alternate user tail-call route also prevents selecting the wrapper's source site");

    auto unrelated = f;
    unrelated.functions[2].site_count = 0;
    const auto unique_entry = logical_call_entry(unrelated.graph(), 3, 1);
    expect(!unique_entry.ambiguous && unique_entry.function == 0,
           "an unrelated source callee does not obscure a proven forwarding entry");
}

void unknown_alternate_targets_remain_ambiguous() {
    Fixture f(4);
    f.functions[0].flags = call_site_function_flags::transparent_forwarder;
    f.edge(0, 1, call_site_flags::synthesized);
    const auto unknown = f.edge(2, table::no_function, call_site_flags::user);
    f.sites[unknown].callee_kind = static_cast<std::uint8_t>(CallSiteCallee::indirect);
    f.edge(3, 0, call_site_flags::user);
    f.edge(3, 2, call_site_flags::user);
    const auto indirect = logical_call_entry(f.graph(), 3, 1);
    expect(indirect.ambiguous && indirect.function == table::no_function,
           "an indirect call on an alternative user route can reach the physical target");

    f.sites[unknown].callee_kind = static_cast<std::uint8_t>(CallSiteCallee::extern_function);
    f.sites[unknown].flags |= call_site_flags::extern_callback;
    const auto callback = logical_call_entry(f.graph(), 3, 1);
    expect(callback.ambiguous && callback.function == table::no_function,
           "an extern callback on an alternative user route can reach the physical target");

    f.sites[unknown].flags = call_site_flags::user;
    const auto ordinary_extern = logical_call_entry(f.graph(), 3, 1);
    expect(!ordinary_extern.ambiguous && ordinary_extern.function == 0,
           "an extern call without callbacks cannot invent an alternate user route");
}

void invalid_forwarding_relations_remain_incomplete() {
    Fixture ambiguous(4);
    ambiguous.functions[0].flags = call_site_function_flags::transparent_forwarder;
    ambiguous.edge(0, 1, call_site_flags::synthesized);
    ambiguous.edge(0, 2, call_site_flags::synthesized);
    ambiguous.edge(3, 0, call_site_flags::user);
    const auto entry = logical_call_entry(ambiguous.graph(), 3, 1);
    expect(entry.ambiguous && entry.function == table::no_function,
           "a declared wrapper with multiple forwarding edges does not prove a call entry");
    std::array<Hop, 16> hops;
    expect(!recover(ambiguous.graph(), {}, 1000, 0, 1, 1, {}, 0, hops).complete,
           "a malformed wrapper cannot authorize one of its forwarding edges");

    Fixture cycle(4);
    cycle.functions[0].flags = call_site_function_flags::transparent_forwarder;
    cycle.functions[1].flags = call_site_function_flags::transparent_forwarder;
    cycle.edge(0, 1, call_site_flags::synthesized);
    cycle.edge(1, 0, call_site_flags::synthesized);
    cycle.edge(3, 0, call_site_flags::user);
    const auto cyclic_entry = logical_call_entry(cycle.graph(), 3, 1);
    expect(cyclic_entry.ambiguous && cyclic_entry.function == table::no_function,
           "a forwarding cycle cannot prove a target even when its prefix reaches that target");
    expect(!recover(cycle.graph(), {}, 1000, 0, 1, 1, {}, 0, hops).complete,
           "a cyclic forwarding relation cannot authorize a missing inline edge");
}
} // namespace
int main() {
    transparent_wrapper_recovers_without_inline_metadata();
    merged_calls_retain_the_unique_source_wrapper();
    nested_forwarding_wrappers_recover_one_route();
    converging_source_wrappers_remain_ambiguous();
    ordinary_routes_make_wrapper_recovery_ambiguous();
    unknown_alternate_targets_remain_ambiguous();
    invalid_forwarding_relations_remain_incomplete();
    merged_inline_requires_proved_endpoints();
    unavailable_cfa_and_proved_inline_edges();
    unique_and_ambiguous_paths();
    self_runs_and_kept_calls();
    inline_levels_and_lost_outer_entries();
}
