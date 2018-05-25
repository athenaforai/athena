//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_TENSOR_H
#define ATHENA_TENSOR_H


namespace athena {
    namespace core {
        template <typename T>
        class Tensor {
        private:
            int *shape;
            int dimension;
        };
    }
}


#endif //ATHENA_TENSOR_H
