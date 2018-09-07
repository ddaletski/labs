#include <ndarray.h>
#include <iostream>

template<template<class, class> class SeqType, class ItemType, class Alloc=std::allocator<ItemType>>
std::ostream& operator << (std::ostream& str, const SeqType<ItemType, Alloc>& seq) {
    str << "[ ";
    for(auto obj : seq) {
        str << obj << " ";
    }
    str << "]";
    return str;
}

int main() {
	std::cout << std::endl;
    NDArray<int> arr({2, 3, 4});
    std::cout << arr << std::endl;
    std::cout << arr.count() << std::endl;

    arr({0, 0, 0}) = 1;

    std::cout << arr << std::endl;

    NDArray<int> copy = arr;

    std::cout << "copy: " << copy << std::endl;
    std::cout << "orig: " << arr << std::endl;

    NDArray<int> moved = std::move(arr);

    std::cout << "moved: " << moved << std::endl;

    std::cout << moved.shape() << std::endl;
    std::cout << arr.shape() << std::endl;

    std::cout << moved.max(-1) << std::endl;
    return 0;
}
