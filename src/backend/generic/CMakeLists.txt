
#set(BLA_VENDOR OpenBLAS)
#if (EXISTS /usr/local/opt/openblas/)
#    set(BLAS_DIR /usr/local/opt/openblas/)
#endif()
find_package(BLAS)

set(GENERIC_EXEC_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/GenericExecutor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GenericExecutor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/add.cpp
        PARENT_SCOPE)

#set(ATHENA_LIBS ${ATHENA_LIBS} ${BLAS_LIBRARIES})
#
#message(STATUS ${BLAS_LIBRARIES})
#message(STATUS ${ATHENA_LIBS})