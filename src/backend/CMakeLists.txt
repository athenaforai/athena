target_sources(athena PUBLIC
               ${CMAKE_CURRENT_SOURCE_DIR}/AbstractExecutor.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/AbstractExecutor.h
               ${CMAKE_CURRENT_SOURCE_DIR}/AbstractDevice.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/AbstractDevice.h
               ${CMAKE_CURRENT_SOURCE_DIR}/VirtualMemory.h
               ${CMAKE_CURRENT_SOURCE_DIR}/VirtualMemory.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/AbstractMemoryManager.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/AbstractMemoryManager.h
               ${CMAKE_CURRENT_SOURCE_DIR}/opcode_parser.h
               ${CMAKE_CURRENT_SOURCE_DIR}/opcode_parser.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/VMState.h
               ${CMAKE_CURRENT_SOURCE_DIR}/opcodes.h
               ${CMAKE_CURRENT_SOURCE_DIR}/opcodes.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/Semaphore.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/Semaphore.h
               )


add_subdirectory(generic)

set(BACKEND_LIBS ${GENERIC_BACKEND_LIBS} PARENT_SCOPE)