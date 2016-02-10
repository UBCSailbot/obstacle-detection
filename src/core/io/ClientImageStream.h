//
// Created by paul on 09/02/16.
//

#ifndef OBSTACLE_DETECTION_CLIENTIMAGESTREAM_H
#define OBSTACLE_DETECTION_CLIENTIMAGESTREAM_H


#include <zmq.hpp>
#include "ImageStream.h"

class ClientImageStream : public ImageStream {

public:
    ClientImageStream(std::string address);
    virtual ~ClientImageStream();

    Image16bit nextImage();

    bool hasNext() const;

    int getImageWidth() const;

    int getImageHeight() const;

private:
    zmq::context_t _context;
    zmq::socket_t _socketToServer;

    bool _serverHasNext;

    static constexpr int IMAGE_REQUEST_SIZE = 1;
};


#endif //OBSTACLE_DETECTION_CLIENTIMAGESTREAM_H
