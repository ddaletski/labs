#include <iostream>
#include "rpnparser.hpp"

int main() {
    RpnParser parser;
    parser.to_polish("10 + 234.5 - 123");
    return 0;
}
