#
# Solution to first week's quiz
#
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)

project(matrix_market)
add_library(matrix_market matrix_market.cpp)
add_executable(example example.cpp)
target_link_libraries(example matrix_market)
