cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)

project(pokeball)

add_library(particle particle.cpp)
add_library(unique_id unique_id.cpp)

add_executable(main main.cpp)
target_link_libraries(main particle unique_id)
