#include "CameraServerZmqContext.h"

zmq::context_t &CameraServerZmqContext::getContext() {
    static zmq::context_t context(1);

    return context;
}

