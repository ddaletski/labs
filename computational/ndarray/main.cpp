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

    int rows = 2, cols = 4, channels = 3;
    int idx = 0;

    NDArray<int> arr({rows, cols, channels});

    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            for(int k = 0; k < channels; ++k) {
                arr({i, j, k}) = idx++;
            }
        }
    }

    std::cout << arr << std::endl;
    double now = clock();
    arr.transpose({0, 2, 1});
    std::cout << arr << std::endl;
    arr.makeContiguous();
    double spent = 1000 * (clock() - now) / CLOCKS_PER_SEC;
    std::cout << "spent: " << spent << std::endl;
    std::cout << arr << std::endl;
    arr.transpose({0, 2, 1});
    std::cout << arr << std::endl;

//
//    std::cout << arr << std::endl;
//
//    arr.transpose({1, 0, 2});
//    std::cout << arr << std::endl;

    /*
    idx = 0;
    NDArray<int> mat({rows, cols});
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            mat({i, j}) = idx++;
        }
    }

//    std::cout << mat << std::endl;
    std::cout << "cont: " << mat.isContiguous() << std::endl;
    std::cout << "shape: " << mat.shape() << std::endl;
    std::cout << "str: " << mat.strides() << std::endl;
    double now = clock();
    mat.transpose({1, 0});
    mat.makeContiguous();
    double spent = 1000 * (clock() - now) / CLOCKS_PER_SEC;
    std::cout << "spent: " << spent << std::endl;
//    std::cout << mat << std::endl;
    std::cout << "cont: " << mat.isContiguous() << std::endl;
    std::cout << "shape: " << mat.shape() << std::endl;
    std::cout << "str: " << mat.strides() << std::endl;
//    std::cout << mat << std::endl;
    std::cout << "cont: " << mat.isContiguous() << std::endl;
    std::cout << "shape: " << mat.shape() << std::endl;
    std::cout << "str: " << mat.strides() << std::endl;

    */
    return 0;
}
