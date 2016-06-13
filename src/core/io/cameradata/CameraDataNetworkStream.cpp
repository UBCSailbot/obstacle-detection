//
// Created by denis on 05/06/16.
//

#include <zmq.hpp>
#include <comm/TCPCameraCommsSub.h>
#include "CameraDataNetworkStream.h"
#include "CameraDataDeserializer.h"

std::vector<CameraData> CameraDataNetworkStream::nextImage() {
    zmq::message_t request;
    zmq::message_t reply;

    pairSocket.send(request);
    pairSocket.recv(&reply);

    return CameraDataDeserializer::deserializeFromZmq(reply);
}

bool CameraDataNetworkStream::hasNext() const {
    return true;
}


CameraDataNetworkStream::CameraDataNetworkStream(const std::string &pubIPaddress,
                                                 const std::string &pubPortNumber) : pairSocket(_context, ZMQ_PAIR) {

    std::string inprocAddress = "inproc://" + TCPCameraCommsSub::ENDPOINT_NAME;

    // Spins up a separate subscriber thread that receives and stores
    //  the latest images sent by the camera server publisher
    TCPCameraCommsSub sub(_context, pubIPaddress, pubPortNumber);
    pairSocket.bind(inprocAddress.c_str());
}
