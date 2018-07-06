//
// Created by Александр Баташев on 20.06.2018.
//

#ifndef ATHENA_ABSTRACTLOSSFUNCTION_H
#define ATHENA_ABSTRACTLOSSFUNCTION_H


#include <core/Node.h>

namespace athena::core::loss {
    class AbstractLossFunction : public Node {
    public:
        AbstractLossFunction ( OpKernel* );

    };
}


#endif //ATHENA_ABSTRACTLOSSFUNCTION_H
