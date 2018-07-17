cmake_minimum_required(VERSION 3.9)
project(athena)

set(ATHENA_VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

#add_subdirectory(libs/openblas)

add_subdirectory(src)

add_subdirectory(libs/gtest)

enable_testing()
add_subdirectory(tests)

find_package(Doxygen)
if(DOXYGEN_FOUND)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
                      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/reference
                      COMMENT "Generating API documentation with Doxygen" VERBATIM
                      )

#    set(DOXYGEN_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
#    set(DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
#
#    add_custom_command(
#            OUTPUT ${DOXYGEN_OUTPUT}
#            COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
#            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
#            COMMAND ${CMAKE_COMMAND} -E echo "Done."
#            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/reference
#            DEPENDS ${DOXYGEN_INPUT}
#    )
#
#    add_custom_target(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})
#
#    add_custom_target(apidoc_forced
#                      COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
#                      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
#                      COMMAND ${CMAKE_COMMAND} -E echo "Done."
#                      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/reference
#                      )
endif(DOXYGEN_FOUND)