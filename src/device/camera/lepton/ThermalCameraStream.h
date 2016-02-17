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

    virtual ~ThermalCameraStream();

    /**
     * Returns the newest frame from the camera. If this function is
     *  called more than once before the camera is able to refresh the
     *  frame, the call blocks until a new frame has taken the place
     *  of the old one.
     */
    Image16bit nextImage() override;

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

private:
    Lepton _lepton;
    std::thread _leptonThread;

    uint16_t* _latestFrame;

    volatile bool _canOverwriteLatestFrame;
    volatile bool _newFrameAvailable;

    /* Provides a lock to make sure that only one thread at a time can check and
 *  modify the _canOverwriteLatestFrame variable. */
    std::mutex _mtx;
    std::condition_variable _cv;

    void startCapture();

    volatile size_t _frameCounter;

};


#endif //OBSTACLE_DETECTION_LEPTONVIDEOSTREAM_H
