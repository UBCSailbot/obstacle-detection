#ifndef OBSTACLE_DETECTION_CLIENTIMAGESTREAM_H
#define OBSTACLE_DETECTION_CLIENTIMAGESTREAM_H


#include <zmq.hpp>

#include "ImageStream.h"
#include <exceptions/EndOfStreamException.h>


/**
 * @deprecated (2016-05-10) - instead use TCPCameraCommsSub
 *
 * An image stream that relays images that it receives over a
 *  TCP connection.
 */
class TCPImageStream: public ImageStream {

  public:

    /**
     * Initializes this image stream by opening a connection to the endpoint at
     *  the specified address. The endpoint on the other end of this connection
     *  should be capable of sending images when queried.
     *
     * @param endpointAddress - the IPv4 address of the endpoint to which
     *  to connect, e.g. "10.42.0.1"
     * @param portNumber - the number of the port to which this server
     *      should bind, e.g. "5555"
     */
    TCPImageStream(const std::string &endpointAddress, const std::string &portNumber);

    virtual ~TCPImageStream();

    /**
     * Queries the endpoint to which this TCPImageStream is connected
     *  for an image, and returns that image. This is a blocking call.
     */
    Image16bit nextImage() override;

    /**
     * @return whether or not the endpoint to which this stream is connected
     *  has any more images. This is a non-blocking call.
     */
    bool hasNext() const override;

    /**
     * A non-blocking call.
     */
    int getImageWidth() const override;

    /**
     * A non-blocking call.
     */
    int getImageHeight() const override;

  private:
    zmq::context_t _context;
    zmq::socket_t _socketToServer;

    bool _serverHasNext;
    int _imageWidth;
    int _imageHeight;

    static constexpr int IMAGE_REQUEST_SIZE = 1;
};


#endif //OBSTACLE_DETECTION_CLIENTIMAGESTREAM_H
