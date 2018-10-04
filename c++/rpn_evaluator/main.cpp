#include <iostream>
#include "rpnparser.hpp"

int main() {
    RpnParser parser;
    try {
        std::cout << parser.to_polish("10 + (234.5 - 123) * 2 - 3 ^ 5") << std::endl;
    } catch (const char* s) {
        std::cout << s << std::endl;
    }
    return 0;
}
