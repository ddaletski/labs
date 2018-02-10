#include "rpnparser.hpp"
#include <iostream>
#include <stack>
#include <typeinfo>

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
                std::regex("\\-"),
                [](const std::string& s) { return std::shared_ptr<Token>{new TokenMinus};}
    );
}

std::string RpnParser::to_polish(const std::string& s) {
    std::vector<TokenPtr> tokens = lexer.tokenize(s);

    std::stack<TokenPtr> stack;

    for (auto tokenPtr : tokens) {
        if(typeid(*tokenPtr) == typeid(TokenNum)) {
            std::cout << "num" << std::endl;
        } else if (typeid(*tokenPtr) == typeid(TokenPlus)) {
            std::cout << "plus" << std::endl;
        } else if (typeid(*tokenPtr) == typeid(TokenMinus)) {
            std::cout << "minus" << std::endl;
        }
    }

    return "";
}
