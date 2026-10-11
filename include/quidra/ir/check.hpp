#pragma once

// Typed-IR instructions of the check domain (shape, extent, range,
// iteration and initialization guards; test assertions).
//
// Owns: the domain's instruction structs and their InstructionTraits
// specializations (quidra/ir/domain.hpp). The fields, their order and their
// default member initializers are the IR data model.

#include "quidra/ir/domain.hpp"
#include "quidra/ir/value_id.hpp"
#include "quidra/types.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace quidra::ir {

struct ShapedConstraintCheck {
    ValueId value;
    TypeKind kind{TypeKind::Tensor};
    std::vector<std::optional<ValueId>> extents;
    std::uint32_t line{};
    std::uint32_t column{};
    // L17: for each axis that a shape variable fixes, the variable's name
    // (empty for the other axes; no entries when none), and the binding the
    // value is stored in: a failure names both (SHAPE_MISMATCH).
    std::vector<std::string> shape_variables{};
    std::string subject{};
};
struct ExtentEqualCheck {
    ValueId actual;
    ValueId expected;
    std::uint32_t line{};
    std::uint32_t column{};
    bool for_collection_lengths{};
};
struct TestAssert { ValueId condition; };
struct ForStepCheck { ValueId step; bool descending{}; std::uint32_t line{}; std::uint32_t column{}; };
// A reference loop over a reference binding: the array the binding
// designates now (`array`) is still the array the loop entered with
// (`entry_array`, of length `entry_length`); otherwise FOR_ITERATION at
// line:column.
struct TraversalSiteCheck {ValueId expected;ValueId current;std::uint32_t line{};std::uint32_t column{};};
template <> struct InstructionTraits<TraversalSiteCheck> : InDomain<Domain::check> {};

struct IterationShapeCheck {
    ValueId array;
    ValueId entry_array;
    ValueId entry_length;
    std::uint32_t line{};
    std::uint32_t column{};
};

// What an initialization check reads: a binding, a class field or an
// argument (L13).
enum class InitializedSubject : std::uint8_t { binding, field, argument };
// A read whose initialization is known only at run time: `flag` (a bool)
// is true when the storage named by `path` (as the source writes it) is
// initialized; otherwise UNINITIALIZED at line:column.
struct InitializedCheck {
    ValueId flag;
    InitializedSubject subject{InitializedSubject::binding};
    std::string path;
    std::uint32_t line{};
    std::uint32_t column{};
};

// No value of a fixed-width real type that the program can observe is NaN
// or an infinity (docs/spec/numeric-and-bin.md). The lowering follows every
// real operation that can produce such a value from finite operands with a
// FiniteCheck of its result; the optimizer may merge the checks of one
// expression and sink the check of a loop (optimizer/finite_check_merging).

// The operation that computed a checked value; with its operands it decides
// the failure (REAL_OVERFLOW, or DIVISION_BY_ZERO for a zero divisor).
enum class FiniteCause : std::uint8_t { addition, subtraction, multiplication, division, power };
// A value a finite check tests: the result of one real operation, its type,
// the operation's source location, its cause and its two operands.
struct CheckedReal {
    ValueId value;
    Type type;
    std::uint32_t line{};
    std::uint32_t column{};
    FiniteCause cause{};
    ValueId left{};
    ValueId right{};
};
// Fails unless every value of `primary` is finite. The values of `covered`
// were computed earlier, and each reaches a primary value only through
// operations that keep a non-finite operand non-finite, so they are finite
// when the primary values are; when a check fails, the first non-finite
// value of `covered`, then of `primary`, in program order, is the one
// reported.
struct FiniteCheck {
    std::vector<CheckedReal> primary;
    std::vector<CheckedReal> covered;
};
// The check of a loop's only checked operation, sunk out of the loop: in
// the body, `flag` (a hidden bool local, false at the loop's entry) becomes
// true once `value` is not finite; at the loop's exit, FiniteFlagCheck fails
// as the operation's FiniteCheck would have.
struct FiniteFlagUpdate {
    std::string flag;
    CheckedReal value;
};
struct FiniteFlagCheck {
    std::string flag;
    CheckedReal value;
};

struct ReferenceBoundCheck {
    ValueId address;
    std::string path;
    std::uint32_t line{};
    std::uint32_t column{};
};
struct SelfReferenceCheck {
    ValueId holder_root, target_root;
    std::string holder_path, target_path;
    std::uint32_t line{}, column{};
};
struct StoredTargetsCheck {
    ValueId value;
    Type type;
    ValueId destination_root;
    std::string destination_path;
    std::uint32_t line{}, column{};
};
template <> struct InstructionTraits<SelfReferenceCheck> : InDomain<Domain::check> {};
template <> struct InstructionTraits<StoredTargetsCheck> : InDomain<Domain::check> {};

template <> struct InstructionTraits<ReferenceBoundCheck> : InDomain<Domain::check> {};

template <> struct InstructionTraits<ShapedConstraintCheck> : InDomain<Domain::check> {};
template <> struct InstructionTraits<ExtentEqualCheck> : InDomain<Domain::check> {};
template <> struct InstructionTraits<TestAssert> : InDomain<Domain::check> {};
template <> struct InstructionTraits<ForStepCheck> : InDomain<Domain::check> {};
template <> struct InstructionTraits<IterationShapeCheck> : InDomain<Domain::check> {};
template <> struct InstructionTraits<InitializedCheck> : InDomain<Domain::check> {};
template <> struct InstructionTraits<FiniteCheck> : InDomain<Domain::check> {};
template <> struct InstructionTraits<FiniteFlagUpdate> : InDomain<Domain::check> {};
template <> struct InstructionTraits<FiniteFlagCheck> : InDomain<Domain::check> {};

} // namespace quidra::ir
