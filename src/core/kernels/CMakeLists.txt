target_sources(athena PUBLIC
               ${CMAKE_CURRENT_SOURCE_DIR}/AddOpKernel.h
               ${CMAKE_CURRENT_SOURCE_DIR}/AddOpKernel.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/MatMulOpKernel.h
               ${CMAKE_CURRENT_SOURCE_DIR}/MatMulOpKernel.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/SigmoidOpKernel.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/SigmoidOpKernel.h
               ${CMAKE_CURRENT_SOURCE_DIR}/ScaleOpKernel.h
               ${CMAKE_CURRENT_SOURCE_DIR}/ScaleOpKernel.cpp
               )