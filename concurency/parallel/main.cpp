#include <iostream>
#include <numeric>
#include <thread>
#include <chrono>
#include <vector>
#include <cmath>
#include <functional>

template<class Func, class ... Args>
double timeit(Func f, Args ... args) {
    double start = clock();

    f(args...);

    return 1.0 * (clock() - start) / CLOCKS_PER_SEC;
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

    for(size_t i = 0; i < threads_count-1; ++i) {
        std::advance(block_end, block_size);
        threads.emplace_back(accumulate_sequential<Iterator, T, BinaryOp>, std::ref(results[i]), block_start, block_end, init, op);
        block_start = block_end;
    }
    threads.emplace_back(accumulate_sequential<Iterator, T, BinaryOp>, std::ref(results.back()), block_start, last, init, op);

    for(auto it = threads.begin(); it != threads.end(); ++it) {
        it->join();
    }

    T result = init;
    accumulate_sequential(result, results.begin(), results.end(), init, op);

    return result;
}


int main() {
    for(int elems_count = 1e3; elems_count <= 1e9; elems_count *= 10) {
        std::cout << "elems count: " << elems_count << std::endl;

        std::vector<int> vec(elems_count);
        for(int i = 0; i < elems_count; ++i) {
            vec[i] = rand() % 100;
        }

        int result = 1;

        accumulate_sequential(result, vec.begin(), vec.end(), 0, std::plus<int>());
        int parallel_result = accumulate_parallel(vec.begin(), vec.end(), 0, std::plus<int>());

        std::cout << result << " | " << parallel_result << std::endl;

        double spent_seq = timeit(accumulate_sequential<decltype(vec.begin()), int, std::function<int(int, int)>>, result, vec.begin(), vec.end(), 0, std::plus<int>());
        double spent_parallel = timeit(accumulate_parallel<decltype(vec.begin()), int, std::function<int(int, int)>>, vec.begin(), vec.end(), 0, std::plus<int>());

        std::cout << "(" << spent_seq << " | " << spent_parallel << ")" << std::endl;
    }

    return 0;
}
