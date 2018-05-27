cmake_minimum_required(VERSION 3.9)
project(athena)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

#add_subdirectory(libs/openblas)

add_subdirectory(src)

add_subdirectory(libs/gtest)

enable_testing()
add_subdirectory(tests)