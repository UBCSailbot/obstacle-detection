#include <io/CameraDataDeserializer.h>
#include "TCPCameraCommsSub.h"

//sub loop interrupt flag
int TCPCameraCommsSub::interrupt = false;


void TCPCameraCommsSub::startSubscriber(zmq::context_t context, const std::string &endpointAddress,
                                        const std::string &portNumber){

    //initialize sub socket and inproc obstacle detection socket
    zmq::socket_t imgSubSocket(context, ZMQ_SUB);
    zmq::socket_t ipcObDecSocket(context, ZMQ_REP);

    //sets message filter on sub socket to accept all messages
    imgSubSocket.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    //connects sub socket and binds inproc socket
    imgSubSocket.connect(("tcp://" + endpointAddress + ":" + portNumber).c_str());
    std::string inprocAddress = "inproc://" + ENDPOINT_NAME;
    ipcObDecSocket.bind(inprocAddress.c_str());

    // create poll item which will check for sub and inproc sockets being triggered
    // ZMQ_POLLIN allows at least one message to be received from any socket without blocking
    zmq_pollitem_t items[2];
    items[0].socket = (void *) imgSubSocket;
    items[0].events = ZMQ_POLLIN;
    items[1].socket = (void *) ipcObDecSocket;
    items[1].events = ZMQ_POLLIN;

    //creates messages to be sent/recieved
    zmq::message_t requestMessage;
    zmq::message_t replyMessage;
    zmq::message_t latestImageMessage;
    bool newImageAvailable = false;
    bool newRequestReceived = false;

    //actual sub loop for recieving messages
    //TODO: implement something that actually watches for an interrupt, look at TCPImageServer.cpp
    while (!interrupt){
        try {
            int nsockets = zmq::poll((zmq_pollitem_t *) &items, 2, POLLTIMEOUT_MS);

            if (nsockets < 0){
                throw zmq::error_t();
            }else if (nsockets == 0){
                std::cout << "zmq poll timed out after " << POLLTIMEOUT_MS << " ms. Retrying." << std::endl;
                continue;
            }
            if(items[0].revents & ZMQ_POLLIN) {
                imgSubSocket.recv(&latestImageMessage);
                newImageAvailable = true;
            }
            if(items[1].revents & ZMQ_POLLIN) {
                ipcObDecSocket.recv(&requestMessage);
                newRequestReceived = true;
            }
            if(newImageAvailable && newRequestReceived){
                latestImageMessage.copy(&replyMessage);
                ipcObDecSocket.send(replyMessage);
                newImageAvailable = false;
                newRequestReceived = false;
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
    //closing the sockets is unnecessary because the c++ destructors do this for us
}