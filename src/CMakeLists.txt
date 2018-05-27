add_subdirectory(core)
add_subdirectory(ops)
add_subdirectory(backend)

add_library(athena ${CORE_SRC} ${OPS_SRC} ${BACKEND_SRC})
target_include_directories(athena PUBLIC .)
target_link_libraries(athena ${BACKEND_LIBS})