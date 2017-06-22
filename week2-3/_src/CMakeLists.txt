cmake_minimum_required (VERSION 2.6)
project (week2-3)

#SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++0x -O3 -DNDEBUG") # Release
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++0x -O0 -g") # Debug
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(task_2_8_1 task_2_8_1.cpp)
