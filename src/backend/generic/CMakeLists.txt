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
    set(BLAS_LIBRARIES ${PROJECT_SOURCE_DIR}/libs/openblas/lib/libopenblas.a PARENT_SCOPE)
endfunction(getOpenBLAS)


function(getblis)
    include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
    find_program(MAKE_EXE NAMES gmake nmake make)
    ExternalProject_Add(blis

            GIT_REPOSITORY "https://github.com/flame/blis.git"
            GIT_TAG "master"

            UPDATE_COMMAND ""
            PATCH_COMMAND ""

            PREFIX ${PROJECT_SOURCE_DIR}/libs
            SOURCE_DIR "blis"
            INSTALL_DIR "blis"

            CONFIGURE_COMMAND ./configure --prefix=${PROJECT_SOURCE_DIR}/libs/blis/include/blis/ --enable-cblas auto

            BUILD_IN_SOURCE TRUE
            BUILD_COMMAND "make"

            INSTALL_COMMAND ${MAKE_EXE} install
            )
    ExternalProject_Get_property(blis SOURCE_DIR)
    add_dependencies(athena blis)
    target_include_directories(athena PUBLIC ${PROJECT_SOURCE_DIR}/libs/blis/include/blis/include/blis)
    target_compile_definitions(athena PUBLIC -DFORCE_BLIS)
    set(BLAS_LIBRARIES ${PROJECT_SOURCE_DIR}/libs/blis/include/blis/lib/libblis.a PARENT_SCOPE)
endfunction(getblis)


option(FORCE_OPENBLAS "Require library to use OpenBLAS" OFF)
option(FORCE_BLIS "Require library to use BLIS" OFF)

if (FORCE_OPENBLAS)
    message(STATUS "OpenBLAS will be downloaded and compiled")
    getOpenBLAS()
elseif(FORCE_BLIS)
    message(STATUS "BLIS will be downloaded and compiled")
    getblis()
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
