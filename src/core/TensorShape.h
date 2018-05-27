//
// Created by Александр Баташев on 26.05.2018.
//

#ifndef ATHENA_TENSORSHAPE_H
#define ATHENA_TENSORSHAPE_H

#include <vector>

namespace athena::core {
    class TensorShape {
    private:
        std::vector<unsigned int> shape;
    public:
        explicit TensorShape(std::vector<unsigned int> shape) : shape(std::move(shape)) {};
        TensorShape(unsigned int* shape, unsigned int length);

        unsigned int dimensions() const;
        unsigned int dim(unsigned int n) const;
        unsigned int total_size();

        bool operator==(const TensorShape &) const;
//        friend bool operator!=(const TensorShape &, const TensorShape &);
    };
}


#endif //ATHENA_TENSORSHAPE_H
