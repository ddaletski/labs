cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(rpn_evaluator)
add_executable(${PROJECT_NAME}
    "main.cpp"
    "rpnparser.cpp"
    "lexer.cpp"
    )
