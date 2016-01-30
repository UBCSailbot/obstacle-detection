#ifndef _ZMQCONTEXTSINGLETON_H
#define _ZMQCONTEXTSINGLETON_H

#include <zmq.hpp>

class ZmqContextSingleton {
public:
    static zmq::context_t& getContext();
};

#endif /* _ZMQCONTEXTSINGLETON_H */
