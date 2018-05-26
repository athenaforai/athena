//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_ADD_H
#define ATHENA_ADD_H
#include <core/Node.h>

/**
 * Add two tensors
 * @param a First tensor
 * @param b Second tensor
 * @return Result a+b tensor
 */
athena::core::Node* add(athena::core::Node* a, athena::core::Node* b);

#endif //ATHENA_ADD_H
