#include "rpnparser.hpp"
#include <iostream>
#include <stack>
#include <typeinfo>
#include <functional>

RpnParser::RpnParser() {
    lexer.addRule(
                std::regex("\\d+(\\.\\d*)?"),
                [](const std::string& s) { return std::shared_ptr<Token>{new TokenNum(s)};}
    );

    lexer.addRule(
                std::regex("\\s+"),
                [](const std::string& s) { return std::shared_ptr<Token>{new TokenSpace()};}
    );

    lexer.addRule(
                std::regex("\\+"),
                [](const std::string& s) { return std::shared_ptr<Token>{new TokenPlus};}
    );

    lexer.addRule(
                std::regex("-"),
                [](const std::string& s) { return std::shared_ptr<Token>{new TokenMinus};}
    );

    lexer.addRule(
                std::regex("\\*"),
                [](const std::string& s) { return std::shared_ptr<Token>{new TokenMul};}
    );

    lexer.addRule(
                std::regex("/"),
                [](const std::string& s) { return std::shared_ptr<Token>{new TokenDiv};}
    );

    lexer.addRule(
                std::regex("\\^"),
                [](const std::string& s) { return std::shared_ptr<Token>{new TokenPow};}
    );

    lexer.addRule(
                std::regex("\\("),
                [](const std::string& s) { return std::shared_ptr<Token>{new TokenParenLeft};}
    );

    lexer.addRule(
                std::regex("\\)"),
                [](const std::string& s) { return std::shared_ptr<Token>{new TokenParenRight};}
    );
}

std::string RpnParser::to_polish(const std::string& s) {
    std::ostringstream result;

    std::vector<TokenPtr> tokens = lexer.tokenize(s);

    std::stack<TokenPtr> stack;

    for (auto tokenPtr : tokens) {
        std::string token_str = tokenPtr->to_str();

        if(typeid(*tokenPtr) == typeid(TokenNum)) {
            result << " " << token_str;
        } else if (dynamic_cast<TokenOperation*>(tokenPtr.get())) {
            auto op_ptr = dynamic_cast<TokenOperation*>(tokenPtr.get());
            std::function<bool(int, int)> cmp;

            if (op_ptr->right_assoc()) {
                cmp = std::less<int>();
            } else {
                cmp = std::less_equal<int>();
            }

            while(!stack.empty()) {
                auto other_op_ptr = dynamic_cast<TokenOperation*>(stack.top().get());
                if (other_op_ptr == nullptr)
                    break;
                if (cmp(op_ptr->priority(), other_op_ptr->priority())) {
                    result << " " << (*other_op_ptr);
                    stack.pop();
                } else {
                    break;
                }
            }
            stack.push(tokenPtr);

        } else if (token_str == "(") {
            stack.push(tokenPtr);
        } else if (token_str == ")") {
            while(true) {
                auto sym = stack.top()->to_str();
                stack.pop();
                if (sym == "(")
                    break;
                else
                    result << " " << sym;
                if (stack.empty())
                    throw SyntaxError(s);
            }
        }
    }

    while (!stack.empty()) {
        auto sym = dynamic_cast<TokenOperation*>(stack.top().get());
        stack.pop();
        if (sym == nullptr)
            throw SyntaxError(s);
        result << " " << (*sym);
    }

    return result.str();
}


double RpnParser::calculate_polish(const std::string& polish) {
    std::vector<TokenPtr> tokens = lexer.tokenize(polish);
    std::stack<double> stack;

    for (auto tokenPtr : tokens) {
        if (typeid(*tokenPtr) == typeid(TokenNum)) {
            stack.push(dynamic_cast<TokenNum*>(tokenPtr.get())->value());
        } else if (dynamic_cast<TokenOperation*>(tokenPtr.get())) {
            auto op = dynamic_cast<TokenOperation*>(tokenPtr.get());
        } else {
        }
    }

    return 0;
}


double RpnParser::calculate_infix(const std::string& infix) {
    return calculate_polish(to_polish(infix));
}


