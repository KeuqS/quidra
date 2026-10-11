#pragma once

#include "constant_numeric_eval.hpp"
#include "quidra/ast.hpp"
#include "quidra/shape_coefficient.hpp"
#include <bit>
#include <optional>
#include <utility>

namespace quidra::for_constants {
using Integer=ShapeCoefficient;
inline bool negative(const Integer& value) {return value.text().front()=='-';}
inline Integer absolute(const Integer& value) {return negative(value)?-value:value;}
inline int compare(const Integer& a,const Integer& b) {
    if(negative(a)!=negative(b)) return negative(a)?-1:1;
    const auto x=absolute(a).text(),y=absolute(b).text();
    const int result=x.size()!=y.size()?(x.size()<y.size()?-1:1):x==y?0:x<y?-1:1;
    return negative(a)?-result:result;
}
inline std::pair<Integer,Integer> divide_nonnegative(const Integer& a,const Integer& b) {
    Integer remainder;std::string quotient;
    for(const char digit:a.text()) {
        remainder=remainder*Integer(10)+Integer(digit-'0');
        unsigned value=0;
        while(compare(remainder,b)>=0) {remainder=remainder+-b;++value;}
        quotient.push_back(char('0'+value));
    }
    return {Integer(quotient),remainder};
}
inline std::optional<Integer> integer_literal(const Expr& expression) {
    if(const auto* value=std::get_if<IntegerExpr>(&expression.data))
        return Integer(value->spelling.empty()?std::to_string(value->value):value->spelling);
    if(const auto* value=std::get_if<UnaryExpr>(&expression.data);value&&value->op=="-")
        if(auto operand=integer_literal(*value->operand)) return -*operand;
    return std::nullopt;
}
struct Rational {Integer numerator;Integer denominator{1};};
inline std::optional<Rational> exact_literal(const Expr& expression) {
    if(const auto integer=integer_literal(expression)) return Rational{*integer,Integer(1)};
    if(const auto* value=std::get_if<RealLiteralExpr>(&expression.data)) {
        ieee_decimal::Decimal decimal;
        if(!ieee_decimal::parse(value->spelling,decimal)) return std::nullopt;
        const auto power=decimal.exponent-static_cast<long long>(decimal.fraction_digits.size());
        if(power>4096||power< -4096) return std::nullopt;
        std::string digits(decimal.integer_digits);digits+=decimal.fraction_digits;
        Rational result{Integer(digits),Integer(1)};
        for(long long i=0;i<(power<0?-power:power);++i)
            if(power<0) result.denominator=result.denominator*Integer(10);
            else result.numerator=result.numerator*Integer(10);
        if(decimal.negative) result.numerator=-result.numerator;
        return result;
    }
    if(const auto* unary=std::get_if<UnaryExpr>(&expression.data);unary&&unary->op=="-")
        if(auto result=exact_literal(*unary->operand)) {result->numerator=-result->numerator;return result;}
    return std::nullopt;
}
inline Integer gcd(Integer a,Integer b) {
    while(!b.zero()) {auto r=divide_nonnegative(a,b).second;a=b;b=r;}
    return a;
}
inline bool signed_word(const Integer& value) {
    return compare(value,Integer("-9223372036854775808"))>=0&&
           compare(value,Integer("9223372036854775807"))<=0;
}
inline Rational dyadic(double value) {
    const auto bits=std::bit_cast<std::uint64_t>(value);
    const auto exponent=(bits>>52)&2047;
    const auto fraction=bits&((std::uint64_t{1}<<52)-1);
    auto numerator=Integer(std::to_string(exponent?(std::uint64_t{1}<<52)|fraction:fraction));
    Integer denominator(1);
    int power=exponent?int(exponent)-1023-52:-1074;
    for(int i=0;i<(power<0?-power:power);++i)
        if(power<0) denominator=denominator*Integer(2);
        else numerator=numerator*Integer(2);
    if(bits>>63) numerator=-numerator;
    return {numerator,denominator};
}
inline std::optional<Rational> fixed_literal(const Expr& expression,const Type& type,bool implicit_zero=false) {
    if(const auto value=integer_literal(expression);implicit_zero && value && value->zero())
        return Rational{*value,Integer(1)};
    if(const auto* value=std::get_if<RealLiteralExpr>(&expression.data)) {
        if(auto materialized=constant_eval::real_literal_value(value->spelling,type)) return dyadic(*materialized);
    }
    if(const auto* value=std::get_if<UnaryExpr>(&expression.data);value&&value->op=="-")
        if(auto operand=fixed_literal(*value->operand,type)) {
            operand->numerator=-operand->numerator;return operand;
        }
    return std::nullopt;
}
inline std::optional<Integer> count(const Rational& start,const Rational& end,const Rational& step,
                                    bool descending,bool start_inclusive,bool end_inclusive) {
    if(step.numerator.zero()||negative(step.numerator)!=descending) return std::nullopt;
    auto distance=(end.numerator*start.denominator)+-(start.numerator*end.denominator);
    if(descending) distance=-distance;
    if(negative(distance)||(!end_inclusive&&distance.zero())) return Integer(0);
    const auto numerator=distance*step.denominator;
    const auto denominator=start.denominator*end.denominator*absolute(step.numerator);
    auto [whole,remainder]=divide_nonnegative(numerator,denominator);
    if(end_inclusive||!remainder.zero()) whole=whole+Integer(1);
    if(!start_inclusive&&!whole.zero()) whole=whole+Integer(-1);
    return whole;
}
inline std::optional<Integer> integer_discard_count(const ForStmt& loop) {
    auto start=integer_literal(*loop.iterable),end=integer_literal(*loop.range->end);
    auto step=loop.range->step?integer_literal(*loop.range->step):
        std::optional<Integer>{Integer(loop.range->descending?-1:1)};
    if(!start||!end||!step) return std::nullopt;
    return count({*start,Integer(1)},{*end,Integer(1)},{*step,Integer(1)},
        loop.range->descending,loop.range->start_inclusive,loop.range->end_inclusive);
}
}
