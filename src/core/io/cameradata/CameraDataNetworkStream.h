//
// Created by denis on 05/06/16.
//

#ifndef OBSTACLE_DETECTION_DUALLEPTONTCPIMAGESTREAM_H
#define OBSTACLE_DETECTION_DUALLEPTONTCPIMAGESTREAM_H

#include "CameraDataStream.h"
#include <comm/TCPCameraCommsSub.h>

class CameraDataNetworkStream : public CameraDataStream {


public:
    CameraDataNetworkStream(const std::string &pubIPaddress, const std::string &pubPortNumber);

    virtual std::vector<CameraData> nextImage() override;

    virtual bool hasNext() const override;

private:
    zmq::context_t &context_;
    zmq::socket_t pairSocket_;
    TCPCameraCommsSub sub_;

};

#endif //OBSTACLE_DETECTION_DUALLEPTONTCPIMAGESTREAM_H
