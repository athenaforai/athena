//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_SESSION_H
#define ATHENA_SESSION_H

#include "Node.h"
#include "InputNode.h"
#include <stack>
#include <backend/ExecutorService.h>

namespace athena::core {
    class Session {
    private:
        std::vector< InputNode* > headNodes;
        std::vector< vm_word > bytecode;
        unsigned long resultCell;

        std::vector< bool > memory_map;
        std::stack< unsigned long > free_mem;

        unsigned long maxMemSize;

        std::tuple< std::vector< unsigned long >, unsigned long >
        getByteCode ( Node* logits );

        athena::backend::ExecutorService* executorService {};

    public:
        Session () : resultCell( 0 ), maxMemSize( 0 ) {};

        ~Session () = default;

        void prepare ( Node* logits );

        Tensor* run ();

        unsigned long getResultCell ();

        unsigned long getFreeMemCell (); // todo replace with memory manager
    };
}


#endif //ATHENA_SESSION_H
