#ifndef BASIC_LEXER_HPP
#define BASIC_LEXER_HPP

#include <vector>

class Token {
public:
    virtual std::string description() = 0;
};

typedef std::shared_ptr<Token> TokenPtr;


class BasicLexer {
public:
    virtual std::vector<TokenPtr> tokenize(const std::string& s) = 0;
};


#endif
