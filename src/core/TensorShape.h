//
// Created by Александр Баташев on 26.05.2018.
//

#ifndef ATHENA_TENSORSHAPE_H
#define ATHENA_TENSORSHAPE_H

#include <vector>
#include <array>

namespace athena::core {
    class TensorShape {
    private:
        std::vector<size_t> shape;
    public:
        explicit TensorShape(std::vector<size_t> shape) : shape(std::move(shape)) {};
        TensorShape(size_t* shape, size_t length);

        size_t dimensions() const;
        size_t dim(size_t n) const;
        size_t total_size() const;
        const std::vector<size_t>& getShape() const;

        bool operator==(const TensorShape &) const;
        bool operator!=(const TensorShape &rhs) const;
//        friend bool operator!=(const TensorShape &, const TensorShape &);
    };
}


#endif //ATHENA_TENSORSHAPE_H
