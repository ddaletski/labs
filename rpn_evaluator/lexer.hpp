#ifndef LEXER_HPP
#define LEXER_HPP

#include "basic_lexer.hpp"
#include <list>
#include <utility>
#include <regex>

class TokenNum : public Token {
    std::string description() {
        return "<number>";
    }
};

class TokenId : public Token {
    std::string description() {
        return "<identifier>";
    }
};

class TokenOperation : public Token { };

class TokenPlus : public TokenOperation {
    std::string description() {
        return "op+";
    }
};

class TokenMinus : public TokenOperation {
    std::string description() {
        return "op-";
    }
};


class Lexer : public BasicLexer {
public:
    Lexer() {}
    ~Lexer() {}

    std::vector<TokenPtr> tokenize(const std::string &s);
private:
    std::list<std::pair<std::regex, TokenPtr>> rules;
};

#endif // LEXER_HPP
