//
// Created by Александр Баташев on 28.05.2018.
//

#include "AbstractOptimizer.h"

void
athena::core::optimizers::AbstractOptimizer::init ( athena::core::Session* session ) {
    if ( session != nullptr ) {
        lastResultCell = session->getResultCell ();
        this->session = session;
    }
}
