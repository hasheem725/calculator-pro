#include "parser.hpp"
#include <charconv>

namespace calc_pro {

double BinaryOpNode::evaluate() const {
    double l_val = left->evaluate();
    double r_val = right->evaluate();

    switch (op) {
        case Operator::Add:      return l_val + r_val;
        case Operator::Subtract: return l_val - r_val;
        case Operator::Multiply: return l_val * r_val;
        case Operator::Divide:
            // Security check for division by zero at the AST level
            if (r_val == 0.0) throw std::runtime_error("Division by zero");
            return l_val / r_val;
        default: return 0.0;
    }
}

void Parser::skip_whitespace() {
    while (pos < input.size() && std::isspace(input[pos])) {
        pos++;
    }
}

std::expected<std::unique_ptr<Node>, CalcError> Parser::parse() noexcept {
    try {
        auto root = parse_expression();
        if (pos < input.size()) return std::unexpected(CalcError::InvalidExpression);
        return std::move(root);
    } catch (...) {
        return std::unexpected(CalcError::InvalidExpression);
    }
}

std::unique_ptr<Node> Parser::parse_factor() {
    skip_whitespace();
    
    // Handle numbers
    double value = 0;
    auto [ptr, ec] = std::from_chars(input.data() + pos, input.data() + input.size(), value);
    
    if (ec == std::errc{}) {
        pos = static_cast<size_t>(ptr - input.data());
        return std::make_unique<NumberNode>(value);
    }
    
    // Handle parentheses for complex expressions
    if (pos < input.size() && input[pos] == '(') {
        pos++;
        auto node = parse_expression();
        if (pos < input.size() && input[pos] == ')') {
            pos++;
            return node;
        }
    }

    throw std::runtime_error("Parse error at factor");
}

std::unique_ptr<Node> Parser::parse_term() {
    auto node = parse_factor();
    skip_whitespace();

    while (pos < input.size() && (input[pos] == '*' || input[pos] == '/')) {
        char op_char = input[pos++];
        auto right = parse_factor();
        node = std::make_unique<BinaryOpNode>(
            std::move(node), 
            std::move(right), 
            static_cast<Operator>(op_char)
        );
        skip_whitespace();
    }
    return node;
}

std::unique_ptr<Node> Parser::parse_expression() {
    auto node = parse_term();
    skip_whitespace();

    while (pos < input.size() && (input[pos] == '+' || input[pos] == '-')) {
        char op_char = input[pos++];
        auto right = parse_term();
        node = std::make_unique<BinaryOpNode>(
            std::move(node), 
            std::move(right), 
            static_cast<Operator>(op_char)
        );
        skip_whitespace();
    }
    return node;
}

} // namespace calc_pro