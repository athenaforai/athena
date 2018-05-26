//
// Created by Александр Баташев on 26.05.2018.
//

#include "GenericExecutor.h"

athena::backend::generic::GenericExecutor::GenericExecutor(std::vector<int>, int maxMem) {
    memory = new athena::core::Tensor &[maxMem];
}

void athena::backend::generic::GenericExecutor::execute() {

}
