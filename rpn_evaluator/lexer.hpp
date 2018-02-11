#ifndef LEXER_HPP
#define LEXER_HPP

#include "basic_lexer.hpp"
#include <vector>
#include <utility>
#include <regex>
#include <functional>
#include <sstream>
#include <exception>

class LexicalAmbiguity : std::exception {
private:
    std::string message;
public:
    LexicalAmbiguity(const std::string& str) {
    }
};

class LexicalError : std::exception {

};


class TokenSpace : public Token {
public:
    std::string to_str() const {
        return " ";
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

    std::string to_str() const {
        return std::to_string(_val);
    }

    double value() {
        return _val;
    }
};

class TokenId : public Token {
private:
    std::string _name;

public:
    TokenId(const std::string& s) : _name(s) {}

    std::string to_str() const {
        return _name;
    }

    std::string name() {
        return _name;
    }
};

class TokenOperation : public Token {
public:
    virtual int priority() const { return 0; }
    virtual bool right_assoc() const { return false; }
};


class TokenPlus : public TokenOperation {
public:
    std::string to_str() const {
        return "+";
    }
    int priority() const { return 0; }
};

class TokenMinus : public TokenOperation {
public:
    std::string to_str() const {
        return "-";
    }
    int priority() const { return 0; }
};

class TokenMul : public TokenOperation {
public:
    std::string to_str() const {
        return "*";
    }
    int priority() const { return 1; }
};

class TokenDiv : public TokenOperation {
public:
    std::string to_str() const {
        return "/";
    }
    int priority() const { return 1; }
};

class TokenPow : public TokenOperation {
public:
    std::string to_str() const {
        return "^";
    }
    int priority() const { return 2; }
    bool right_assoc() const { return true; }
};


class TokenParenLeft : public Token {
public:
    std::string to_str() const {
        return "(";
    }
};

class TokenParenRight : public Token {
public:
    std::string to_str() const {
        return ")";
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
