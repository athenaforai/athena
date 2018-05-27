add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backend)

set(SRC_TEST ${CORE_TEST} ${BACKEND_TEST} PARENT_SCOPE)