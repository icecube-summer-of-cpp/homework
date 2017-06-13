cmake_minimum_required(VERSION 2.6)
project(week1-homework)

set(PROJECT_NAME "homework")
set(BINDIR "/home/jh/Exercise/Study/2017/icecube_cpp_bootcamp/homework/week1/quiz/bin")
set(CMAKE_CXX_STANDARD 14)
include_directories(/home/jh/Exercise/Study/2017/icecube_cpp_bootcamp/homework/week1/quiz/include)
file(GLOB SRCS src/*.cc)
add_executable(${PROJECT_NAME} ${SRCS})
 
install(TARGETS ${PROJECT_NAME} DESTINATION ${BINDIR})
