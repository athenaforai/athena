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
            T *heap;    //Array with unordered data
            int *shape;     //Array with sizes of dimensions
            int dimensionality;      //Count dimensions
            int sizeHeap;

        public:
            //** CONSTRUCTORS **//
            Tensor(int dimensionality, const int* shape);

            //** DESTRUCTOR **//
            ~Tensor();

            //** METHODS ACCESS **//
            T get(const int *indexes);       //Size of *indexes* must be equals to *dimensionality*
            void set(const int *indexes, T value);       //Size of *indexes* must be equals to *dimensionality*
        };


    }
}


#endif
