//
// Created by denis on 05/06/16.
//

#include <zmq.hpp>
#include <comm/ZmqContextSingleton.h>
#include "CameraDataNetworkStream.h"
#include "CameraDataDeserializer.h"

std::vector<CameraData> CameraDataNetworkStream::nextImage() {
    zmq::message_t request;
    zmq::message_t reply;

    pairSocket_.send(request);
    pairSocket_.recv(&reply);

    return CameraDataDeserializer::deserializeFromZmq(reply);
}

bool CameraDataNetworkStream::hasNext() const {
    return true;
}

CameraDataNetworkStream::CameraDataNetworkStream(const std::string &pubIPaddress,
                                                 const std::string &pubPortNumber) : context_(
        ZmqContextSingleton::getContext()), pairSocket_(context_, ZMQ_PAIR), sub_(context_, pubIPaddress,
                                                                                  pubPortNumber) {
    std::string inprocAddress = "inproc://" + TCPCameraCommsSub::ENDPOINT_NAME;

    // Spins up a separate subscriber thread that receives and stores
    //  the latest images sent by the camera server publisher
    pairSocket_.bind(inprocAddress.c_str());
}
