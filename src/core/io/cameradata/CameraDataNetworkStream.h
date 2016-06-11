//
// Created by denis on 05/06/16.
//

#ifndef OBSTACLE_DETECTION_DUALLEPTONTCPIMAGESTREAM_H
#define OBSTACLE_DETECTION_DUALLEPTONTCPIMAGESTREAM_H

#include "CameraDataStream.h"

class CameraDataNetworkStream : public CameraDataStream {


public:
    CameraDataNetworkStream(const std::string &pubIPaddress, const std::string &pubPortNumber);


    virtual std::vector<CameraData> nextImage() override;

    virtual bool hasNext() const override;

private:
    zmq::context_t _context;
    zmq::socket_t pairSocket;

    int _imageWidth;
    int _imageHeight;
};

#endif //OBSTACLE_DETECTION_DUALLEPTONTCPIMAGESTREAM_H
