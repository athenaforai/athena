//
// Created by Александр Баташев on 27.05.2018.
//

#include "DataType.h"

namespace athena::core {
    unsigned int typesize ( DataType type ) {
        switch ( type ) {
            case DataType::FLOAT:
                return sizeof( float );
            case DataType::DOUBLE:
                return sizeof( double );
            case DataType::INT:
                return sizeof( int );
        }
    };
}