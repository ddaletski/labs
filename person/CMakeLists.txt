cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(person)
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
