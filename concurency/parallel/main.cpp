#include <iostream>
#include <numeric>
#include <thread>
#include <chrono>
#include <vector>
#include <cmath>
#include <functional>

template<class Func, class ... Args>
double timeit(Func f, Args ... args) {
    using hrc = std::chrono::high_resolution_clock;

    auto start = hrc::now();
    f(args...);
    auto end = hrc::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}


template<class Iterator, class T, class BinaryOp>
void accumulate_sequential(T& result, Iterator first, Iterator last, const T& init, BinaryOp op) {
    result = init;

    for(auto it = first; it != last; ++it) {
        result = op(result, *it);
    }
}


template<class Iterator, class T, class BinaryOp>
T accumulate_parallel(Iterator first, Iterator last, const T& init, BinaryOp op) {
    size_t elems_count = std::distance(first, last);
    size_t threads_count = std::max(int(std::thread::hardware_concurrency()), 4);
    size_t block_size = ceil(1.0 * elems_count / threads_count);

    std::vector<std::thread> threads;

    Iterator block_start = first;
    Iterator block_end = first;
    std::vector<T> results(threads_count);

    auto result_it = results.begin();

    for(size_t i = 0; i < threads_count-1; ++i) {
        std::advance(block_end, block_size);
        threads.emplace_back(accumulate_sequential<Iterator, T, BinaryOp>, std::ref(*result_it), block_start, block_end, init, op);
        block_start = block_end;
        ++result_it;
    }
    threads.emplace_back(accumulate_sequential<Iterator, T, BinaryOp>, std::ref(*result_it), block_start, last, init, op);

    for(auto it = threads.begin(); it != threads.end(); ++it) {
        it->join();
    }

    T result = init;
    accumulate_sequential(result, results.begin(), results.end(), init, op);

    return result;
}

typedef double MyType;

MyType f(MyType x, MyType y) {
    return pow(pow(x, 5) + pow(y, 5), 1.0 / 6);
}


int main() {
    for(MyType elems_count = 1e3; elems_count <= 1e8; elems_count *= 10) {
        std::cout << "elems count: " << elems_count << std::endl;

        std::vector<MyType> vec(elems_count);
        for(MyType i = 0; i < elems_count; ++i) {
            vec[i] = rand() % 100;
        }

        MyType result = 1;
        MyType initial_value = 1;

        double spent_seq = timeit(accumulate_sequential<decltype(vec.begin()), MyType, std::function<MyType(MyType, MyType)>>, result, vec.begin(), vec.end(), initial_value, f);
        std::cout << "---\n";
        double spent_parallel = timeit(accumulate_parallel<decltype(vec.begin()), MyType, std::function<MyType(MyType, MyType)>>, vec.begin(), vec.end(), initial_value, f);

        std::cout << "(" << spent_seq << " | " << spent_parallel << ")" << std::endl;

        std::cout << std::endl;
    }

    return 0;
}
