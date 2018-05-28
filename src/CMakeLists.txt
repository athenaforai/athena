add_library(athena STATIC)

add_subdirectory(core)
add_subdirectory(ops)
add_subdirectory(backend)
add_subdirectory(optimizers)

target_include_directories(athena PUBLIC .)
target_link_libraries(athena ${BACKEND_LIBS})