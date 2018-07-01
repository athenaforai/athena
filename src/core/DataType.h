//
// Created by Александр Баташев on 26.05.2018.
//

#ifndef ATHENA_DATATYPE_H
#define ATHENA_DATATYPE_H

namespace athena::core {

    enum class DataType : int {
        FLOAT = 0,
        DOUBLE = 1,
        INT = 2
    };

    unsigned int typesize ( DataType type );
}

#endif //ATHENA_DATATYPE_H
