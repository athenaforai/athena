add_executable(runIntegrationTests vm.cpp)
target_include_directories(runIntegrationTests PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_compile_definitions(runIntegrationTests PUBLIC TEST_ENVIRONMENT)
target_link_libraries(runIntegrationTests gtest gtest_main)
target_link_libraries(runIntegrationTests athena)
if($ENV{USE_CCOV})
    target_link_libraries(runIntegrationTests gcov)
endif()
add_test(
        NAME IntegrationTest
        COMMAND runIntegrationTests
)