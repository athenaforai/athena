/*
 * Copyright (c) 2018 Athena. All rights reserved.
 * https://athenaproject.ml
 *
 * Licensed under MIT license.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an “AS IS” BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

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

    void matmulf (
            GenericMemoryManager* memoryManager,
            bool aTransp,
            athena::core::Tensor* a,
            bool bTransp,
            athena::core::Tensor* b,
            athena::core::Tensor* res ) {

        auto af = reinterpret_cast<float*>(memoryManager->getPhysicalAddress(
                a->getStartAddress()));
        auto bf = reinterpret_cast<float*>(memoryManager->getPhysicalAddress(
                b->getStartAddress()));
        auto cf = reinterpret_cast<float*>(memoryManager->getPhysicalAddress(
                res->getStartAddress()));

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

    }

    void matmuld (
            GenericMemoryManager* memoryManager,
            bool aTransp,
            athena::core::Tensor* a,
            bool bTransp,
            athena::core::Tensor* b,
            athena::core::Tensor* res
    ) {
        auto af = reinterpret_cast<double*>(memoryManager->getPhysicalAddress(
                a->getStartAddress()));
        auto bf = reinterpret_cast<double*>(memoryManager->getPhysicalAddress(
                b->getStartAddress()));
        auto cf = reinterpret_cast<double*>(memoryManager->getPhysicalAddress(
                res->getStartAddress()));

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
    }

    void matmul (
            GenericMemoryManager* memoryManager,
            bool aTransp,
            athena::core::Tensor* a,
            bool bTransp,
            athena::core::Tensor* b,
            athena::core::Tensor* res
    ) {
        // todo shape checks
        if ( a->getShape().dimensions() != 2 || b->getShape().dimensions() != 2 ) {
            // todo better log output
            throw std::runtime_error( "Matrix is a 2D array" );
        }

        if ( a->getType() == athena::core::DataType::FLOAT ) {
            matmulf( memoryManager, aTransp, a, bTransp, b, res );
        } else if ( a->getType() == athena::core::DataType::DOUBLE ) {
            matmuld( memoryManager, aTransp, a, bTransp, b, res );
        }
    }
}

#undef NO_TRANS
#undef C_ORDER