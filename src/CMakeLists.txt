add_subdirectory(core)
add_subdirectory(ops)

add_library(athena ${CORE_SRC} ${OPS_SRC})