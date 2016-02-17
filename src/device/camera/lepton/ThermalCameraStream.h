#ifndef OBSTACLE_DETECTION_LEPTONVIDEOSTREAM_H
#define OBSTACLE_DETECTION_LEPTONVIDEOSTREAM_H


#include <io/ImageStream.h>
#include "Lepton.h"

/**
 * Exposes a connection to an infrared camera as an
 *  ImageStream, in effect encapsulating a live video stream as a
 *  stream of individual frames.
 */
class ThermalCameraStream : public ImageStream {

public:

    ThermalCameraStream(Lepton camera);

    /**
     * @return Always returns true, since a camera is in theory
     *  an infinite source of images.
     */
    bool hasNext() const override;

    /**
     * @return The width of the frames output by the underlying camera, in pixels.
     */
    int getImageWidth() const override;

    /**
     * @return The height of the frames output by the underlying camera, in pixels.
     */
    int getImageHeight() const override;

};


#endif //OBSTACLE_DETECTION_LEPTONVIDEOSTREAM_H
