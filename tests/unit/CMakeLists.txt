add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backend)

add_executable(runTests ${CORE_TEST} ${BACKEND_TEST})
target_include_directories(runTests PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests athena)

add_test(
        NAME runTests
        COMMAND runTests
)