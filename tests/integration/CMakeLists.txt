add_executable(runIntegrationTests vm.cpp)
target_include_directories(runIntegrationTests PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(runIntegrationTests gtest gtest_main)
target_link_libraries(runIntegrationTests athena)

add_test(
        NAME runIntegrationTests
        COMMAND runIntegrationTests
)