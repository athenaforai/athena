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
#    set(BLA_VENDOR OpenBLAS PARENT_SCOPE)
#    set(BLAS_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs/openblas PARENT_SCOPE)
    ExternalProject_Get_property(OpenBLAS SOURCE_DIR)
    set(BLAS_LIBRARIES ${PROJECT_SOURCE_DIR}/libs/openblas/lib/libopenblas.a PARENT_SCOPE)
    set(BLAS_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/libs/openblas/include PARENT_SCOPE)
    set(OpenBLAS_DEPS OpenBLAS PARENT_SCOPE)
endfunction(getOpenBLAS)


option(FORCE_OPENBLAS "Require library to use OpenBLAS" OFF)

if (FORCE_OPENBLAS)
    getOpenBLAS()
else()
#    getOpenBLAS()
    find_package(BLAS)
endif()

#if()
include_directories(${PROJECT_SOURCE_DIR}/libs/openblas/include)
message(STATUS ${BLAS_INCLUDE_DIR})
message(STATUS ${CMAKE_BINARY_DIR}/openblas/include)

set(GENERIC_EXEC_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/GenericExecutor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GenericExecutor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/add.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ops.h
        PARENT_SCOPE)

set(GENERIC_BACKEND_LIBS ${BLAS_LIBRARIES} PARENT_SCOPE)
set(GENERIC_BACKEND_DEPS ${OpenBLAS_DEPS} PARENT_SCOPE)
#
#message(STATUS ${BLAS_LIBRARIES})
#message(STATUS ${ATHENA_LIBS})