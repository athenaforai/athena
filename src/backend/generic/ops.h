//
// Created by Александр Баташев on 27.05.2018.
//

#ifndef ATHENA_OPS_H
#define ATHENA_OPS_H

#include <core/Tensor.h>
#include <core/DataType.h>

namespace athena::backend::generic {
    athena::core::Tensor *add(athena::core::Tensor *a, athena::core::Tensor *b);
}
#endif //ATHENA_OPS_H
