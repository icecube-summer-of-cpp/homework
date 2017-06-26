cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)

project(unique_id)

add_library(unique_id unique_id.cpp)
add_library(particle particle.cpp)

add_executable(main main.cpp)
target_link_libraries(main unique_id particle)
