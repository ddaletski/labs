cmake_minimum_required(VERSION 3.0)

project(Parallel)

set(CXX_STANDARD_REQUIRED 11)
set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(run ${SOURCES} ${HEADERS})
target_link_libraries(run pthread)
