#pragma once
#include "quidra/ir/module.hpp"
#include "llvm_backend/string_pool.hpp"
#include <string>
namespace quidra::llvm_backend {
class CallSiteMetadata;
std::string emit_parallel_node_tables(const ir::Module& module,StringPool& pool);
std::string emit_parallel_node_wrapper(const ir::Function& function,CallSiteMetadata* metadata=nullptr);
}
