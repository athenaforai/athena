add_subdirectory(core)
add_subdirectory(ops)
add_subdirectory(backend)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(athena ${CORE_SRC} ${OPS_SRC} ${BACKEND_SRC})
target_include_directories(athena PUBLIC .)
target_link_libraries(athena ${CONAN_LIBS})