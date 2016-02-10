//
// Created by paul on 09/02/16.
//

#include "ClientImageStream.h"

ClientImageStream::ClientImageStream(std::string address) :
        _context(1), _socketToServer(_context, ZMQ_REQ)
{
    _socketToServer.connect(address.c_str());
    _serverHasNext = false;
}

ClientImageStream::~ClientImageStream() {
    _context.close();
    _socketToServer.close();
}

Image16bit ClientImageStream::nextImage() {
    zmq::message_t request(IMAGE_REQUEST_SIZE);

    // TODO: Check if the server has more images.
    // First send a request to update _serverHasNext.

    // If all is well, request the next image from the server.
    _socketToServer.send(request);

    //  Get the reply.
    zmq::message_t reply;
    _socketToServer.recv (&reply);

    // Deserialize.
    // TODO: Encode size of image in message.
    cv::Mat container(60, 80, CV_16UC1, reply.data());
    cv::Mat newImage(60, 80, CV_16UC1);
    container.copyTo(newImage);

    return Image16bit(newImage, false);
}

bool ClientImageStream::hasNext() const {
    return _serverHasNext;
}

int ClientImageStream::getImageWidth() const {
    // TODO: Implement.
    return 0;
}

int ClientImageStream::getImageHeight() const {
    // TODO: Implement.
    return 0;
}
