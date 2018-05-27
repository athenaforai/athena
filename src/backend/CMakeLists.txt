target_sources(athena PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ExecutorService.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ExecutorService.h
        ${CMAKE_CURRENT_SOURCE_DIR}/AbstractExecutor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AbstractExecutor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ExecutorFactory.cpp
        )


add_subdirectory(generic)

set(BACKEND_LIBS ${GENERIC_BACKEND_LIBS} PARENT_SCOPE)