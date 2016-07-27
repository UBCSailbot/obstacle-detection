#ifndef _IMAGEFEEDZMQ
#define _IMAGEFEEDZMQ

#include "ZmqContextSingleton.h"
#include <zmq.hpp>
#include <cstdint>
#include <iostream>
#include <string>
class ImageFeedZmq {
  private:
    zmq::context_t &m_ctx;
    zmq::socket_t *m_socket;

  public:
    ImageFeedZmq(zmq::context_t &ctx);
    ~ImageFeedZmq();
    bool init(const std::string &portNum);
    bool sendFrame(const uint8_t *buf, size_t size);
    static void zmqFree(void *data, void *hint);
};

#endif /* _IMAGEFEEDZMQ */
