#include "parallel_effects.hpp"
#include <limits>
#include <stdexcept>
#include <type_traits>
namespace quidra::semantics {
namespace {
std::optional<StoragePath> intersection(const PathSet& left,const PathSet& right) {
    for(const auto& path:left) if(overlaps_any(right,path)) return path;
    return std::nullopt;
}
bool resources_conflict(const ResourceAccess& left,const ResourceAccess& right) {
    if(left.kind!=right.kind) return false;
    if(left.origin==ResourceOrigin::Handle && right.origin==ResourceOrigin::Handle)
        return overlaps(left.handle,right.handle);
    return left.use==ResourceUse::Exclusive || right.use==ResourceUse::Exclusive;
}
std::optional<ParallelConflict> conflict(const ParallelNodeEffects& left,
    const ParallelNodeEffects& right,const std::vector<std::string>& names,
    const CheckedProgram* checked) {
    const auto storage=[&](const StoragePath& path,ParallelConflictKind kind) {
        ParallelConflict result;result.storage=describe(path,names);result.kind=kind;return result;
    };
    if(auto path=intersection(left.writes,right.writes)) return storage(*path,ParallelConflictKind::WriteWrite);
    if(auto path=intersection(left.reads,right.writes)) return storage(*path,ParallelConflictKind::ReadWrite);
    if(auto path=intersection(left.writes,right.reads)) return storage(*path,ParallelConflictKind::ReadWrite);
    const auto reference_overlap=[&](const std::map<std::string,Type>& shared,
                                     const std::map<StoragePath,Type>& targets,
                                     ParallelConflictKind kind)->std::optional<ParallelConflict> {
        for(const auto& [_,shared_type]:shared) for(const auto& [path,target_type]:targets)
            if(!checked || reference_target_compatible(*checked,shared_type,target_type))
                return storage(path,kind);
        return std::nullopt;
    };
    const auto directional_reference_conflict=[&](const ParallelNodeEffects& shared,
                                                  const ParallelNodeEffects& direct)
        ->std::optional<ParallelConflict> {
        if(auto found=reference_overlap(shared.reference_shared_writes,direct.reference_target_writes,
                                        ParallelConflictKind::WriteWrite))return found;
        if(auto found=reference_overlap(shared.reference_shared_writes,direct.reference_target_reads,
                                        ParallelConflictKind::ReadWrite))return found;
        if(auto found=reference_overlap(shared.reference_shared_reads,direct.reference_target_writes,
                                        ParallelConflictKind::ReadWrite))return found;
        if(auto found=reference_overlap(shared.reference_shared_writes,direct.reference_resolved_writes,
                                        ParallelConflictKind::WriteWrite))return found;
        if(auto found=reference_overlap(shared.reference_shared_writes,direct.reference_resolved_reads,
                                        ParallelConflictKind::ReadWrite))return found;
        return reference_overlap(shared.reference_shared_reads,direct.reference_resolved_writes,
                                 ParallelConflictKind::ReadWrite);
    };
    if(auto found=directional_reference_conflict(left,right))return found;
    if(auto found=directional_reference_conflict(right,left))return found;
    const auto resolved_overlap=[&](const std::map<StoragePath,Type>& resolved,
                                    const auto& targets,ParallelConflictKind kind)
        ->std::optional<ParallelConflict> {
        for(const auto& [path,_]:resolved) {
            if constexpr(std::is_same_v<std::decay_t<decltype(targets)>,PathSet>) {
                if(overlaps_any(targets,path))return storage(path,kind);
            } else {
                for(const auto& [target,_type]:targets)
                    if(overlaps(path,target))return storage(path,kind);
            }
        }
        return std::nullopt;
    };
    const auto directional_resolved_conflict=[&](const ParallelNodeEffects& resolved,
                                                 const ParallelNodeEffects& other)
        ->std::optional<ParallelConflict> {
        if(auto found=resolved_overlap(resolved.reference_resolved_writes,other.writes,
                                       ParallelConflictKind::WriteWrite))return found;
        if(auto found=resolved_overlap(resolved.reference_resolved_writes,other.reads,
                                       ParallelConflictKind::ReadWrite))return found;
        if(auto found=resolved_overlap(resolved.reference_resolved_reads,other.writes,
                                       ParallelConflictKind::ReadWrite))return found;
        if(auto found=resolved_overlap(resolved.reference_resolved_writes,other.reference_resolved_writes,
                                       ParallelConflictKind::WriteWrite))return found;
        if(auto found=resolved_overlap(resolved.reference_resolved_writes,other.reference_resolved_reads,
                                       ParallelConflictKind::ReadWrite))return found;
        return resolved_overlap(resolved.reference_resolved_reads,other.reference_resolved_writes,
                                ParallelConflictKind::ReadWrite);
    };
    if(auto found=directional_resolved_conflict(left,right))return found;
    if(auto found=directional_resolved_conflict(right,left))return found;
    for(const auto& a:left.shared) for(const auto& b:right.shared) {
        if(!a.writes && !b.writes) continue;
        if(a.fresh_region && b.fresh_region && a.fresh_region!=b.fresh_region) continue;
        return storage(a.path,a.writes && b.writes?ParallelConflictKind::WriteWrite:ParallelConflictKind::ReadWrite);
    }
    for(const auto& a:left.resources) for(const auto& b:right.resources)
        if(resources_conflict(a,b)) {
            ParallelConflict result;result.kind=ParallelConflictKind::Resource;result.resource=a.kind;
            result.handle=a.origin==ResourceOrigin::Handle && b.origin==ResourceOrigin::Handle;
            result.storage=result.handle?describe(a.handle,names):describe(a.kind);return result;
        }
    if(left.mutates_ambient && right.mutates_ambient) {
        ParallelConflict result;result.kind=ParallelConflictKind::Ambient;result.storage="runtime state";return result;
    }
    return std::nullopt;
}
}
ParallelDependencies parallel_dependencies(const std::vector<ParallelNodeEffects>& nodes,
    const std::vector<std::string>& parameter_names,const CheckedProgram* checked) {
    if(nodes.size()>std::numeric_limits<std::uint32_t>::max())
        throw std::length_error("too many parallel nodes");
    ParallelDependencies result;
    result.predecessors.resize(nodes.size());
    std::vector<std::vector<bool>> reachable(nodes.size(),std::vector<bool>(nodes.size()));
    for(std::uint32_t j=0;j<nodes.size();++j) {
        for(std::uint32_t i=0;i<j;++i)
            if(intersection(nodes[i].writes,nodes[j].reads)) {
                reachable[j][i]=true;
                for(std::uint32_t p=0;p<i;++p) reachable[j][p]=reachable[j][p] || reachable[i][p];
            }
        for(std::uint32_t i=0;i<j;++i) if(reachable[j][i]) result.predecessors[j].push_back(i);
    }
    for(std::uint32_t i=0;i<nodes.size();++i) for(std::uint32_t j=i+1;j<nodes.size();++j) {
        if(reachable[j][i]) continue;
        if(auto found=conflict(nodes[i],nodes[j],parameter_names,checked)) {
            found->first=i;found->second=j;result.conflict=std::move(found);
            return result;
        }
    }
    return result;
}
} // namespace quidra::semantics
