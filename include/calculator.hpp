#pragma once

#include <string_view>
#include <expected>
#include <string>
#include <numbers>

namespace calc_pro {

// Strong typing for operators to prevent implicit conversions
enum class Operator : char {
    Add      = '+',
    Subtract = '-',
    Multiply = '*',
    Divide   = '/',
    None     = '\0'
};

// Domain-specific error types
enum class CalcError {
    InvalidExpression,
    DivisionByZero,
    Overflow
};

class Calculator {
public:
    // Constants using modern constexpr and std::numbers
    static constexpr double PI = std::numbers::pi;
    static constexpr double E  = std::numbers::e;

    /**
     * @brief Evaluates a mathematical expression safely.
     * @param expression Non-owning view of the input string.
     * @return Result or a typed error.
     */
    [[nodiscard]] static std::expected<double, CalcError> 
    evaluate(std::string_view expression) noexcept;

private:
    // Internal helper for safe arithmetic
    static std::expected<double, CalcError> 
    apply_op(double a, double b, Operator op) noexcept;
};

} // namespace calc_pro