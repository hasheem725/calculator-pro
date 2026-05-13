#pragma once

#include <memory>
#include <string_view>
#include <expected>
#include "Calculator.hpp"

namespace calc_pro {

// Base class for AST nodes
class Node {
public:
    virtual ~Node() = default;
    [[nodiscard]] virtual double evaluate() const = 0;
};

// Leaf node representing a numeric value
class NumberNode : public Node {
    double value;
public:
    explicit NumberNode(double val) : value(val) {}
    double evaluate() const override { return value; }
};

// Node representing a binary operation (+, -, *, /)
class BinaryOpNode : public Node {
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Operator op;

public:
    BinaryOpNode(std::unique_ptr<Node> l, std::unique_ptr<Node> r, Operator o)
        : left(std::move(l)), right(std::move(r)), op(o) {}

    double evaluate() const override;
};

class Parser {
public:
    explicit Parser(std::string_view expression) : input(expression) {}

    // Audit Note: Returns a unique_ptr to ensure the caller owns the memory safety
    [[nodiscard]] std::expected<std::unique_ptr<Node>, CalcError> parse() noexcept;

private:
    std::string_view input;
    size_t pos{0};

    // Recursive descent methods
    std::unique_ptr<Node> parse_expression();
    std::unique_ptr<Node> parse_term();
    std::unique_ptr<Node> parse_factor();
    void skip_whitespace();
};

} // namespace calc_pro