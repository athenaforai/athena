if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
    conan_basic_setup()
elseif(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) # Not CLion
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

set(CMAKE_MODULE_PATH ${CONAN_CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})

add_subdirectory(core)
add_subdirectory(ops)
add_subdirectory(backend)

add_library(athena ${CORE_SRC} ${OPS_SRC} ${BACKEND_SRC})
target_include_directories(athena PUBLIC .)
target_link_libraries(athena ${CONAN_LIBS})