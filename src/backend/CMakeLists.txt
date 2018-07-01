target_sources(athena PUBLIC
               ${CMAKE_CURRENT_SOURCE_DIR}/ExecutorService.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/ExecutorService.h
               ${CMAKE_CURRENT_SOURCE_DIR}/AbstractExecutor.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/AbstractExecutor.h
               ${CMAKE_CURRENT_SOURCE_DIR}/ExecutorFactory.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/AbstractDevice.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/AbstractDevice.h
               ${CMAKE_CURRENT_SOURCE_DIR}/opcode_parser.h
               ${CMAKE_CURRENT_SOURCE_DIR}/opcode_parser.cpp
               )


add_subdirectory(generic)

set(BACKEND_LIBS ${GENERIC_BACKEND_LIBS} PARENT_SCOPE)