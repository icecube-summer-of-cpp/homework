cmake_minimum_required (VERSION 2.6)
project (week1)

#SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++0x -O3 -DNDEBUG") # Release
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++0x -O0 -g") # Debug
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(task_1_10_1 task_1_10_1.cpp)
add_executable(task_1_10_2a task_1_10_2a.cpp)
