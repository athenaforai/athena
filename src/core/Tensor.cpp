//
// Created by Александр Баташев on 25.05.2018.
//

#include "Tensor.h"



namespace athena {
    namespace core {
        //** CONSTRUCTORS **//
        template<typename T>
        Tensor<T>::Tensor(int dimensionality, const int *shape) : dimensionality(dimensionality),
                                                                  shape(new int[dimensionality]) {
            int i;

            sizeHeap = 1;
            for (i = 0; i < dimensionality; i++)
                sizeHeap *= shape[i];
            heap = new T[sizeHeap];

            for (i = 0; i < dimensionality; i++)
                this->shape[i] = shape[i];
        }

        //** DESTRUCTOR **//
        template<typename T>
        Tensor<T>::~Tensor() {
            delete[] heap;
            delete[] shape;
        }

        //** METHODS ACCESS **//
        template<typename T>
        T Tensor<T>::get(const int *indexes) {
            int i;
            T *target = heap;

            for (i = 0; i < dimensionality; i++) {
                target = target + indexes[i] * shape[i];
            }

            return *target;
        }

        template<typename T>
        void Tensor<T>::set(const int *indexes, T value) {
            int i;
            T *target = heap;

            for (i = 0; i < dimensionality; i++) {
                target = target + indexes[i] * shape[i];
            }

            *target = value;
        }
    }
}