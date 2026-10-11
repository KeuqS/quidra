#pragma once

#include <algorithm>
#include <cstdint>
#include <limits>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

namespace quidra {

// Exact signed polynomial coefficients, independent of runtime integer boxes.
class ShapeCoefficient {
public:
    ShapeCoefficient() = default;
    explicit ShapeCoefficient(std::int64_t value) : text_(std::to_string(value)) {}
    explicit ShapeCoefficient(std::string text) : text_(std::move(text)) { normalize(); }
    bool zero() const { return text_ == "0"; }
    bool one() const { return text_ == "1"; }
    const std::string& text() const { return text_; }
    bool operator==(const ShapeCoefficient&) const = default;
    ShapeCoefficient operator-() const {
        return zero() ? *this : ShapeCoefficient(negative() ? text_.substr(1) : "-" + text_);
    }
    friend ShapeCoefficient operator+(const ShapeCoefficient& a, const ShapeCoefficient& b) {
        const auto x = a.magnitude(), y = b.magnitude();
        if (a.negative() == b.negative())
            return ShapeCoefficient((a.negative() ? "-" : "") + add(x, y));
        const bool greater = x.size() != y.size() ? x.size() > y.size() : x >= y;
        return ShapeCoefficient(((greater ? a.negative() : b.negative()) ? "-" : "") +
                                (greater ? subtract(x, y) : subtract(y, x)));
    }
    friend ShapeCoefficient operator*(const ShapeCoefficient& a, const ShapeCoefficient& b) {
        const auto x = a.magnitude(), y = b.magnitude();
        std::string out(x.size() + y.size(), '0');
        for (std::size_t i = x.size(); i-- > 0;) {
            unsigned carry = 0;
            for (std::size_t j = y.size(); j-- > 0;) {
                const auto index = i + j + 1;
                const auto sum = unsigned(out[index] - '0') +
                                 unsigned(x[i] - '0') * unsigned(y[j] - '0') + carry;
                out[index] = char('0' + sum % 10); carry = sum / 10;
            }
            out[i] = char(out[i] + carry);
        }
        return ShapeCoefficient((a.negative() != b.negative() ? "-" : "") + out);
    }
    std::optional<std::int64_t> nonnegative_word() const {
        if (negative()) return std::nullopt;
        std::uint64_t value = 0;
        const auto maximum = std::uint64_t(std::numeric_limits<std::int64_t>::max());
        for (const char digit : text_) {
            if (value > (maximum - unsigned(digit - '0')) / 10) return std::nullopt;
            value = value * 10 + unsigned(digit - '0');
        }
        return static_cast<std::int64_t>(value);
    }
private:
    std::string text_{"0"};
    bool negative() const { return text_.front() == '-'; }
    std::string_view magnitude() const { return negative() ? std::string_view(text_).substr(1) : text_; }
    void normalize() {
        const bool sign = !text_.empty() && text_.front() == '-';
        const auto begin = text_.find_first_not_of('0', sign ? 1 : 0);
        text_ = begin == std::string::npos ? "0" : (sign ? "-" : "") + text_.substr(begin);
    }
    static std::string add(std::string_view a, std::string_view b) {
        std::string out; unsigned carry = 0; std::size_t i = a.size(), j = b.size();
        while (i || j || carry) {
            const unsigned sum = carry + (i ? unsigned(a[--i] - '0') : 0) +
                                         (j ? unsigned(b[--j] - '0') : 0);
            out.push_back(char('0' + sum % 10)); carry = sum / 10;
        }
        std::reverse(out.begin(), out.end()); return out;
    }
    static std::string subtract(std::string_view a, std::string_view b) {
        std::string out; int borrow = 0; std::size_t i = a.size(), j = b.size();
        while (i) {
            int difference = int(a[--i] - '0') - borrow - (j ? int(b[--j] - '0') : 0);
            borrow = difference < 0;
            if (borrow) difference += 10;
            out.push_back(char('0' + difference));
        }
        std::reverse(out.begin(), out.end()); return out;
    }
};

} // namespace quidra
