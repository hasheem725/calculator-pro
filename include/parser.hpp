#ifndef PARSER_HPP
#define PARSER_HPP
#include <string>

class Parser {
public:
    bool isValidExpression(const std::string& expr);
    double parseAndCalculate(const std::string& expr, class Calculator& calc);
};

#endif