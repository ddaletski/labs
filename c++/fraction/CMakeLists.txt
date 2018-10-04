cmake_minimum_required(VERSION 3.1)
project(fraction)

set(CMAKE_CXX_STANDARD 11)
ENABLE_LANGUAGE(CXX)

find_package(Threads REQUIRED)


set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
    "main.cpp"
    "fraction.cpp"
    )


enable_testing()

add_executable(run_tests "test.cpp" "fraction.cpp")
target_link_libraries(run_tests "-lgtest" ${CMAKE_THREAD_LIBS_INIT})

add_test(test1 "run_tests")
