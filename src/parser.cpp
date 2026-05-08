#include "parser.hpp"
#include "calculator.hpp"
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

bool Parser::isValidExpression(const std::string& expr) {
    if (expr.empty()) return false;

    // Check for allowed characters: digits, spaces, and operators (+, -, *, /)
    for (char c : expr) {
        if (!std::isdigit(c) && !std::isspace(c) && 
            c != '+' && c != '-' && c != '*' && c != '/') {
            return false;
        }
    }
    return true;
}

double Parser::parseAndCalculate(const std::string& expr, Calculator& calc) {
    std::stringstream ss(expr);
    double val1, val2;
    char op;

    // Basic parser logic for "Value1 Operator Value2"
    if (!(ss >> val1 >> op >> val2)) {
        return 0.0;
    }

    switch (op) {
        case '+': return calc.add(val1, val2);
        case '-': return calc.subtract(val1, val2);
        case '*': return calc.multiply(val1, val2);
        case '/': return calc.divide(val1, val2);
        default: return 0.0;
    }
}
