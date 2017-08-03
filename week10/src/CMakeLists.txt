cmake_minimum_required (VERSION 2.6)
project (Week9)

#SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -O3 -DNDEBUG") # Release
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -O0") # Debug
SET(SDL_LINKER_FLAGS "-D_GNU_SOURCE=1 -D_REENTRANT -I/usr/include/SDL -lSDL") # SDL
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

##
## Stuff for GTest
##

# Download and unpack googletest at configure time
#configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
#execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#  RESULT_VARIABLE result
#  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
#if(result)
#  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
#endif()
#execute_process(COMMAND ${CMAKE_COMMAND} --build .
#  RESULT_VARIABLE result
#  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
#if(result)
#  message(FATAL_ERROR "Build step for googletest failed: ${result}")
#endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
#add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
#                 ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
#if (CMAKE_VERSION VERSION_LESS 2.8.11)
#  include_directories("${gtest_SOURCE_DIR}/include")
#endif()

##
## My part
##

add_executable(excercise_4_8_1 excercise_4_8_1.cpp)
add_executable(excercise_4_8_2 excercise_4_8_2.cpp)
add_executable(excercise_4_8_3 excercise_4_8_3.cpp)
add_executable(mandelbrot mandelbrot.cpp)

TARGET_LINK_LIBRARIES(mandelbrot "${SDL_LINKER_FLAGS}")

# Now simply link against gtest or gtest_main as needed. Eg
#target_link_libraries(excercise_3_11_11 gtest_main)
#add_test(NAME test_test COMMAND excercise_3_11_11)
