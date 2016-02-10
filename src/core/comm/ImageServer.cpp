//
// Created by paul on 09/02/16.
//

#include <iostream>
#include "ImageServer.h"

int ImageServer::_interrupted = 0;

ImageServer::ImageServer(ImageStream &stream, std::string address) :
        _stream(stream), _address(address)
{
    std::thread tempThread(&ImageServer::startListener, this);
    std::swap(tempThread, _listenerThread);
    _listenerThread.detach();
}

ImageServer::~ImageServer() {
    _interrupted = true;
}

void ImageServer::handleSignal(int signal_value)
{
    _interrupted = true;
}

void ImageServer::catchSignals(void)
{
    struct sigaction action;
    action.sa_handler = handleSignal;
    action.sa_flags = 0;
    sigemptyset (&action.sa_mask);
    sigaction (SIGINT, &action, NULL);
    sigaction (SIGTERM, &action, NULL);
}

void ImageServer::startListener() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind(_address.c_str());

    catchSignals();

    // The server only stays active as long as its image stream has more images.
    while(!_interrupted) {
        zmq::message_t request;

        try {
            //  Wait for next request from client
            socket.recv (&request);

            // TODO: Parse and interpret different possible requests.

            if (_stream.hasNext()) {
                // Get next image.
                Image16bit tmp = _stream.nextImage();

                //  Send reply back to client
                // Multiply num pixels by 2 to get number of bytes, since each
                //   pixel is two bytes.
                size_t replySize = (size_t) (tmp.rows * tmp.cols * 2);
                zmq::message_t reply (replySize);
                memcpy ((void *) reply.data(), tmp.data, replySize);

                socket.send (reply);
            }
            else {
                // TODO: Handle case when stream is out of images.
                // TODO: Log that a request was received but could not be satisfied.
            }
        }
        catch(zmq::error_t& e) {
            // TODO: Log that the server has received an interrupt signal.
            std::cout << "zmq error encountered " << std::endl;
        }
        if (_interrupted) {
            // TODO: Log that the server is shutting down.
            std::cout << "server shutting down due to interrupt" << std::endl;
            break;
        }
    }

    socket.close();
    context.close();
}
