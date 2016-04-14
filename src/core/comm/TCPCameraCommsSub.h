#ifndef OBSTACLE_DETECTION_TCPCAMERACOMMSSUB_H
#define OBSTACLE_DETECTION_TCPCAMERACOMMSSUB_H


#include <iostream>
#include <thread>
#include <signal.h>
#include <errno.h>

#include <zmq.hpp>
#include <io/ImageStream.h>
#include "types/CameraData.h"
#include <exceptions/ZmqException.h>

/* Defines class TCPCameraCommsSub (a subscriber) which recieves object of type CameraData over TCP from a publisher*/

class TCPCameraCommsSub {
    public:
        TCPCameraCommsSub(const std::string &endpointAddress, const std::string &portNumber);

        void startSubscriber(zmq::context_t context, const std::string &endpointAddress,
                                    const std::string &portNumber);
        static const std::string ENDPOINT_NAME = "CameraSubObstacleDetectionPair";
    private:
        static bool interrupt;
        const static int POLLTIMEOUT_MS = 200;
};

#endif //OBSTACLE_DETECTION_TCPCAMERACOMMSSUB_H