#pragma once
#include "node_failure.hpp"
#include "quidra/abi/runtime_entry_points.hpp"
#include <utility>
namespace quidra::runtime {
// A runtime intermediate has no generated SSA shadow until its C ABI returns.
// Outside a node the existing allocation/failure path is unchanged.
class NodeRuntimeOwner {
public:
    explicit NodeRuntimeOwner(void* value,void (*drop)(void*)=release_managed)noexcept
        :value_(node_failure_active()?value:nullptr),drop_(drop){}
    NodeRuntimeOwner(const NodeRuntimeOwner&)=delete;
    NodeRuntimeOwner& operator=(const NodeRuntimeOwner&)=delete;
    ~NodeRuntimeOwner(){if(value_)cleanup_node_slot(drop_,std::exchange(value_,nullptr));}
    void relinquish()noexcept{value_=nullptr;}
    void replace(void* value)noexcept{value_=node_failure_active()?value:nullptr;}
private:
    static void release_managed(void* value){quidra_managed_release(value,nullptr);}
    void* value_{};
    void (*drop_)(void*){};
};
}
