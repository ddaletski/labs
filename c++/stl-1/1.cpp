#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <functional>

#define COLORIZE


#ifndef __unix__
    #undef COLORIZE
#endif
#ifdef COLORIZE
    #define COLOR_RED "\033[1;31m"
    #define COLOR_GREEN "\033[1;32m"
    #define COLOR_YELLOW "\033[1;33m"
    #define COLOR_BLUE "\033[1;34m"
    #define COLOR_PURPLE "\033[1;35m"
    #define COLOR_RESET "\033[m"
#else
    #define COLOR_RED ""
    #define COLOR_GREEN ""
    #define COLOR_YELLOW ""
    #define COLOR_BLUE ""
    #define COLOR_PURPLE ""
    #define COLOR_RESET ""
#endif

template<class T>
std::ostream& operator << (std::ostream& stream, const std::vector<T>& v) {
    stream << "[ ";
    for(auto it = v.begin(); it != v.end(); ++it) {
        stream << (*it) << " ";
    }
    stream << "]";
    return stream;
}

int main()
{
    std::vector<int> vec;
    try {
        int num;
        std::string buf;
        std::istringstream converter;
        for(int i = 0; ; ++i) {
            std::cout << "v[" << i << "] = ";
            std::cin >> buf;
            if ((buf[0] < '0' || buf[0] > '9') && buf[0] != '-' && buf[0] != '.')
                break;
            converter.str(buf);
            converter >> num;
            converter.clear();
            vec.push_back(num);
        }
    } catch (...) {

    }

    std::cout << COLOR_GREEN << "Вектор: " << COLOR_RESET << vec << std::endl;

    int sum = std::accumulate(vec.begin(), vec.end(), 0, std::plus<int>());
    std::cout << COLOR_GREEN << "Сумма: " << COLOR_RESET << sum << std::endl;

    std::cout << COLOR_GREEN << "Всего чисел: " << COLOR_RESET << vec.size() << std::endl;

    int m = 4;
    int countOfM = std::count(vec.begin(), vec.end(), m);
    std::cout << COLOR_GREEN << "Чисел = " << COLOR_BLUE << m << COLOR_GREEN << " всего " << COLOR_RESET << countOfM << std::endl;

    int countOfGTM = std::count_if(vec.begin(), vec.end(), std::bind2nd(std::greater<int>(), m));
    std::cout << COLOR_GREEN << "Чисел > " << COLOR_BLUE << m << COLOR_GREEN << " всего " << COLOR_RESET << countOfGTM << std::endl;

    double average = double(sum) / vec.size();
    std::replace(vec.begin(), vec.end(), 0, int(average));
    std::cout << COLOR_GREEN << "Среднее арифметическое: " << COLOR_RESET << average << std::endl;
    std::cout << COLOR_GREEN << "Вектор после замены нулей на [ср. арифм].: " << COLOR_RESET << vec << std::endl;

    size_t interval_start = 0;
    size_t interval_end = vec.size() / 2;
    size_t interval_sum = std::accumulate(vec.begin() + interval_start, vec.begin() + interval_end, 0, std::plus<int>());
    std::for_each(vec.begin(), vec.end(), [&](int& x) { x += interval_sum; });

    std::cout << COLOR_GREEN <<
                 "Сумма элементов вектора из интервала [" <<
                 interval_start << ", " << interval_end << ") = " <<
                 COLOR_RESET << interval_sum << std::endl;

    std::cout << COLOR_GREEN <<
                 "Вектор после прибавления к каждому эелементу этой суммы: " <<
                 COLOR_RESET << vec << std::endl;


    int max = *std::max_element(vec.begin(), vec.end());
    int min = *std::min_element(vec.begin(), vec.end());

    std::cout << COLOR_GREEN <<
                 "Минимальное и максимальное значения вектора: " <<
                 COLOR_RESET << min << ", " << max << std::endl;

    std::replace_if(vec.begin(), vec.end(), [](int& x) { return x%2==0; }, max-min);
    std::cout << COLOR_GREEN <<
                 "Вектор после замены четных чисел на разность максимального и минимального значений: " <<
                 COLOR_RESET << vec << std::endl;

    auto end = vec.end();
    for (auto it = vec.begin(); it < end; ++it) {
        end = std::remove(it+1, end, *it);
        end = std::remove(it+1, end, -(*it));
    }
    vec = std::vector<int>(vec.begin(), end);

    std::cout << COLOR_GREEN <<
                 "Вектор после удаления повторений: " <<
                 COLOR_RESET << std::endl;
    std::cout << vec << std::endl;

    return 0;
}
