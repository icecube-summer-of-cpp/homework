cmake_minimum_required (VERSION 2.6)

set (CMAKE_CXX_STANDARD 11)

project(particle)

set(SOURCE_FILES particle.cpp)

add_library(direction direction.cpp)
add_library(position position.cpp)

add_executable(particle particle.cpp)
target_link_libraries(particle direction position)
