cmake_minimum_required (VERSION 2.6)
project (QuizWeek3)

#SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -O3 -DNDEBUG") # Release
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -O0 -g") # Debug
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(test_unique_id test_unique_id.cpp unique_id.cpp unique_id.hpp particle.hpp)
