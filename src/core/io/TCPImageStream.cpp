#include "TCPImageStream.h"

TCPImageStream::TCPImageStream(const std::string &endpointAddress,
                               const std::string &portNumber) :
    _context(1), _socketToServer(_context, ZMQ_REQ) {
    _socketToServer.connect(("tcp://" + endpointAddress + ":" + portNumber).c_str());
    // deprecatedTODO: Properly initialize _serverHasNext and the size of the images provided.
    _serverHasNext = true;
    _imageHeight = 60;
    _imageWidth = 80;
}

TCPImageStream::~TCPImageStream() {
    _socketToServer.close();
}

Image16bit TCPImageStream::nextImage() {
    zmq::message_t request(IMAGE_REQUEST_SIZE);

    if (!_serverHasNext) {
        throw new EndOfStreamException();
    }

    // Request the next image from the server.
    _socketToServer.send(request);

    //  Get the reply.
    zmq::message_t reply;
    // deprecatedTODO: Error handling: if the message is of the wrong size
    //   or otherwise malformed, retry a couple times. If that fails,
    //   throw an exception.
    int status = _socketToServer.recv(&reply);

    // Deserialize.
    // deprecatedTODO: Encode serverHasNext in image.
    cv::Mat container(_imageHeight, _imageWidth, CV_16UC1, reply.data());
    cv::Mat newImage(_imageHeight, _imageWidth, CV_16UC1);
    container.copyTo(newImage);

    return Image16bit(newImage, false);
}

bool TCPImageStream::hasNext() const {
    return _serverHasNext;
}

int TCPImageStream::getImageWidth() const {
    return _imageWidth;
}

int TCPImageStream::getImageHeight() const {
    return _imageHeight;
}
