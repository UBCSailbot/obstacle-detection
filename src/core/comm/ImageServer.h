//
// Created by paul on 09/02/16.
//

#ifndef OBSTACLE_DETECTION_LEPTONIMAGESERVER_H
#define OBSTACLE_DETECTION_LEPTONIMAGESERVER_H


#include <signal.h>

#include <io/ImageStream.h>
#include <zmq.hpp>
#include <thread>

class ImageServer {

public:

    /**
     * Sets up an ImageServer bound to the given address to
     *  serve out images from the given stream.
     */
    ImageServer(ImageStream &stream, std::string address);

    virtual ~ImageServer();

private:
    ImageStream &_stream;
    std::string _address;

    std::thread _listenerThread;
    static int _interrupted;

    void startListener();

    static void handleSignal(int signal_value);

    static void catchSignals(void);
};


#endif //OBSTACLE_DETECTION_LEPTONIMAGESERVER_H
