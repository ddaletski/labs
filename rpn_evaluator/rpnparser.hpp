#ifndef RPNPARSER_HPP
#define RPNPARSER_HPP
#include <string>
#include <exception>
#include "lexer.hpp"

class SyntaxError : std::exception {
    private:
        std::string _info;
    public:
        SyntaxError(const std::string arg) {
            _info = "syntax error at '" + arg + "'";
        }

        virtual const char* what() const noexcept {
            return _info.c_str();
        }
};

class RpnParser {
public:
    RpnParser();

    std::string to_polish(const std::string& s);
    double calculate_polish(const std::string& polish);
    double calculate_infix(const std::string& infix);

private:
    Lexer lexer;
};

#endif // RPNPARSER_HPP
