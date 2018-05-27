function(getOpenBLAS)
    include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
    find_program(MAKE_EXE NAMES gmake nmake make)
    ExternalProject_Add(OpenBLAS

            GIT_REPOSITORY "https://github.com/xianyi/OpenBLAS.git"
            GIT_TAG "master"

            UPDATE_COMMAND ""
            PATCH_COMMAND ""

            PREFIX ${PROJECT_SOURCE_DIR}/libs
            SOURCE_DIR "openblas"
            INSTALL_DIR "openblas"

            CONFIGURE_COMMAND ""

            BUILD_IN_SOURCE TRUE
            BUILD_COMMAND "make"

            INSTALL_COMMAND ${MAKE_EXE} PREFIX=${PROJECT_SOURCE_DIR}/libs/openblas install

    )
    ExternalProject_Get_property(OpenBLAS SOURCE_DIR)
    add_dependencies(athena OpenBLAS)
    target_include_directories(athena PUBLIC ${PROJECT_SOURCE_DIR}/libs/openblas/include)
    target_compile_definitions(athena PUBLIC -DFORCE_OPENBLAS)
endfunction(getOpenBLAS)


option(FORCE_OPENBLAS "Require library to use OpenBLAS" OFF)

if (FORCE_OPENBLAS)
    message(STATUS "OpenBLAS will be downloaded and compiled")
    getOpenBLAS()
else()
    if (APPLE)
        set(BLA_VENDOR Apple)
        target_compile_definitions(athena PUBLIC -DAPPLE_ACCELERATE)
        message(STATUS "Apple Accelerate Framework will be used")
    endif()
    find_package(BLAS)

endif()

target_sources(athena PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/GenericExecutor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GenericExecutor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/add.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ops.h)

set(GENERIC_BACKEND_LIBS ${BLAS_LIBRARIES} PARENT_SCOPE)
