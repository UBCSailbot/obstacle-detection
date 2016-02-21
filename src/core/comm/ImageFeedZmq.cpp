#include "ImageFeedZmq.h"

ImageFeedZmq::ImageFeedZmq(zmq::context_t &ctx) :
    m_ctx(ctx), m_socket(NULL) {

}

ImageFeedZmq::~ImageFeedZmq() {
    if (m_socket != NULL) {
        delete m_socket;
    }
}

bool ImageFeedZmq::init(int port) {
    // Create the socket
    m_socket = new zmq::socket_t(m_ctx, ZMQ_PUB);

    std::string zmq_base = "tcp://127.0.0.1:";
    std::string port_str = std::to_string(port);

    // Bind the socket
    m_socket->bind( (zmq_base.append(port_str)).c_str() );


    // Apparently this always succeeds
    return true;
}

bool ImageFeedZmq::sendFrame(const uint8_t *buf, size_t size) {
    // Check that we've initialized first
    if (m_socket == NULL) {
        return false;
    }

    /* We need to allocate our own buffer, because we can't
       assume the one we're given will exist long enough */
    void *nbuf = malloc(size);
    if (nbuf == NULL) {
        return false;
    }
    memcpy(nbuf, buf, size);

    zmq::message_t msg(nbuf, size, ImageFeedZmq::zmqFree);

    // Send the message
    return m_socket->send(msg);
}

void ImageFeedZmq::zmqFree(void *data, void *hint) {
    free(data);
}
