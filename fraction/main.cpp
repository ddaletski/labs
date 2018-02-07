#include <iostream>
#include "fraction.h"

int main() {
    auto fs = fraction::from_string;
    fraction f = 2 + ((fs("1/2") + fs("3/4") - 2) * 2) * 3;
    std::cout << f << std::endl;
    f++;
    f /= 2;
    std::cout << f << std::endl;

    std::cout << 0.35 * double(f) << std::endl;

//    std::cout << (f < -1) << std::endl;
    return 0;
}
