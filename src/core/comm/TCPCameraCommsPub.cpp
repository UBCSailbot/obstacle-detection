#include "TCPCameraCommsPub.h"

void TCPCameraCommsPub::startPublisher(zmq::context_t context, const std::string &endpointAddress,
                                       const std::string &portNumber, ICameraMultiplexer &cameraMux) {
    zmq::socket_t imgPubSocket(context, ZMQ_PUB);
    imgPubSocket.bind(("tcp://" + endpointAddress + ":" + portNumber).c_str());

    while (!interrupted) {
        std::vector<CameraData> camDataVector = cameraMux.getLatestCameraData();
        zmq::message_t pubMessage = CameraDataSerializer::serializeToZmq(camDataVector);
        imgPubSocket.send(pubMessage);

        if(interrupted){
            std::cout << "Publisher shutting down due to interrupt" << std::endl;
            break;
        }
    }
}
TCPCameraCommsPub::TCPCameraCommsPub(zmq::context_t context, const std::string &endpointAddress,
                                     const std::string &portNumber, ICameraMultiplexer &cameraMux) {
    std::thread _pubThread(TCPCameraCommsPub::startPublisher, std::ref(context), endpointAddress, portNumber, cameraMux);
    _pubThread.detach();
}
