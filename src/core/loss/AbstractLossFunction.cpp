//
// Created by Александр Баташев on 20.06.2018.
//

#include "AbstractLossFunction.h"

athena::core::loss::AbstractLossFunction::AbstractLossFunction (
        athena::core::OpKernel* opKernel
) : Node( opKernel ) {
}
