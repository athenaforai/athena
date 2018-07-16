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
        std::vector< size_t > shape;
    public:
        explicit TensorShape ( std::vector< size_t > shape ) :
                shape( std::move( shape )) {};

        TensorShape() = default;

        TensorShape ( unsigned long* shape, unsigned long length );

        TensorShape ( const TensorShape & );

        TensorShape &operator= ( const TensorShape & );

        unsigned long dimensions () const;

        unsigned long dim ( unsigned long n ) const;

        unsigned long totalSize () const;

        const std::vector< unsigned long > &getShape () const;

        bool operator== ( const TensorShape & ) const;

        bool operator!= ( const TensorShape &rhs ) const;
//        friend bool operator!=(const TensorShape &, const TensorShape &);
    };
}


#endif //ATHENA_TENSORSHAPE_H
