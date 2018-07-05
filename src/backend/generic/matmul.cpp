//
// Created by Александр Баташев on 27.05.2018.
//

#include "ops.h"

#ifdef APPLE_ACCELERATE

#include <Accelerate/Accelerate.h>

#else
#include "cblas.h"
#endif

#define NO_TRANS CBLAS_TRANSPOSE::CblasNoTrans
#define TRANS CBLAS_TRANSPOSE::CblasTrans
#define C_ORDER CBLAS_ORDER::CblasRowMajor

#include <core/Tensor.h>
#include <core/DataType.h>
#include <stdexcept>


namespace athena::backend::generic {

    athena::core::Tensor* matmulf (
            bool aTransp, athena::core::Tensor* a, bool bTransp, athena::core::Tensor* b
    ) {
        auto af = reinterpret_cast<float*>(a->raw());
        auto bf = reinterpret_cast<float*>(b->raw());

        auto cf = new float[a->getShape().dim( 0 ) * b->getShape().dim( 1 )];

        cblas_sgemm(
                C_ORDER, // Specifies row-major (C) or column-major (Fortran) data ordering
                aTransp ? TRANS : NO_TRANS, // Specifies whether to transpose matrix A
                bTransp ? TRANS : NO_TRANS, // Specifies whether to transpose matrix B
                static_cast<const int>(a->getShape().dim(
                        0 )), // Number of rows in matrices A and C.
                static_cast<const int>(b->getShape().dim(
                        1 )), // Number of columns in matrices B and C
                static_cast<const int>(a->getShape().dim( 1 )), // Number of columns in
                // matrix A; number of rows in matrix B
                1, // Scaling factor for the product of matrices A and B
                af, // Matrix A
                static_cast<const int>(a->getShape().dim(
                        0 )), // The size of the first dimention of matrix A; if you are passing a matrix A[m][n], the value should be m
                bf, // Matrix B
                static_cast<const int>(b->getShape().dim(
                        0 )), // The size of the first dimention of matrix B; if you are passing a matrix B[m][n], the value should be m
                0, // Scaling factor for matrix C
                cf, // Matrix C
                static_cast<const int>(a->getShape().dim(
                        0 ))); // The size of the first dimention of matrix C; if you are passing a matrix C[m][n], the value should be m

        return new athena::core::Tensor(
                const_cast<core::TensorShape &>(b->getShape()),
                athena::core::DataType::FLOAT,
                reinterpret_cast<unsigned char*>(cf));
    }

    athena::core::Tensor* matmuld (
            bool aTransp, athena::core::Tensor* a, bool bTransp, athena::core::Tensor* b
    ) {
        auto af = reinterpret_cast<double*>(a->raw());
        auto bf = reinterpret_cast<double*>(b->raw());

        auto cf = new double[a->getShape().dim( 0 ) * b->getShape().dim( 1 )];

        cblas_dgemm(
                C_ORDER, // Specifies row-major (C) or column-major (Fortran) data ordering
                aTransp ? TRANS : NO_TRANS, // Specifies whether to transpose matrix A
                bTransp ? TRANS : NO_TRANS, // Specifies whether to transpose matrix B
                static_cast<const int>(a->getShape().dim(
                        0
                )), // Number of rows in matrices A and C.
                static_cast<const int>(b->getShape().dim(
                        1
                )), // Number of columns in matrices B and C
                static_cast<const int>(a->getShape().dim(
                        1
                )), // Number of columns in matrix A; number of rows in matrix B
                1, // Scaling factor for the product of matrices A and B
                af, // Matrix A
                static_cast<const int>(a->getShape().dim(
                        0
                )), // The size of the first dimention of matrix A; if you are passing a matrix A[m][n], the value should be m
                bf, // Matrix B
                static_cast<const int>(b->getShape().dim(
                        0
                )), // The size of the first dimention of matrix B; if you are passing a matrix B[m][n], the value should be m
                0, // Scaling factor for matrix C
                cf, // Matrix C
                static_cast<const int>(a->getShape().dim(
                        0
                ))); // The size of the first dimention of matrix C; if you are passing a matrix C[m][n], the value should be m

        return new athena::core::Tensor(
                const_cast<core::TensorShape &>(b->getShape()),
                athena::core::DataType::FLOAT,
                reinterpret_cast<unsigned char*>(cf));
    }

    athena::core::Tensor* matmul (
            bool aTransp, athena::core::Tensor* a, bool bTransp, athena::core::Tensor* b
    ) {
        // todo shape checks
        if ( a->getShape().dimensions() != 2 || b->getShape().dimensions() != 2 ) {
            // todo better log output
            throw std::runtime_error( "Matrix is a 2D array" );
        }

        if ( a->getType() == athena::core::DataType::FLOAT ) {
            return matmulf( aTransp, a, bTransp, b );
        } else if ( a->getType() == athena::core::DataType::DOUBLE ) {
            return matmuld( aTransp, a, bTransp, b );
        }

        return nullptr;
    }
}

#undef NO_TRANS
#undef C_ORDER