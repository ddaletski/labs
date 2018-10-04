#ifndef BASIC_LEXER_HPP
#define BASIC_LEXER_HPP

#include <vector>
#include <memory>

class Token {
public:
    virtual std::string to_str() const = 0;

    friend std::ostream& operator << (std::ostream& str, const Token& t) {
        str << t.to_str();
        return str;
    }
};

typedef std::shared_ptr<Token> TokenPtr;


class BasicLexer {
public:
    virtual std::vector<TokenPtr> tokenize(const std::string& s) = 0;
};


#endif
