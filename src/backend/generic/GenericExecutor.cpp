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

#include "GenericExecutor.h"
#include <backend/opcodes.h>
#include <stdexcept>
#include <backend/opcode_parser.h>
#include "ops.h"

using namespace athena::core;

void athena::backend::generic::GenericExecutor::execute () {

    VMState state;

    processBytecode( state, this->bytecode );

}

athena::backend::AbstractMemoryManager*
athena::backend::generic::GenericExecutor::getMemoryManager () {
    return device->getMemoryManager();
}

void athena::backend::generic::GenericExecutor::processBytecode (
        athena::backend::VMState &state, std::vector<vm_word> bytecode ) {
    OpCode op;
    auto *args = new vm_word[10];
    unsigned long argc = 0;

    auto gmm = dynamic_cast<GenericMemoryManager*>(device->getMemoryManager());

    while ( parse( bytecode, state.IP, op, args, argc ) <= bytecode.size()) {
        switch ( op ) {
            case OpCode::ADD: {
                gmm->loadAndLock( args[ 0 ] );
                gmm->loadAndLock( args[ 1 ] );
                gmm->allocateAndLock( args[ 2 ] );
                add( gmm,
                     gmm->getTensor( args[ 0 ] ),
                     gmm->getTensor( args[ 1 ] ),
                     gmm->getTensor( args[ 2 ] ));

                gmm->unlock( args[ 0 ] );
                gmm->unlock( args[ 1 ] );
                gmm->unlock( args[ 2 ] );
                break;
            }
            case OpCode::MATMUL: {

                gmm->loadAndLock( args[ 1 ] );
                gmm->loadAndLock( args[ 3 ] );
                gmm->allocateAndLock( args[ 4 ] );

                auto aTransp = static_cast<bool>(args[ 0 ]);
                Tensor* a = gmm->getTensor( args[ 1 ] );
                auto bTransp = static_cast<bool>( args[ 2 ]);
                Tensor* b = gmm->getTensor( args[ 3 ] );
                Tensor* res = gmm->getTensor( args[ 4 ] );
                matmul( gmm, aTransp, a, bTransp, b, res );

                gmm->unlock( args[ 1 ] );
                gmm->unlock( args[ 3 ] );
                gmm->unlock( args[ 4 ] );
                break;
            }
            case OpCode::SIGMOID: {
                gmm->loadAndLock( args[ 0 ] );
                gmm->allocateAndLock( args[ 1 ] );
                Tensor* x = gmm->getTensor( args[ 0 ]);
                Tensor* res = gmm->getTensor( args[ 1 ]);
                sigmoid( gmm, x, res );
                gmm->unlock( args[ 0 ] );
                gmm->unlock( args[ 1 ] );
                break;
            }
            case OpCode::SIGMOID_DERIV: {
                gmm->loadAndLock( args[ 0 ] );
                gmm->allocateAndLock( args[ 1 ] );
                Tensor* x = gmm->getTensor( args[ 0 ]);
                Tensor* res = gmm->getTensor( args[ 1 ]);
                sigmoid_deriv( gmm, x, res );
                gmm->unlock( args[ 0 ] );
                gmm->unlock( args[ 1 ] );
                break;
            }
            case OpCode::SCALE: {
                gmm->loadAndLock( args[ 0 ] );
                gmm->loadAndLock( args[ 1 ] );
                gmm->allocateAndLock( args[ 2 ] );
                Tensor* x = gmm->getTensor( args[ 0 ]);
                Tensor* y = gmm->getTensor( args[ 1 ]);
                Tensor* res = gmm->getTensor( args[ 2 ]);
                scale( gmm, x, y, res );
                gmm->unlock( args[ 0 ] );
                gmm->unlock( args[ 1 ] );
                gmm->unlock( args[ 2 ] );
                break;
            }
            case OpCode::MSE: {
                gmm->loadAndLock( args[ 0 ] );
                gmm->loadAndLock( args[ 1 ] );
                gmm->allocateAndLock( args[ 2 ] );
                Tensor* x = gmm->getTensor( args[ 0 ]);
                Tensor* y = gmm->getTensor( args[ 1 ]);
                Tensor* res = gmm->getTensor( args[ 2 ]);
                mse( gmm, x, y, res );
                gmm->unlock( args[ 0 ] );
                gmm->unlock( args[ 1 ] );
                gmm->unlock( args[ 2 ] );
                break;
            }
            case OpCode::MSE_DERIV: {
                gmm->loadAndLock( args[ 0 ] );
                gmm->loadAndLock( args[ 1 ] );
                gmm->allocateAndLock( args[ 2 ] );
                Tensor* x = gmm->getTensor( args[ 0 ]);
                Tensor* y = gmm->getTensor( args[ 1 ]);
                Tensor* res = gmm->getTensor( args[ 2 ]);
                mse_deriv( gmm, x, y, res );
                gmm->unlock( args[ 0 ] );
                gmm->unlock( args[ 1 ] );
                gmm->unlock( args[ 2 ] );
                break;
            }
            case OpCode::MKSCALAR: {
                gmm->allocateAndLock( args[ 1 ] );
                unsigned long x = args[ 0 ];
                Tensor* res = gmm->getTensor( args[ 1 ]);
                mkscalar( gmm, x, res );
                gmm->unlock( args[ 1 ] );
                break;
            }
            case OpCode::TRANSPOSE: {
                gmm->loadAndLock( args[ 0 ] );
                gmm->allocateAndLock( args[ 1 ] );
                Tensor* x = gmm->getTensor( args[ 0 ]);
                Tensor* res = gmm->getTensor( args[ 1 ]);
                transpose( gmm, x, res );
                gmm->unlock( args[ 0 ] );
                gmm->unlock( args[ 1 ] );
                break;
            }
            case OpCode::COPY: {
                gmm->loadAndLock( args[ 0 ] );
                gmm->allocateAndLock( args[ 1 ] );
                Tensor* x = gmm->getTensor( args[ 0 ]);
                Tensor* res = gmm->getTensor( args[ 1 ]);
                copy( gmm, x, res );
                gmm->unlock( args[ 0 ] );
                gmm->unlock( args[ 1 ] );
                break;
            }
            case OpCode::DEL: {
                gmm->deleteFromMem( args[ 0 ] );
                break;
            }
            case OpCode::ALLOC: {
                auto shape = new TensorShape( args, argc - 1 );
                auto t = new Tensor( *shape, DataType::FLOAT ); // todo data type
                t->setStartAddress( args[ argc - 1 ] );
                gmm->addTensor( t );
                break;
            }
            case OpCode::MUL: {
                gmm->loadAndLock( args[ 0 ] );
                gmm->loadAndLock( args[ 1 ] );
                gmm->allocateAndLock( args[ 2 ] );
                mul( gmm,
                     gmm->getTensor( args[ 0 ] ),
                     gmm->getTensor( args[ 1 ] ),
                     gmm->getTensor( args[ 2 ] ));

                gmm->unlock( args[ 0 ] );
                gmm->unlock( args[ 1 ] );
                gmm->unlock( args[ 2 ] );
                break;
            }
            case OpCode::HADAMARD: {
                gmm->loadAndLock( args[ 0 ] );
                gmm->loadAndLock( args[ 1 ] );
                gmm->allocateAndLock( args[ 2 ] );
                hadamard( gmm,
                          gmm->getTensor( args[ 0 ] ),
                          gmm->getTensor( args[ 1 ] ),
                          gmm->getTensor( args[ 2 ] ));

                gmm->unlock( args[ 0 ] );
                gmm->unlock( args[ 1 ] );
                gmm->unlock( args[ 2 ] );
                break;
            }
            default:
                throw std::runtime_error( "Unknown instruction" );
        }
    }
}
