add_library(athena STATIC core/kernels/ScaleOpKernel.cpp core/kernels/ScaleOpKernel.h backend/generic/scale.cpp)

add_subdirectory(core)
add_subdirectory(ops)
add_subdirectory(backend)

target_include_directories(athena PUBLIC .)
target_link_libraries(athena ${BACKEND_LIBS})