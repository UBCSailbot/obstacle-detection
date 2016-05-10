#ifndef OBSTACLE_DETECTION_TCPCAMERACOMMSSUB_H
#define OBSTACLE_DETECTION_TCPCAMERACOMMSSUB_H


#include <iostream>
#include <thread>
#include <signal.h>
#include <errno.h>

#include <zmq.hpp>
#include <io/ImageStream.h>
#include "types/CameraData.h"
#include "AStoppableWorker.h"
#include <exceptions/ZmqException.h>

/* Defines class TCPCameraCommsSub (a subscriber) which recieves object of type CameraData
 * over TCP from a publisher and sends the CameraData over inproc to a client
 */

class TCPCameraCommsSub : public AStoppableWorker {
public:

    /**
     * Initializes this subscriber by opening a connection to the endpoint at
     *  the specified address. The endpoint on the other end of this connection
     *  should be a publisher of vectors of CameraData.
     *
     * Calling this constructor spins up a separate thread that runs until
     *  interrupted. That thread polls both a publisher of CameraData and
     *  a thread that requests CameraData thus received. The latter
     *  thread runs in the same process as this one.
     *
     * @param endpointAddress - the IPv4 address of the endpoint to which
     *  to connect, e.g. "10.42.0.1"
     * @param portNumber - the number of the port to which this server
     *      should bind, e.g. "5555"
     */
    TCPCameraCommsSub(zmq::context_t &context, const std::string &endpointAddress,
                      const std::string &portNumber);

    static const std::string ENDPOINT_NAME;

private:
    void startSubscriber(zmq::context_t &context, const std::string &pubEndpointAddress,
                                const std::string &pubPortNumber);

    const static int POLLTIMEOUT_MS = 2000;
};

#endif //OBSTACLE_DETECTION_TCPCAMERACOMMSSUB_H