#include <iostream>
#include <cassert>
#include <stdexcept>
#include "calculator.hpp"
#include "parser.hpp"

// --- Calculator Tests ---

void test_calculator_operations() {
    Calculator calc;
    
    // Standard operations
    assert(calc.add(10, 5) == 15);
    assert(calc.subtract(10, 5) == 5);
    assert(calc.multiply(10, 5) == 50);
    assert(calc.divide(10, 5) == 2);
    
    // Floating point / negative checks
    assert(calc.add(-1, -1) == -2);
    assert(calc.multiply(2.5, 2) == 5.0);

    // Edge Case: Division by zero
    try {
        calc.divide(10, 0);
        assert(false); // Should not reach here
    } catch (const std::runtime_error& e) {
        std::cout << "Caught expected division by zero exception." << std::endl;
    }
    
    std::cout << "[PASS] Calculator Operations" << std::endl;
}

// --- Parser Tests ---

void test_parser_validation() {
    Parser parser;
    
    // Valid expressions
    assert(parser.isValidExpression("10 + 5") == true);
    assert(parser.isValidExpression("100/2") == true);
    assert(parser.isValidExpression("  3 * 4  ") == true);
    
    // Invalid expressions (Chaos Agent might inject these)
    assert(parser.isValidExpression("10 @ 5") == false); // Invalid character
    assert(parser.isValidExpression("hello world") == false);
    assert(parser.isValidExpression("") == false);
    
    std::cout << "[PASS] Parser Validation" << std::endl;
}

void test_parser_calculation() {
    Calculator calc;
    Parser parser;
    
    // Check if the parser correctly calls the calculator
    assert(parser.parseAndCalculate("20 + 20", calc) == 40.0);
    assert(parser.parseAndCalculate("50 - 10", calc) == 40.0);
    assert(parser.parseAndCalculate("8 * 5", calc) == 40.0);
    assert(parser.parseAndCalculate("160 / 4", calc) == 40.0);
    
    // Malformed input handling
    assert(parser.parseAndCalculate("invalid", calc) == 0.0);
    
    std::cout << "[PASS] Parser Calculation Integration" << std::endl;
}

int main() {
    try {
        std::cout << "Starting Test Suite..." << std::endl;
        
        test_calculator_operations();
        test_parser_validation();
        test_parser_calculation();
        
        std::cout << "\nALL SCENARIOS PASSED SUCCESSFULLY!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\nTEST SUITE FAILED: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
