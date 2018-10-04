#include <iostream>
#include "charset.h"

int main(int argc, char *argv[])
{
    charSet set1;
    set1 |= make_charset("abcdef");
    charSet set2;
    set2 = set1;
    std::cout << set1 << std::endl;
    std::cout << set2 << std::endl;

    set1 << '0' << '1';
    set2 << '%' << '$';

    std::cout << "set1:\n" << set1 << "\nset2:\n" << set2 << "\n";
    charSet set3 = set1 & set2;
    std::cout << "1 & 2\n" << set3 << std::endl;

    std::string s = "asdfghj";
    charSet set5 = s;
    std::cout << "set5:\n" << set5 << std::endl;
    std::cout << "\033[1;32mDone\033[m\n";
    return 0;
}
