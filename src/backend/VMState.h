//
// Created by Александр Баташев on 29.07.2018.
//

#ifndef ATHENA_VMSTATE_H
#define ATHENA_VMSTATE_H

namespace athena::backend {

    /**
     * VMState structure describes current state of executor thread
     */
    struct VMState {

        /**
         * Batch Counter, number of batches
         */
        unsigned long BC = 1;

        /**
         * Batch Pointer, number of current batch
         */
        unsigned long BP = 0;

        /**
         * Instruction Pointer, points to instruction that is going to be executed
         */
        unsigned long IP = 0;



    };

}

#endif //ATHENA_VMSTATE_H
