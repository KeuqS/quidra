#pragma once

// Type helpers: the LLVM functions a module defines once per type, after the
// function bodies, for the values whose clone, drop, equality or numeric
// array cast needs code of its own.
//
// Owns: the helper symbols, the collection of the types a module needs and
// the text of each clone, drop and equality helper (the array cast helpers
// are array_cast_helpers.hpp), and TypeHelperSet, which runs them all for
// one module.
// The collectors key their std::map by type_identifier, so helpers are
// emitted in identifier order, once per type; collecting can throw (a
// malformed array cast, an unknown class), so nothing is collected before
// every function is emitted.

#include "quidra/ir/module.hpp"
#include "llvm_backend/array_cast_helpers.hpp"
#include "llvm_backend/storage_layout.hpp"
#include "llvm_text/llvm_builder.hpp"
#include "llvm_text/llvm_module.hpp"

#include <map>
#include <string>
#include <unordered_map>

namespace quidra::llvm_backend {

// The helper symbols (@quidra_clone_<id>, ...), named by type_identifier
// (runtime_abi::generated_helper_prefix).
std::string clone_name(const Type&t);
std::string drop_name(const Type&t);
std::string equality_name(const Type&t);
std::string stored_targets_name(const Type& type);
bool holds_reference_fields(const Type&,const std::unordered_map<std::string,ir::ClassLayout>&);
// The slice helpers of an array type: @quidra_slice_get_<id>
// copies the elements a slice selects into a new runtime-sized array, and
// @quidra_slice_set_<id> stores an array's elements into them. Both plan the
// slice with the runtime's quidra_slice_plan, which owns the direction, step
// and bound rules and their failures.
std::string slice_get_name(const Type& array);
std::string slice_set_name(const Type& array);

// The drop callback that releasing a value of `type` passes to the runtime:
// the runtime's drop function of a big number or a runtime handle, the drop
// helper of a type that has one, or null.
std::string drop_callback_for(const Type& type,
                              const std::unordered_map<std::string,ir::ClassLayout>& layouts);

// The entry block of a helper whose parameter %src may be null: a null
// source returns null (block null.ret), any other continues at `body`.
// The clone helpers and the array cast helpers (array_cast_helpers.hpp)
// begin with it.
void return_null_for_null_source(llvm_text::LlvmBuilder& b, llvm_text::LlvmBlock body);

// Deep copies of the types that Clone instructions copy.
void collect_clone_types(const ir::Module&m,std::map<std::string,Type>&types,const std::unordered_map<std::string,ir::ClassLayout>&layouts);
std::string emit_clone_helper(const Type&t,const std::unordered_map<std::string,ir::ClassLayout>&layouts,const ArrayLayoutPolicy&array_layout);

// Releases of owned values: the drop callbacks passed to the runtime.
void collect_drop_types(const ir::Module& module, std::map<std::string,Type>& types,
                        const std::unordered_map<std::string,ir::ClassLayout>& layouts);
std::string emit_drop_helper(const Type& type,
                             const std::unordered_map<std::string,ir::ClassLayout>& layouts,
                             const ArrayLayoutPolicy& array_layout);

// The slice helpers of the array types that ArraySlice and ArraySliceSet
// slice.
std::string emit_slice_get_helper(const Type& array,
                                  const std::unordered_map<std::string,ir::ClassLayout>& layouts,
                                  const ArrayLayoutPolicy& array_layout);
std::string emit_slice_set_helper(const Type& array,
                                  const std::unordered_map<std::string,ir::ClassLayout>& layouts,
                                  const ArrayLayoutPolicy& array_layout);

// Structural equality: == and != on bins, arrays and classes.
void collect_equality_types(const ir::Module& module, std::map<std::string,Type>& types,
                            const std::unordered_map<std::string,ir::ClassLayout>& layouts);
std::string emit_equality_helper(
    const Type& type,
    const std::unordered_map<std::string,ir::ClassLayout>& layouts,
    const ArrayLayoutPolicy& array_layout);

// TypeHelperSet: the type helpers of one module.
//
// Owns the array cast pairs and the clone, drop, equality and slice types. Which
// exception comes first, when several steps would throw, is part of the
// behavior, so collecting and writing interleave in a fixed order:
// collect_array_casts_and_clones runs once every function is emitted; emit
// writes the array cast and clone helpers, then collects and writes the drop
// helpers, then the equality helpers, then the slice helpers (collected with
// the clones, whose element copies they call), into the module's helpers
// section.
class TypeHelperSet {
public:
    TypeHelperSet(const ir::Module& module,
                  const std::unordered_map<std::string,ir::ClassLayout>& layouts,
                  const ArrayLayoutPolicy& array_layout)
        :module_(module),layouts_(layouts),array_layout_(array_layout){}

    void collect_array_casts_and_clones();
    void emit(llvm_text::LlvmModule& module);

private:
    const ir::Module& module_;
    const std::unordered_map<std::string,ir::ClassLayout>& layouts_;
    const ArrayLayoutPolicy& array_layout_;
    std::map<std::string,ArrayCastPair> array_cast_pairs_;
    std::map<std::string, Type> clone_types_;
    std::map<std::string, Type> drop_types_;
    std::map<std::string, Type> equality_types_;
    std::map<std::string, Type> slice_get_types_;
    std::map<std::string, Type> slice_set_types_;
};

} // namespace quidra::llvm_backend
