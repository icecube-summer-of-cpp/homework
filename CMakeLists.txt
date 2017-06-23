cmake_minimum_required(VERSION 3.7)
project(cppsummer)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(./homework/2017-06-05)
add_subdirectory(./homework/2017-06-12)
add_subdirectory(./quizes/1)
add_subdirectory(./quizes/2)
add_executable(test test.cpp)