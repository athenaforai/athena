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
    /**
     * The class encapsulates everything needed for a single training step
     */
    class Session {
    private:
        /**
         * Contains references to all InputNodes in the graph
         */
        std::vector< InputNode* > headNodes;

        /**
         * Contains graph bytecode
         */
        std::vector< vm_word > bytecode;

        /**
         * Contains address of final result
         */
        unsigned long resultCell;

        std::vector< bool > memory_map;
        std::stack< unsigned long > free_mem;

        unsigned long maxMemSize;

        /**
         * Generates bytecode for sub-graph
         * @param logits sub-graph
         * @return bytecode
         */
        std::tuple< std::vector< unsigned long >, unsigned long >
        getByteCode ( Node* logits );

        athena::backend::ExecutorService* executorService {};

    public:
        Session () : resultCell( 0 ), maxMemSize( 0 ) {};

        ~Session () = default;

        /**
         * Generates bytecode for the whole graph
         * @param logits
         */
        void prepare ( Node* logits );

        /**
         * does single training step
         * @return result tensor
         */
        Tensor* run ();

        unsigned long getResultCell ();

        unsigned long getFreeMemCell (); // todo replace with memory manager

        athena::backend::ExecutorService* getExecutorService();
    };
}


#endif //ATHENA_SESSION_H
