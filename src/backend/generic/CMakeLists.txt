#find_package(Boost REQUIRED COMPONENTS system numeric)

#include_directories(${Boost_INCLUDE_DIRS})
#message(WARNING ${Boost_INCLUDE_DIRS})
#link_directories(${Boost_LIBRARY_DIRS})

set(GENERIC_EXEC_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/GenericExecutor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GenericExecutor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/add.cpp
        PARENT_SCOPE)