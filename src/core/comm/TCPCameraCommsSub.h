#ifndef OBSTACLE_DETECTION_TCPCAMERACOMMSSUB_H
#define OBSTACLE_DETECTION_TCPCAMERACOMMSSUB_H


#include <iostream>
#include <thread>
#include <signal.h>
#include <zmq.hpp>
#include <io/ImageStream.h>

/* Defines class TCPCameraCommsSub (a subscriber) which recieves object of type CameraData over TCP from a publisher*/

class TCPCameraCommsSub {
    public:
        TCPCameraCommsSub(const std::string &endpointAddress, const std::string &portNumber);

        static bool reqCheck();
        static bool frameCheck();
        static void startSubscriber(zmq::context_t context, const std::string &endpointAddress,
                                    const std::string &portNumber);

    private:
        static int interrupt;
};

#endif //OBSTACLE_DETECTION_TCPCAMERACOMMSSUB_H