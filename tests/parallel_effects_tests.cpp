#include "semantics/parallel_effects.hpp"
#include <cstdio>
#include <cstdlib>
using namespace quidra::semantics;
void require(bool yes) {if(!yes) std::abort();}
StoragePath local(const char* name) {return {StorageRoot::local(name),{}};}
ResourceAccess direct(ResourceKind kind,ResourceUse use) {return {kind,use,ResourceOrigin::Direct,{}};}
ResourceAccess handle(const char* name,ResourceUse use) {return {ResourceKind::FileSystem,use,ResourceOrigin::Handle,local(name)};}
bool rejected(ParallelNodeEffects a,ParallelNodeEffects b) {
    const auto result=parallel_dependencies({std::move(a),std::move(b)});
    if(result.conflict) require(result.conflict->first==0 && result.conflict->second==1);
    return result.conflict.has_value();
}
int main() {
    const auto x=local("x"),y=local("y"),z=local("z");
    ParallelNodeEffects a,b,c,d;
    ParallelNodeEffects address_only,producer;
    address_only.address_roots={x};producer.writes={x};
    const auto address_plan=parallel_dependencies({producer,address_only});
    require(!address_plan.conflict && address_plan.predecessors[1].empty());
    a.writes={x};b.reads={x};b.writes={y};c.reads={x};c.writes={z};d.reads={y,z};
    const auto diamond=parallel_dependencies({a,b,c,d});
    require(!diamond.conflict && diamond.predecessors==std::vector<std::vector<std::uint32_t>>{{},{0},{0},{0,1,2}});
    require(rejected(a,a));
    ParallelNodeEffects read;read.reads={x};require(rejected(read,a));
    require(!rejected(a,read)); // RAW establishes the source-order edge.
    ParallelNodeEffects field_a,field_b;
    field_a.writes={x.child(PathStep::field_named("a"))};field_b.writes={x.child(PathStep::field_named("b"))};
    require(!rejected(field_a,field_b));
    field_b.writes={x};require(rejected(field_a,field_b));
    field_a.writes={x.child(PathStep::element(0))};field_b.writes={x.child(PathStep::element(1))};
    require(!rejected(field_a,field_b));field_b.writes={x.child(PathStep::any_element())};require(rejected(field_a,field_b));
    auto pair=[&](ResourceAccess one,ResourceAccess two,bool expected) {
        ParallelNodeEffects left,right;left.resources={one};right.resources={two};
        const auto graph=parallel_dependencies({left,right});
        require(graph.predecessors[1].empty());require(graph.conflict.has_value()==expected);
    };
    using K=ResourceKind;using U=ResourceUse;
    pair(direct(K::Stdout,U::Exclusive),direct(K::Stdout,U::Exclusive),true);
    pair(direct(K::FileSystem,U::Shared),direct(K::FileSystem,U::Exclusive),true);
    pair(direct(K::FileSystem,U::Shared),direct(K::FileSystem,U::Shared),false);
    pair(direct(K::Network,U::Exclusive),direct(K::Network,U::Exclusive),true);
    pair(direct(K::Clock,U::Exclusive),direct(K::Clock,U::Exclusive),true);
    pair(direct(K::Clock,U::Exclusive),direct(K::Clock,U::Shared),true);
    pair(direct(K::Clock,U::Shared),direct(K::Clock,U::Shared),false);
    pair(direct(K::Environment,U::Shared),direct(K::Environment,U::Shared),false);
    pair(handle("a",U::Shared),handle("a",U::Shared),true);
    pair(handle("a",U::Exclusive),handle("b",U::Exclusive),false);
    pair(handle("a",U::Shared),direct(K::FileSystem,U::Exclusive),true);
    pair(handle("a",U::Exclusive),direct(K::FileSystem,U::Shared),true);
    pair(handle("a",U::Shared),direct(K::FileSystem,U::Shared),false);
    pair(direct(K::Process,U::Exclusive),direct(K::FileSystem,U::Shared),false);
    ParallelNodeEffects process,file;
    process.resources={direct(K::Process,U::Exclusive),direct(K::FileSystem,U::Exclusive),direct(K::Network,U::Exclusive),direct(K::Stdin,U::Exclusive)};
    file.resources={direct(K::FileSystem,U::Shared)};require(rejected(process,file));
    file.resources={handle("f",U::Shared)};require(rejected(process,file));
    file.resources={handle("f",U::Exclusive)};require(rejected(process,file));
    // Extern I/O has no summary resource; it therefore commutes with print.
    ParallelNodeEffects foreign,print;print.resources={direct(K::Stdout,U::Exclusive)};
    require(!rejected(foreign,print));
    ParallelNodeEffects shared_a,shared_b;
    shared_a.shared={{{StorageRoot::shared("a"),{}},true,0}};
    shared_b.shared={{{StorageRoot::shared("b"),{}},false,0}};require(rejected(shared_a,shared_b));
    shared_a.shared[0].fresh_region=1;shared_b.shared[0].fresh_region=2;require(!rejected(shared_a,shared_b));
    shared_b.shared[0].fresh_region=1;require(rejected(shared_a,shared_b));
    shared_a.shared[0].writes=false;require(!rejected(shared_a,shared_b));
    ParallelNodeEffects ambient;ambient.mutates_ambient=true;require(rejected(ambient,ambient));
    // An unrelated RAW chain may order otherwise conflicting resource uses.
    print.writes={x};ParallelNodeEffects ordered=print;ordered.writes.clear();ordered.reads={x};
    require(!rejected(print,ordered));
    const auto parameter=StoragePath{StorageRoot::parameter(0),{}};
    ParallelNodeEffects named;named.writes={parameter};
    const auto named_conflict=parallel_dependencies({named,named},{"total"});
    require(named_conflict.conflict && named_conflict.conflict->storage=="total" &&
        named_conflict.conflict->kind==ParallelConflictKind::WriteWrite);
    ParallelNodeEffects named_reader;named_reader.reads={parameter};
    require(parallel_dependencies({named_reader,named},{"total"}).conflict->kind==ParallelConflictKind::ReadWrite);
    ParallelNodeEffects output;output.resources={direct(K::Stdout,U::Exclusive)};
    output.mutates_ambient=true;
    const auto resource_conflict=parallel_dependencies({output,output});
    require(resource_conflict.conflict && resource_conflict.conflict->kind==ParallelConflictKind::Resource &&
        resource_conflict.conflict->resource==K::Stdout);
    quidra::CheckedProgram checked;
    const auto integer=quidra::Type::simple(quidra::TypeKind::Int32);
    const auto text=quidra::Type::simple(quidra::TypeKind::String);
    ParallelNodeEffects stored_writer,direct_reader,direct_writer,unmarked;
    stored_writer.reference_shared_writes.emplace("int32",integer);
    direct_reader.reads={x};direct_reader.reference_target_reads.emplace(x,integer);
    direct_writer.writes={x};direct_writer.reference_target_writes.emplace(x,integer);
    const auto shared_read=parallel_dependencies({stored_writer,direct_reader},{},&checked);
    require(shared_read.conflict && shared_read.conflict->kind==ParallelConflictKind::ReadWrite);
    // An unknown stored target is a hazard, never an inferred RAW edge.
    require(shared_read.predecessors[1].empty());
    require(parallel_dependencies({direct_reader,stored_writer},{},&checked).conflict.has_value());
    require(parallel_dependencies({stored_writer,direct_writer},{},&checked).conflict->kind==ParallelConflictKind::WriteWrite);
    direct_reader.reference_target_reads[x]=text;
    require(!parallel_dependencies({stored_writer,direct_reader},{},&checked).conflict);
    unmarked.reads={x};
    require(!parallel_dependencies({stored_writer,unmarked},{},&checked).conflict);
    ParallelNodeEffects stored_reader;stored_reader.reference_shared_reads.emplace("int32",integer);
    require(parallel_dependencies({stored_reader,direct_writer},{},&checked).conflict->kind==ParallelConflictKind::ReadWrite);
    direct_reader.reference_target_reads[x]=integer;
    require(!parallel_dependencies({stored_reader,direct_reader},{},&checked).conflict);
    ParallelNodeEffects resolved_a,resolved_b;
    resolved_a.reference_resolved_writes.emplace(x,integer);
    resolved_b.reference_resolved_writes.emplace(y,integer);
    require(!parallel_dependencies({resolved_a,resolved_b},{},&checked).conflict);
    resolved_b.reference_resolved_writes.clear();
    resolved_b.reference_resolved_reads.emplace(x,integer);
    const auto resolved_read=parallel_dependencies({resolved_a,resolved_b},{},&checked);
    require(resolved_read.conflict && resolved_read.predecessors[1].empty());
    require(parallel_dependencies({resolved_a,unmarked},{},&checked).conflict.has_value());
    require(parallel_dependencies({unmarked,resolved_a},{},&checked).conflict.has_value());
    require(parallel_dependencies({stored_writer,resolved_b},{},&checked).conflict.has_value());
    std::puts("parallel RAW closure/storage/shared/resource conflict contract: PASS");
}
