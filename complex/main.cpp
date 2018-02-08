#include <iostream>
#include "complex.h"
#include <sstream>
#include <string>


Complex::Complex from_s(const std::string& s) {
    Complex::Complex c;
    std::istringstream stream(s);
    stream >> c;
    return c;
}


int main() {
    auto x = from_s("1 + 3 * i") * from_s("-1+1*i");
    auto y = from_s("10 - 2*i") / from_s("2 + 1*i");
    std::cout << x << " + " << y << " = " << (x + y) << std::endl;
    return 0;
}
