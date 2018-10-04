#include "deconv.hpp"
#include <iostream>

using namespace Tensor;

template <class T>
Tensor3D<T> deconv(const Tensor3D<T>& tensor) {
    auto top_bottom = tensor.dsplit();
    auto top = top_bottom.first;
    auto bottom = top_bottom.second.rotate_around_x().rotate_around_x();

    auto tensor2 = top.vstack(bottom);

    top_bottom = tensor2.dsplit();
    top = top_bottom.first;
    bottom = top_bottom.second.rotate_around_y().rotate_around_y();

    auto tensor3 = top.hstack(bottom);

    return tensor3;
}

int main(int argc, char *argv[]) {
    uint N = 16;
    Tensor3D<int> tensor(1, 1, N);
    std::cout << "start" << std::endl;

    for(int k = 0; k < N; ++k) 
        tensor.at(0, 0, k) = k + 1;

    std::cout << tensor << std::endl << std::endl;

    while(tensor.d3() > 1) 
        tensor = deconv(tensor);

    std::cout << tensor << std::endl;

    return 0;
}
