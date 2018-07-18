//
// Created by Александр Баташев on 26.05.2018.
//

#ifndef ATHENA_DATATYPE_H
#define ATHENA_DATATYPE_H

namespace athena::core {

    /**
     * Data type for Tensor
     * FLOAT - single precision floating point number (32 bit)
     * DOUBLE - double precision floating point number (64 bit)
     * INT - signed integer number (32 bit)
     */
    enum class DataType : int {
        FLOAT = 0,
        DOUBLE = 1,
        INT = 2
    };

    unsigned int typesize ( DataType type );
}

#endif //ATHENA_DATATYPE_H
