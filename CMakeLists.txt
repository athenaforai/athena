cmake_minimum_required(VERSION 3.10)
project(athena)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

add_subdirectory(libs/gtest)

enable_testing()
add_subdirectory(tests)