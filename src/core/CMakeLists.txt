target_sources(athena PUBLIC
               ${CMAKE_CURRENT_SOURCE_DIR}/Tensor.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/Tensor.h
               ${CMAKE_CURRENT_SOURCE_DIR}/TensorShape.h
               ${CMAKE_CURRENT_SOURCE_DIR}/TensorShape.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/DataType.h
               ${CMAKE_CURRENT_SOURCE_DIR}/DataType.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/OpKernel.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/OpKernel.h
               ${CMAKE_CURRENT_SOURCE_DIR}/Node.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/Node.h
               ${CMAKE_CURRENT_SOURCE_DIR}/InputNode.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/InputNode.h
               ${CMAKE_CURRENT_SOURCE_DIR}/Session.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/Session.h
               ${CMAKE_CURRENT_SOURCE_DIR}/opcodes.h
               )

add_subdirectory(kernels)
add_subdirectory(optimizers)
add_subdirectory(loss)
add_subdirectory(initializers)