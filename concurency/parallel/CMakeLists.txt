set(CMAKE_MINIMUM_REQUIRED_VERSION 3.0)
project(Parallel)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(run ${SOURCES} ${HEADERS})
target_link_libraries(run pthread)
