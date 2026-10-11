#pragma once

// Tensor element types as generated code, the runtime, device code and native
// packages name them.
//
// Owns: the dtype codes and the element kinds of a sorted array. The dtype
// codes are the QCORE_DTYPE_* enumerators of quidra/native_extension.h, which
// the native package ABI defines; the runtime and device code compare and
// switch on those enumerators, never on their numbers.
//
// The codes are ordered: the signed integers int64, int8, int16 and int32,
// the unsigned integers uint8, uint16, uint32 and uint64, then float64,
// float32 and bool, then the appended 16-bit reals float16 (real16) and
// bfloat16 (real16b), then the appended complex dtypes, a real part and an
// imaginary part each: complex16 (com16), complex16b (com16b), complex32
// (com32) and complex64 (com64). Range tests rely on the order: the integer
// dtypes are
// QCORE_DTYPE_INT64 to QCORE_DTYPE_UINT64 (the signed ones up to
// QCORE_DTYPE_INT32), and the numeric dtypes QCORE_DTYPE_INT64 to
// QCORE_DTYPE_FLOAT32 and QCORE_DTYPE_FLOAT16 to QCORE_DTYPE_BFLOAT16
// (abi::numeric_dtype_code).

#include "quidra/native_extension.h"

#include <array>
#include <cstddef>
#include <string_view>

namespace quidra::abi {

// The dtype codes as a type, for code that maps types to them (the compiler,
// ir::dtype_of); the runtime compares its int dtype fields with the
// QCORE_DTYPE_* enumerators directly.
enum class Dtype : int {
    int64 = QCORE_DTYPE_INT64,
    int8 = QCORE_DTYPE_INT8,
    int16 = QCORE_DTYPE_INT16,
    int32 = QCORE_DTYPE_INT32,
    uint8 = QCORE_DTYPE_UINT8,
    uint16 = QCORE_DTYPE_UINT16,
    uint32 = QCORE_DTYPE_UINT32,
    uint64 = QCORE_DTYPE_UINT64,
    float64 = QCORE_DTYPE_FLOAT64,
    float32 = QCORE_DTYPE_FLOAT32,
    boolean = QCORE_DTYPE_BOOL,
    float16 = QCORE_DTYPE_FLOAT16,
    bfloat16 = QCORE_DTYPE_BFLOAT16,
    complex16 = QCORE_DTYPE_COMPLEX_FLOAT16,
    complex16b = QCORE_DTYPE_COMPLEX_BFLOAT16,
    complex32 = QCORE_DTYPE_COMPLEX_FLOAT32,
    complex64 = QCORE_DTYPE_COMPLEX_FLOAT64,
};

// The code that crosses the C ABI (an int parameter or field).
constexpr int dtype_code(Dtype dtype) { return static_cast<int>(dtype); }

// What the runtime stores per element of a dtype: its size in bytes (bool
// takes one byte), and the canonical spelling of the dtype's Quidra type,
// which runtime messages print (quidra/numeric_types.hpp checks that the
// numeric rows spell their types the same way).
struct DtypeInfo {
    Dtype dtype;
    int bytes;
    std::string_view quidra_name;
};

inline constexpr std::array<DtypeInfo, 17> dtype_infos{{
    {Dtype::int64, 8, "int64"},
    {Dtype::int8, 1, "int8"},
    {Dtype::int16, 2, "int16"},
    {Dtype::int32, 4, "int32"},
    {Dtype::uint8, 1, "nat8"},
    {Dtype::uint16, 2, "nat16"},
    {Dtype::uint32, 4, "nat32"},
    {Dtype::uint64, 8, "nat64"},
    {Dtype::float64, 8, "real64"},
    {Dtype::float32, 4, "real32"},
    {Dtype::boolean, 1, "bool"},
    {Dtype::float16, 2, "real16"},
    {Dtype::bfloat16, 2, "real16b"},
    {Dtype::complex16, 4, "com16"},
    {Dtype::complex16b, 4, "com16b"},
    {Dtype::complex32, 8, "com32"},
    {Dtype::complex64, 16, "com64"},
}};

// Only the canonical language spelling names a tensor dtype in package rules.
constexpr bool canonical_tensor_dtype_name(std::string_view name) {
    for (const auto& info : dtype_infos) {
        if (info.quidra_name == name) return true;
    }
    return false;
}

// A numeric dtype code: an integer or a real, not bool.
constexpr bool numeric_dtype_code(int code) {
    return (code >= QCORE_DTYPE_INT64 && code <= QCORE_DTYPE_FLOAT32) ||
           code == QCORE_DTYPE_FLOAT16 || code == QCORE_DTYPE_BFLOAT16;
}

// A real dtype code: float64, float32, float16 or bfloat16.
constexpr bool real_dtype_code(int code) {
    return code == QCORE_DTYPE_FLOAT64 || code == QCORE_DTYPE_FLOAT32 ||
           code == QCORE_DTYPE_FLOAT16 || code == QCORE_DTYPE_BFLOAT16;
}

// A complex dtype code: complex16, complex16b, complex32 or complex64.
constexpr bool complex_dtype_code(int code) {
    return code >= QCORE_DTYPE_COMPLEX_FLOAT16 && code <= QCORE_DTYPE_COMPLEX_FLOAT64;
}

// The real dtype of each part of a complex dtype, or the dtype itself.
constexpr int complex_part_dtype_code(int code) {
    switch (code) {
        case QCORE_DTYPE_COMPLEX_FLOAT16: return QCORE_DTYPE_FLOAT16;
        case QCORE_DTYPE_COMPLEX_BFLOAT16: return QCORE_DTYPE_BFLOAT16;
        case QCORE_DTYPE_COMPLEX_FLOAT32: return QCORE_DTYPE_FLOAT32;
        case QCORE_DTYPE_COMPLEX_FLOAT64: return QCORE_DTYPE_FLOAT64;
        default: return code;
    }
}

// The entry of dtype_infos for `dtype` (the table is in code order).
constexpr const DtypeInfo& dtype_info(Dtype dtype) {
    return dtype_infos[static_cast<std::size_t>(dtype_code(dtype) - QCORE_DTYPE_INT64)];
}

static_assert(
    [] {
        for (std::size_t i = 0; i < dtype_infos.size(); ++i) {
            if (dtype_code(dtype_infos[i].dtype) != QCORE_DTYPE_INT64 + static_cast<int>(i)) return false;
        }
        return true;
    }(),
    "dtype_infos is in code order");

// The element kind of a sorted array (quidra_array_sorted): how the runtime
// compares the elements and how wide each one is. The values are numbered on
// their own, not taken from the dtype codes: a kind with a dtype has the value
// of its dtype code, string follows them, and a sortable kind added later
// takes the next free value whatever its dtype code is.
enum class SortElementKind : int {
    int64 = 1,
    int8 = 2,
    int16 = 3,
    int32 = 4,
    uint8 = 5,
    uint16 = 6,
    uint32 = 7,
    uint64 = 8,
    float64 = 9,
    float32 = 10,
    boolean = 11,
    string = 12,
    // The words of the arbitrary-precision integer types int and nat
    // (abi::bare_integer_layout).
    bare_integer = 13,
    // The 16-bit reals, ordered as their values.
    real16 = 14,
    real16b = 15,
};

// The code that crosses the C ABI (the kind parameter of quidra_array_sorted).
constexpr int sort_element_kind_code(SortElementKind kind) { return static_cast<int>(kind); }

} // namespace quidra::abi
