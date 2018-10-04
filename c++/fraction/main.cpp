#include <iostream>
#include "fraction.h"
#include <functional>

#define fs fraction::from_string

int main() {
    fraction f = 2 + ((fs("1/2") + fs("3/4") - 2) * 2) * fs("3/2");
    std::cout << f << std::endl;
    f /= 2;
    std::cout << f << std::endl;

    std::cout << 35 * f << std::endl;

    std::cout << (-1 < f) << std::endl;
    return 0;
}
