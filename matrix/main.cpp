#include <iostream>
#include "matrix.h"


int main()
{
    ///////////////////////////////////////////////////////////////////
    // just change dimensions of matrices to see exception handling

    matrix<int> m(3, 3, [](uint i, uint j) {return int(i + j);});
    matrix<int> m1(3, 3, 3);
    matrix<int> m2 (3 ,3, 1);
    auto m3 = m2;

    //////////////////////////////////////////////////////////////////
    // arithmetic operations

    std::cout << "m:\n" << m << "m1:\n" << m1 << "m2:\n" << m2 << "\n";
    try {
        m3 = m1 + m + m2;
        m *= 2;
        m1 = 4 * m1 / 2;
    } catch (WrongDimensionException& ex) {
        std::cout << "\033[1;31m" << ex.what() << "\033[m\n";
    }
    std::cout << "after operations\n";
    std::cout << "m:\n" << m << "m1:\n" << m1 << "m2:\n" << m2 << "m3:\n" << m3 << "\n";

    ///////////////////////////////////////////////////////////////////////////////////
    // identifiers

    std::cout << "ID's:\n";
    std::cout << m.getID() << " " << m1.getID() << " " << m2.getID() << " " << m3.getID() << std::endl;
    std::cout << "count of available objects:\n";
    std::cout << matrix<int>::get_count_of_instances() << "\n\n";

    ///////////////////////////////////////////////////////////////////////////////////
    // matrix product

    matrix<int> A(3, 3, [](uint i, uint j) {return int(i < j ? i : j) + 1;});
    matrix<int> B(2, 4, 2);

    try {
    std::cout << "A = \n" << A << std::endl;
    std::cout << "B = \n" << B << std::endl;
    std::cout << "AB = \n" << A * B << std::endl;
    } catch (WrongDimensionException& ex) {
        std::cout << ex.what() << std::endl;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    // input operator

    m.fill_console();
    std::cout << "result:\n" << m << std::endl;

    ////////////////////////////////////////////////////////////////////////////////////
    // zero division

    try {
        std::cout << m / 0 << std::endl;
    } catch (ZeroDivisionException& ex) {
        std::cout << "\033[1;31m" <<  ex.what() << "\033[m\n";
    }

    /////////////////////////////////////////////////////////////////////////////////////
    // unary -
    std::cout << "A = \n" << A << "\n-A = \n" << -A << "\n";

    std::cout << "\033[1;32mdone\033[m\n";
    return 0;
}
