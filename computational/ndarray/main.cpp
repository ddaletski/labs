#include <ndarray.h>
#include <iostream>


int main() {
	std::cout << std::endl;
    NDArray<int> arr({2, 3, 4}, 2);
    std::cout << arr << std::endl;
    std::cout << arr.count() << std::endl;

    arr({1, 1, 0}) = 1;
    std::cout << arr << std::endl;
    return 0;
}
