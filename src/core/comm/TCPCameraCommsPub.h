#ifndef OBSTACLE_DETECTION_TCPCAMERACOMMSPUB_H
#define OBSTACLE_DETECTION_TCPCAMERACOMMSPUB_H

#include <iostream>
#include <thread>
#include <signal.h>
#include <errno.h>

#include <zmq.hpp>
#include <io/ImageStream.h>
#include "types/CameraData.h"
#include <exceptions/ZmqException.h>
#include <camera/ICameraMultiplexer.h>
#include <io/CameraDataSerializer.h>

/* Defines class TCPCameraCommsPub (a publisher) which sends object of type CameraData over TCP to a subscriber*/

class TCPCameraCommsPub {
public:
    TCPCameraCommsPub(zmq::context_t &context, const std::string &endpointAddress,
                      const std::string &portNumber, ICameraMultiplexer &cameraMux);

    static const std::string ENDPOINT_NAME;

private:
    static bool interrupted;
    static void startPublisher(zmq::context_t &context, const std::string &endpointAddress,
                                  const std::string &portNumber, ICameraMultiplexer &cameraMux);
};


#endif //OBSTACLE_DETECTION_TCPCAMERACOMMSPUB_H
