#include "Calculator.hpp"
#include <charconv> // For fast, locale-independent conversion
#include <limits>

namespace calc_pro {

std::expected<double, CalcError> 
Calculator::apply_op(double a, double b, Operator op) noexcept {
    switch (op) {
        case Operator::Add:      return a + b;
        case Operator::Subtract: return a - b;
        case Operator::Multiply: return a * b;
        case Operator::Divide:
            if (b == 0.0) [[unlikely]] return std::unexpected(CalcError::DivisionByZero);
            return a / b;
        default: return std::unexpected(CalcError::InvalidExpression);
    }
}

std::expected<double, CalcError> 
Calculator::evaluate(std::string_view expression) noexcept {
    // Audit Note: Using std::from_chars for security (no buffer overflows)
    double result = 0.0;
    auto [ptr, ec] = std::from_chars(expression.data(), 
                                     expression.data() + expression.size(), 
                                     result);

    if (ec != std::errc{}) {
        return std::unexpected(CalcError::InvalidExpression);
    }

    // This is a simplified evaluator structure for brevity; 
    // real implementation would use a Shunting-yard or Recursive Descent.
    return result; 
}

} // namespace calc_pro