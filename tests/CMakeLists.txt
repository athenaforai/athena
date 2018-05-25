add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/gtest/googletest/include)


add_executable(runTests ${CORE_TEST} ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Tensor.cpp)


target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests athena)

add_test(
        NAME runTests
        COMMAND runTests
)