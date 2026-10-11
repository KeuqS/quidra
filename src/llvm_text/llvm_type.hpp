#pragma once

// LlvmType: the type of an LLVM value or memory slot, as textual IR spells
// it. The set of types is closed: void, the integers i1, i8, i16, i32 and
// i64, float, double, ptr and half (the scalars); an array of a scalar
// ([N x T]); and a structure of two scalars ({ T, U }), the result of an
// overflow intrinsic.
//
// A small value type. The scalars are also named constants in
// llvm_text::types (i64, ptr, ...), for code that writes many operations.
// A type is written by appending its spelling to a text; the element count
// of an array is written in decimal (append_decimal).

#include "llvm_text/appendable_text.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <vector>
#include <utility>

namespace quidra::llvm_text {

class LlvmType {
public:
    enum class Scalar : std::uint8_t { void_type, i1, i8, i16, i32, i64, float_type, double_type, ptr, half_type };

    constexpr LlvmType(Scalar scalar) : shape_(Shape::scalar), first_(scalar) {}

    constexpr LlvmType(const LlvmType& other)
        : shape_(other.shape_), first_(other.first_), second_(other.second_), count_(other.count_),
          elements_(other.elements_ ? new std::vector<LlvmType>(*other.elements_) : nullptr) {}
    constexpr LlvmType(LlvmType&& other) noexcept
        : shape_(other.shape_), first_(other.first_), second_(other.second_), count_(other.count_),
          elements_(std::exchange(other.elements_, nullptr)) {}
    constexpr LlvmType& operator=(const LlvmType& other) {
        if (this != &other) *this = LlvmType(other);
        return *this;
    }
    constexpr LlvmType& operator=(LlvmType&& other) noexcept {
        if (this != &other) {
            if (elements_) delete elements_;
            shape_ = other.shape_; first_ = other.first_; second_ = other.second_; count_ = other.count_;
            elements_ = std::exchange(other.elements_, nullptr);
        }
        return *this;
    }
    constexpr ~LlvmType() { if (elements_) delete elements_; }

    // [count x element], element a scalar.
    static constexpr LlvmType array(std::uint64_t count, LlvmType element) {
        LlvmType type(element.first_);
        type.shape_ = Shape::array;
        type.count_ = count;
        return type;
    }
    // { first, second }, both scalars.
    static constexpr LlvmType structure(LlvmType first, LlvmType second) {
        LlvmType type(first.first_);
        type.shape_ = Shape::structure;
        type.second_ = second.first_;
        return type;
    }

    static LlvmType aggregate(std::vector<LlvmType> elements) {
        LlvmType type(Scalar::void_type);
        type.shape_=Shape::aggregate;
        type.elements_=new std::vector<LlvmType>(std::move(elements));
        return type;
    }

    static constexpr std::string_view spelling(Scalar scalar) {
        constexpr std::array<std::string_view, 10> spellings{"void", "i1",    "i8",     "i16", "i32",
                                                             "i64",  "float", "double", "ptr", "half"};
        return spellings[static_cast<std::size_t>(scalar)];
    }

    // Appends the spelling to a text (a FixedText at compile time).
    template <AppendableText Text>
    constexpr void print(Text& out) const;

    friend constexpr bool operator==(const LlvmType& a, const LlvmType& b) {
        if (a.shape_ != b.shape_ || a.first_ != b.first_ || a.second_ != b.second_ || a.count_ != b.count_) return false;
        if (a.elements_ && b.elements_) return *a.elements_ == *b.elements_;
        return a.elements_ ? a.elements_->empty() : !b.elements_ || b.elements_->empty();
    }

private:
    enum class Shape : std::uint8_t { scalar, array, structure, aggregate };

    Shape shape_;
    Scalar first_;
    Scalar second_{Scalar::void_type};
    std::uint64_t count_{};
    // Keep scalar ABI descriptors literal even with pre-constexpr-vector libraries.
    // Only runtime aggregates allocate; copies retain independent value ownership.
    std::vector<LlvmType>* elements_{};
};

template <AppendableText Text>
constexpr void LlvmType::print(Text& out) const {
    switch (shape_) {
        case Shape::scalar:
            out.append(spelling(first_));
            return;
        case Shape::array:
            out.append("[");
            append_decimal(out, count_);
            out.append(" x ");
            out.append(spelling(first_));
            out.append("]");
            return;
        case Shape::aggregate:
            out.append("{ ");
            for(std::size_t i=0;elements_&&i<elements_->size();++i) {
                if(i) out.append(", ");
                (*elements_)[i].print(out);
            }
            out.append(" }");
            return;
        case Shape::structure:
            out.append("{ ");
            out.append(spelling(first_));
            out.append(", ");
            out.append(spelling(second_));
            out.append(" }");
            return;
    }
}

// The scalar types by their LLVM names.
namespace types {

inline constexpr LlvmType void_type{LlvmType::Scalar::void_type};
inline constexpr LlvmType i1{LlvmType::Scalar::i1};
inline constexpr LlvmType i8{LlvmType::Scalar::i8};
inline constexpr LlvmType i16{LlvmType::Scalar::i16};
inline constexpr LlvmType i32{LlvmType::Scalar::i32};
inline constexpr LlvmType i64{LlvmType::Scalar::i64};
inline constexpr LlvmType float_type{LlvmType::Scalar::float_type};
inline constexpr LlvmType double_type{LlvmType::Scalar::double_type};
inline constexpr LlvmType ptr{LlvmType::Scalar::ptr};
inline constexpr LlvmType half_type{LlvmType::Scalar::half_type};

} // namespace types

} // namespace quidra::llvm_text
