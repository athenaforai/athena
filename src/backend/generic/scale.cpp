#include <core/Tensor.h>
#include <core/DataType.h>

namespace athena::backend::generic
{
    athena::core::Tensor* scale (
            athena::core::Tensor* c,
            athena::core::Tensor* src ) {
        if(c == nullptr || src == nullptr)
            return nullptr;
        unsigned long idx = 0;
        unsigned long size = src->getShape().totalSize();
        auto cNum = *(double*)(c->get(&idx));

        if(src->getType() == athena::core::DataType::DOUBLE)
        {
            auto p_src = (double*)src->raw();
            auto p_dest = new double[size];
#pragma omp parallel for
            for( unsigned long i = 0; i < size; i++)
                p_dest[i] = cNum * p_src[i];
            return new athena::core::Tensor(src->getShape(),
                                            src->getType(),
                                            (unsigned char*)p_dest);
        }else if(src->getType() == athena::core::DataType::FLOAT)
        {
            auto p_src = (float*)src->raw();
            auto p_dest = new float[size];
#pragma omp parallel for
            for( unsigned long i = 0; i < size; i++)
                p_dest[i] = static_cast<float>(cNum * p_src[i]);
            return new athena::core::Tensor(src->getShape(),
                                            src->getType(),
                                            (unsigned char*)p_dest);
        }else if(src->getType() == athena::core::DataType::INT)
        {
            auto p_src = (int*)src->raw();
            auto p_dest = new int[size];
#pragma omp parallel for
            for( unsigned long i = 0; i < size; i++)
                p_dest[i] = static_cast<int>(cNum * p_src[i]);
            return new athena::core::Tensor(src->getShape(),
                                            src->getType(),
                                            (unsigned char*)p_dest);
        }else
            return nullptr;

    }
};

