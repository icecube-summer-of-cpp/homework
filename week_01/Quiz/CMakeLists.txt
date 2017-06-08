
# General makefile to compile

cmake_minimum_required (VERSION 2.6)
project (Quiz_1)
add_library(matrix_reader matrix_reader.cpp)
set (CMAKE_CXX_STANDARD 11)
add_executable (Quiz_1 Quiz_1.cpp)
target_link_libraries ( Quiz_1 matrix_reader)
