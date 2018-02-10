cmake_minimum_required(VERSION 3.1)

project(fraction)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
    "main.cpp"
    "fraction.cpp"
    )
