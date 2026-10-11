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
} // namespace
int main() {
    merged_inline_requires_proved_endpoints();
    unavailable_cfa_and_proved_inline_edges();
    unique_and_ambiguous_paths();
    self_runs_and_kept_calls();
    inline_levels_and_lost_outer_entries();
}
