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

    unsigned int typesize(DataType type) {
        switch (type) {
            case DataType::FLOAT:
                return sizeof(float);
            case DataType::DOUBLE:
                return sizeof(double);
            case DataType::INT:
                return sizeof(int);
        }
    };

//    std::type_info& cpptype(DataType type) {
//        switch (type) {
//            case DataType::FLOAT:
//                return typeid(float);
//            case DataType::DOUBLE:
//                return typeid(double);
//            case DataType::INT:
//                return typeid(int);
//        }
//    }
}

#endif //ATHENA_DATATYPE_H
