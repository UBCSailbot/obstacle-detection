#ifndef OBSTACLE_DETECTION_CAMERAENCLOSUREZMQCONTEXT_H
#define OBSTACLE_DETECTION_CAMERAENCLOSUREZMQCONTEXT_H

#include <zmq.hpp>

/**
 * This class provides a single global context for
 *  the camera enclosure server process.
 *  This avoids unnecessary duplication of i/o threads,
 *  since each ZMQ context has at least 1 i/o thread to
 *  itself.
 */
class CameraServerZmqContext {
public:
    static zmq::context_t &getContext();
};


#endif //OBSTACLE_DETECTION_CAMERAENCLOSUREZMQCONTEXT_H
