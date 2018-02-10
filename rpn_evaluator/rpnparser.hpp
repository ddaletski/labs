#ifndef RPNPARSER_HPP
#define RPNPARSER_HPP
#include <string>
#include "lexer.hpp"

class RpnParser {
public:
    RpnParser();

    std::string to_polish(const std::string& s);

private:
    Lexer lexer;
};

#endif // RPNPARSER_HPP
