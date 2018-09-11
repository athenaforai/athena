/*
 * Copyright (c) 2018 Athena. All rights reserved.
 * https://athenaframework.ml
 *
 * Licensed under MIT license.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an “AS IS” BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#ifndef ATHENA_GENERICEXECUTOR_H
#define ATHENA_GENERICEXECUTOR_H

#include <backend/AbstractExecutor.h>
#include <stack>
#include <core/Tensor.h>
#include <utility>
#include <vector>
#include <backend/opcodes.h>
#include <backend/VMState.h>
#include "CPUDevice.h"

#ifdef TEST_ENVIRONMENT
#include <gtest/gtest.h>
#endif

namespace athena::backend::generic {

    /**
     * <p>
     * GenericExecutor is the state of the art implementation of AbstractExecutor.
     * While we try to make it work fast, the main goal of this implementation
     * is to be mathematically correct and provide an example for more specific
     * implementation.
     * </p>
     * <p>
     * GenericExecutor executes
     * <a href="https://athenaframework.ml/athena/bytecode/basics.html">bytecode</a>
     * with standard CPU device. The actual implementations of bytecode commands
     * use BLAS to speed up calculations. There are several accelerators available:
     * <ul>
     * <li> <a href="https://developer.apple.com/documentation/accelerate">Apple
     * Accelerate Framework</a> </li>
     * <li> <a href="https://github.com/xianyi/OpenBLAS.git">OpenBLAS</a> </li>
     * <li> <a href="https://github.com/flame/blis.git">BLIS</a> </li>
     * </ul>
     * You can configure them during compile time. Other accelerators may be added
     * later.
     * </p>
     */
    class GenericExecutor : public athena::backend::AbstractExecutor {
#ifdef TEST_ENVIRONMENT
        friend class GenericExecutorTest;
        FRIEND_TEST( GenericExecutorTest, add_1d );
        FRIEND_TEST( GenericExecutorTest, copy_2x2 );
        FRIEND_TEST( GenericExecutorTest, matmul_unit );
        FRIEND_TEST( GenericExecutorTest, mkscalar_12_1_float );
        FRIEND_TEST( GenericExecutorTest, mse_7_2_vs_10_9 );
        FRIEND_TEST( GenericExecutorTest, scalef_test_2x2x2 );
        FRIEND_TEST( GenericExecutorTest, scalef_test_2x2 );
        FRIEND_TEST( GenericExecutorTest, scalef_test_1x1 );
#endif

    private:

        CPUDevice* device;

        void processBytecode ( VMState &state, std::vector<vm_word> bytecode );
    public:
        explicit GenericExecutor (
                CPUDevice* cpuDevice
        ) : AbstractExecutor(), device( cpuDevice ) {};

        ~GenericExecutor ();

        void execute () override ;

        AbstractMemoryManager* getMemoryManager () override ;
    };
}


#endif //ATHENA_GENERICEXECUTOR_H
