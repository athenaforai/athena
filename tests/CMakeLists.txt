

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/gtest/googletest/include)


add_executable(runTests ${SRC_TEST})
target_include_directories(runTests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests athena)

add_test(
        NAME runTests
        COMMAND runTests
)