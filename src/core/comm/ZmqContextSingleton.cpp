#include "ZmqContextSingleton.h"

zmq::context_t& ZmqContextSingleton::getContext() {
    static zmq::context_t context(1);

    return context;
}
