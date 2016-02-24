#ifndef OBSTACLE_DETECTION_LEPTONIMAGESERVER_H
#define OBSTACLE_DETECTION_LEPTONIMAGESERVER_H


#include <iostream>
#include <thread>
#include <signal.h>

#include <zmq.hpp>

#include <io/ImageStream.h>

/**
 * Defines a server that listens for requests over TCP and replies with
 *  images obtained from a given ImageStream.
 */
class TCPImageServer {

  public:

    /**
     * Sets up a TCPImageServer bound to the given address to
     *  serve out images from the given stream over TCP. This spins up
     *  a separate thread that listens for incoming requests at that
     *  address.
     *
     * @param stream - the ImageStream from which to serve images.
     * @param endpointAddress - the IPv4 address of the endpoint to which
     *      this server should bind, e.g. "10.42.0.1"
     * @param portNumber - the number of the port to which this server
     *      should bind, e.g. "5555"
     */
    TCPImageServer(ImageStream &stream, const std::string &endpointAddress,
                   const std::string &portNumber);

    virtual ~TCPImageServer();

  private:
    ImageStream &_stream;
    std::string _fullAddress;

    std::thread _listenerThread;
    static int _interrupted;

    void startListener();

    static void handleSignal(int signal_value);

    static void catchSignals(void);
};


#endif //OBSTACLE_DETECTION_LEPTONIMAGESERVER_H
