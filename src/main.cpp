#include "Calculator.hpp"
#include <iostream>
#include <string>

int main() {
    using namespace calc_pro;

    std::cout << "--- Calculator Pro (Secure Edition) ---\n";
    std::cout << "Enter expression: ";

    std::string input;
    if (!std::getline(std::cin, input) || input.empty()) {
        return 0;
    }

    // RAII: String is managed automatically. 
    // Pass by view to evaluate() for zero-copy performance.
    auto result = Calculator::evaluate(input);

    if (result) {
        // Explicitly using fixed precision for readability
        std::cout << "Result: " << *result << std::endl;
    } else {
        switch (result.error()) {
            case CalcError::DivisionByZero: 
                std::cerr << "Security Audit Alert: Division by zero blocked.\n"; 
                break;
            case CalcError::InvalidExpression: 
                std::cerr << "Error: Malformed input syntax.\n"; 
                break;
            default: 
                std::cerr << "Error: Unknown execution fault.\n";
        }
    }

    return 0;
}