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
#define C_ORDER CBLAS_ORDER::CblasRowMajor

#include <core/Tensor.h>
#include <core/DataType.h>
#include <stdexcept>



namespace athena::backend::generic {

    athena::core::Tensor *matmulf(athena::core::Tensor *a, athena::core::Tensor *b) {
        auto af = reinterpret_cast<float *>(a->raw());
        auto bf = reinterpret_cast<float *>(b->raw());

        auto cf = new float[a->getShape().dim(0) * b->getShape().dim(1)];

        cblas_sgemm(C_ORDER, // Specifies row-major (C) or column-major (Fortran) data ordering
                    NO_TRANS, // Specifies whether to transpose matrix A
                    NO_TRANS, // Specifies whether to transpose matrix B
                    a->getShape().dim(0), // Number of rows in matrices A and C.
                    b->getShape().dim(1), // Number of columns in matrices B and C
                    a->getShape().dim(1), // Number of columns in matrix A; number of rows in matrix B
                    1, // Scaling factor for the product of matrices A and B
                    af, // Matrix A
                    a->getShape().dim(0), // The size of the first dimention of matrix A; if you are passing a matrix A[m][n], the value should be m
                    bf, // Matrix B
                    b->getShape().dim(0), // The size of the first dimention of matrix B; if you are passing a matrix B[m][n], the value should be m
                    1, // Scaling factor for matrix C
                    cf, // Matrix C
                    a->getShape().dim(0)); // The size of the first dimention of matrix C; if you are passing a matrix C[m][n], the value should be m

        return new athena::core::Tensor(const_cast<core::TensorShape &>(b->getShape()),
                                        athena::core::DataType::FLOAT,
                                        reinterpret_cast<unsigned char *>(cf));
    }

    athena::core::Tensor *matmuld(athena::core::Tensor *a, athena::core::Tensor *b) {
        auto af = reinterpret_cast<double *>(a->raw());
        auto bf = reinterpret_cast<double *>(b->raw());

        auto cf = new double[a->getShape().dim(0) * b->getShape().dim(1)];

        cblas_dgemm(C_ORDER, // Specifies row-major (C) or column-major (Fortran) data ordering
                    NO_TRANS, // Specifies whether to transpose matrix A
                    NO_TRANS, // Specifies whether to transpose matrix B
                    a->getShape().dim(0), // Number of rows in matrices A and C.
                    b->getShape().dim(1), // Number of columns in matrices B and C
                    a->getShape().dim(1), // Number of columns in matrix A; number of rows in matrix B
                    1, // Scaling factor for the product of matrices A and B
                    af, // Matrix A
                    a->getShape().dim(0), // The size of the first dimention of matrix A; if you are passing a matrix A[m][n], the value should be m
                    bf, // Matrix B
                    b->getShape().dim(0), // The size of the first dimention of matrix B; if you are passing a matrix B[m][n], the value should be m
                    1, // Scaling factor for matrix C
                    cf, // Matrix C
                    a->getShape().dim(0)); // The size of the first dimention of matrix C; if you are passing a matrix C[m][n], the value should be m

        return new athena::core::Tensor(const_cast<core::TensorShape &>(b->getShape()),
                                        athena::core::DataType::FLOAT,
                                        reinterpret_cast<unsigned char *>(cf));
    }

    athena::core::Tensor *matmul(athena::core::Tensor *a, athena::core::Tensor *b) {
        // todo shape checks
        if (a->getShape().dimensions() != 2 || b->getShape().dimensions() != 2) {
            // todo better log output
            throw std::runtime_error("Matrix is a 2D array");
        }

        if (a->getType() == athena::core::DataType::FLOAT) {
            return matmulf(a, b);
        } else if (a->getType() == athena::core::DataType::DOUBLE) {
            return matmuld(a, b);
        }

        return nullptr;
    }
}

#undef NO_TRANS
#undef C_ORDER