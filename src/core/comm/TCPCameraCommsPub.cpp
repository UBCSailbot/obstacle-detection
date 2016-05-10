#include "TCPCameraCommsPub.h"

const std::string TCPCameraCommsPub::ENDPOINT_NAME = "CameraPubCommandListenerPair";

volatile bool TCPCameraCommsPub::_terminate = false;

void TCPCameraCommsPub::startPublisher(zmq::context_t &context, const std::string &endpointAddress,
                                      const std::string &portNumber, ICameraMultiplexer &cameraMux) {
    zmq::socket_t imgPubSocket(context, ZMQ_PUB);
    std::string fullAddress = "tcp://" + endpointAddress + ":" + portNumber;
    imgPubSocket.bind(fullAddress.c_str());

    while (!_terminate) {
        std::vector<CameraData> camDataVector = cameraMux.getLatestCameraData();
        zmq::message_t pubMessage = CameraDataSerializer::serializeToZmq(camDataVector);
        imgPubSocket.send(pubMessage);

        // TODO: Redirect to logger
        if(_terminate){
            std::cout << "Publisher shutting down due to termination request " << std::endl;
            break;
        }
    }
}

TCPCameraCommsPub::TCPCameraCommsPub(zmq::context_t &context, const std::string &endpointAddress,
                                     const std::string &portNumber, ICameraMultiplexer &cameraMux) {
    std::thread _pubThread(&TCPCameraCommsPub::startPublisher, std::ref(context), std::ref(endpointAddress),
                           std::ref(portNumber), std::ref(cameraMux));
    _pubThread.detach();
}

void TCPCameraCommsPub::stop() {
    _terminate = true;
}
