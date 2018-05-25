cmake_minimum_required(VERSION 3.10)
project(athena)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(backend)

add_subdirectory(libs/gtest)
add_subdirectory(tests)