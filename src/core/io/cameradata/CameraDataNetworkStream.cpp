//
// Created by denis on 05/06/16.
//

#include <zmq.hpp>
#include <comm/TCPCameraCommsSub.h>
#include "CameraDataNetworkStream.h"
#include "CameraDataDeserializer.h"

int _imageHeight;

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
                                                 const std::string &pubPortNumber) : _context(1),
                                                                                       pairSocket(_context, ZMQ_PAIR) {

    _imageHeight = 60;
    _imageWidth = 80;

    std::string inprocAddress = "inproc://" + TCPCameraCommsSub::ENDPOINT_NAME;
    pairSocket.bind(inprocAddress.c_str());

    // Spins up a separate subscriber thread that receives and stores
    //  the latest images sent by the camera server publisher
    TCPCameraCommsSub sub(_context, pubIPaddress, pubPortNumber);
    pairSocket.bind(inprocAddress.c_str());
}
