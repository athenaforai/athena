cmake_minimum_required(VERSION 3.9)
project(athena)

set(ATHENA_VERSION 0.2)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

add_subdirectory(src)

add_subdirectory(libs/gtest)
add_subdirectory(libs/hermes)
target_include_directories(athena PUBLIC libs/hermes/include)

enable_testing()
add_subdirectory(tests)

find_package(Doxygen)
if(DOXYGEN_FOUND)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
                      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                      COMMENT "Generating API documentation with Doxygen" VERBATIM
                      )

endif(DOXYGEN_FOUND)