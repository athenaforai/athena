add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backend)

add_executable(runTests ${CORE_TEST} ${BACKEND_TEST} backend/generic/copy.cpp backend/generic/mkscalar.cpp backend/generic/mse.cpp backend/generic/scale.cpp)
target_include_directories(runTests PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_compile_definitions(runTests PUBLIC TEST_ENVIRONMENT)
target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests athena)

add_test(
        NAME UnitTests
        COMMAND runTests
)

if($ENV{USE_GCOV})
    target_link_libraries(runTests gcov)
endif()