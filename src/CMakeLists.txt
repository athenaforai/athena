add_library(athena STATIC core/kernels/ScaleOpKernel.cpp core/kernels/ScaleOpKernel.h backend/generic/scale.cpp)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage ${PROJECT_TEST_NAME} coverage)
endif()

add_subdirectory(core)
add_subdirectory(ops)
add_subdirectory(backend)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(${PROJECT_TEST_NAME} gcov)
endif()

target_include_directories(athena PUBLIC .)
target_link_libraries(athena ${BACKEND_LIBS})