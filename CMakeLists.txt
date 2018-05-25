cmake_minimum_required(VERSION 3.9)
project(athena)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

add_subdirectory(src)

add_subdirectory(libs/gtest)

enable_testing()
add_subdirectory(tests)