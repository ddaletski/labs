#ifndef LEXER_HPP
#define LEXER_HPP

#include "basic_lexer.hpp"
#include <list>
#include <utility>
#include <regex>
#include <functional>
#include <sstream>


class TokenSpace : public Token {
public:
    std::string description() {
        return "<space>";
    }
};

class TokenNum : public Token {
private:
    double _val;

public:
    TokenNum(const std::string& s) {
        std::istringstream stream(s);
        stream >> _val;
    }

    std::string description() {
        return "<number " + std::to_string(_val) + ">";
    }
};

class TokenId : public Token {
private:
    std::string _name;

public:
    TokenId(const std::string& s) : _name(s) {}

    std::string description() {
        return "<identifier " + _name + ">";
    }
};

class TokenOperation : public Token {
public:
    int priority () { return 0; }
    bool left_assoc() { return false; }
    bool right_assoc() { return false; }
};


class TokenPlus : public TokenOperation {
public:
    std::string description() {
        return "<op +>";
    }
};

class TokenMinus : public TokenOperation {
public:
    std::string description() {
        return "<op ->";
    }
};

class Lexer : public BasicLexer {
public:
    typedef std::function<TokenPtr(const std::string&)> tokenFactory;
    Lexer() {}
    ~Lexer() {}

    std::vector<TokenPtr> tokenize(const std::string &s);

    void addRule(const std::regex& re, const tokenFactory& factory);

private:
    std::vector<std::pair<std::regex, tokenFactory>> rules;
};

#endif // LEXER_HPP
