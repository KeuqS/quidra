#pragma once

// TypeKind: the kind of a Type (quidra/types.hpp). The numeric kinds are
// described by quidra/numeric_types.hpp.
//
// The enumerators' positions are part of the typed IR's text (`ir.full` prints
// kinds as integers), so a new kind is appended after Invalid and no existing
// position moves.

namespace quidra {

enum class TypeKind {
    Int64,
    Int8,
    Int16,
    Int32,
    Nat8,
    Nat16,
    Nat32,
    Nat64,
    Int,
    Real64,
    Real32,
    Real,
    Bool,
    String,
    Bin,
    Void,
    Never,
    Error,
    None,
    Array,
    Tensor,
    Union,
    Class,
    Address,
    Function,
    Auto,
    Range,
    Invalid,
    Nat,
    Real16,
    Real16b,
    Com16,
    Com16b,
    Com32,
    Com64,
    Com,
    Tuple,
    Traversal
};

} // namespace quidra
