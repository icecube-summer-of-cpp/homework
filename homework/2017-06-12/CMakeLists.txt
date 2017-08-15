cmake_minimum_required(VERSION 3.7)
project(cppsummer)

set(CMAKE_CXX_STANDARD 14)

add_executable(polynom 2.10.cpp polynom.cpp)
add_executable(manged_res_example managed_res.cpp old_res.cpp)