cmake_minimum_required (VERSION 2.6)
project (Quiz1)

#SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++0x -O3 -DNDEBUG") # Release
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++0x -O0 -g") # Debug
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(exercise_1_10_3 exercise_1_10_3.cpp  exercise_1_10_3.hpp)
