#include "AStoppableWorker.h"

/**
 * Even though the destructor for this class is pure virtual,
 *  we still need to define the destructor so that
 *  inheriting classes need not worry about impementing
 *  their own.
 */
AStoppableWorker::~AStoppableWorker() {}

void AStoppableWorker::stop() {
    _terminate = true;
}
