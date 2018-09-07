cmake_minimum_required(VERSION 3.0)
project(ndarray)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${SRC_DIR})
file(GLOB SOURCES ${SRC_DIR}/*.cpp)
file(GLOB HEADERS ${SRC_DIR}/*.h)

add_executable(run ${SOURCES} ${HEADERS})

