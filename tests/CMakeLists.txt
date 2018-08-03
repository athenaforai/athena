add_subdirectory(unit)
add_subdirectory(integration)

include_directories(${PROJECT_SOURCE_DIR}/libs/gtest/googletest/include)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage runTests coverage)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
endif()