cmake_minimum_required (VERSION 2.6)
project (Week1)
###CXXFLAGS= -O3 -DNDEBUG -std=c++0x # Release

### add_library(excercise_1_10_1 excercise_1_10_1.cpp)
### add_library(excercise_1_10_2 excercise_1_10_2.cpp)
### add_library(excercise_1_10_3 excercise_1_10_3.cpp)
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++0x -O0 -g")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(excercise_1_10_1 excercise_1_10_1.cpp)
add_executable(excercise_1_10_2 excercise_1_10_2.cpp)
add_executable(excercise_1_10_2_b excercise_1_10_2_b.cpp)
add_executable(excercise_1_10_3 excercise_1_10_3.cpp)
