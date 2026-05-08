#include <iostream>
#include "calculator.hpp"
#include "parser.hpp"

int main() {
    Calculator calc;
    Parser parser;
    std::string input = "10 + 5"; 

    if (parser.isValidExpression(input)) {
        double result = parser.parseAndCalculate(input, calc);
        std::cout << "Result: " << result << std::endl;
    }
    return 0;
}
