cmake_minimum_required (VERSION 2.6)
project (Week1)

#SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++0x -O3 -DNDEBUG") # Release
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++0x -O0 -g") # Debug
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(excercise_1_10_1 excercise_1_10_1.cpp)
add_executable(excercise_1_10_2_a excercise_1_10_2_a.cpp)
add_executable(excercise_1_10_2_b excercise_1_10_2_b.cpp)
add_executable(excercise_1_10_3 excercise_1_10_3.cpp)
