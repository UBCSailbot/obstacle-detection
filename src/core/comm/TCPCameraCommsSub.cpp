#include "TCPCameraCommsSub.h"

//sub loop interrupt flag
bool TCPCameraCommsSub::interrupt = false;
const std::string TCPCameraCommsSub::ENDPOINT_NAME = "CameraSubObstacleDetectionPair";

void TCPCameraCommsSub::startSubscriber(zmq::context_t &context, const std::string &pubEndpointAddress,
                                        const std::string &pubPortNumber) {

    // Initialize subscriber socket. This receives vectors of CameraData
    //  from a publisher.
    zmq::socket_t imgSubSocket(context, ZMQ_SUB);
    // set message filter on sub socket to accept all messages
    imgSubSocket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    std::string publisherAddress = "tcp://" + pubEndpointAddress + ":" + pubPortNumber;
    imgSubSocket.connect(publisherAddress.c_str());

    // Initialize PAIR socket to talk to obstacle detection thread, running
    //  in the same process.
    zmq::socket_t pairSocket(context, ZMQ_PAIR);
    std::string inprocAddress = "inproc://" + ENDPOINT_NAME;
    pairSocket.connect(inprocAddress.c_str());

    // Create a zmq polling object which will listen to
    //  both the sub and pair sockets for incoming zmq messages.
    zmq_pollitem_t items[2];
    items[0].socket = (void *) imgSubSocket;
    items[0].events = ZMQ_POLLIN;
    items[1].socket = (void *) pairSocket;
    items[1].events = ZMQ_POLLIN;

    // Initialize message objects
    zmq::message_t pairRequest;
    zmq::message_t pairReply;
    zmq::message_t latestImages;
    bool newImagesAvailable = false;
    bool newPairRequestReceived = false;

    //actual sub loop for receiving messages
    //TODO: implement something that actually watches for an interrupt
    while (!interrupt) {
        try {
            int nsockets = zmq::poll((zmq_pollitem_t *) &items, 2, POLLTIMEOUT_MS);

            if (nsockets < 0) {
                throw zmq::error_t();
            }
            else if (nsockets == 0) {
                std::cout << "zmq poll timed out after " << POLLTIMEOUT_MS << " ms. Retrying." << std::endl;
                continue;
            }

            if (items[0].revents & ZMQ_POLLIN) {
                imgSubSocket.recv(&latestImages);
                newImagesAvailable = true;
            }
            if (items[1].revents & ZMQ_POLLIN) {
                pairSocket.recv(&pairRequest);
                newPairRequestReceived = true;
            }
            if (newImagesAvailable && newPairRequestReceived) {
                pairReply.copy(&latestImages);
                pairSocket.send(pairReply);
                newImagesAvailable = false;
                newPairRequestReceived = false;
            }

        } catch (zmq::error_t &e) {
            // TODO: Log zmq error, handle error
            std::cout << "zmq error encountered " << std::endl;
            std::cout << e.what() << std::endl;
        }

        if (interrupt) {
            // TODO: Log that the server is shutting down.
            std::cout << "server shutting down due to interrupt" << std::endl;
            break;
        }
    }
    // closing the sockets is unnecessary because the c++ destructors do this for us
}

TCPCameraCommsSub::TCPCameraCommsSub(zmq::context_t &context, const std::string &endpointAddress,
                                     const std::string &portNumber) {
    std::thread _pollingThread(&TCPCameraCommsSub::startSubscriber, std::ref(context), endpointAddress,
                               portNumber);
    _pollingThread.detach();
}
