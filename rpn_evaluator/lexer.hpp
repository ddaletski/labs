#ifndef LEXER_HPP
#define LEXER_HPP

#include "basic_lexer.hpp"
#include <vector>
#include <utility>
#include <regex>
#include <functional>
#include <sstream>
#include <exception>


class LexicalError : public std::exception {
private:
    std::string _info;
public:
    LexicalError() { _info = "Lexical error"; }
    LexicalError(const std::string& str) {
        _info = "Lexical error at '" + str + "'";
    }
    virtual const char* what() const noexcept {
        return _info.c_str();
    }
};

class LexicalAmbiguity : public LexicalError {
private:
    std::string _info;
public:
    LexicalAmbiguity(const std::string& str) {
        _info = "Ambiuous lexic at '" + str + "'";
    }
    virtual const char* what() const noexcept {
        return _info.c_str();
    }
};

class UnknownToken : public LexicalError {
private:
    std::string _info;
public:
    UnknownToken(const std::string& str) {
        _info = "Unknown token at '" + str + "'";
    }
    virtual const char* what() const noexcept {
        return _info.c_str();
    }
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
        std::ostringstream stream;
        stream << _val;
        return stream.str();
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
