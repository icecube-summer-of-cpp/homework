cmake_minimum_required (VERSION 2.6)

set (CMAKE_CXX_STANDARD 11)

project(polynomial)

set(SOURCE_FILES Polynomial.cpp)

add_executable(polynomial Polynomial.cpp Polynomial.h)

