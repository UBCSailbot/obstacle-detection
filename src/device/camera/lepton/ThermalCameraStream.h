#ifndef OBSTACLE_DETECTION_THERMALCAMERASTREAM2_H
#define OBSTACLE_DETECTION_THERMALCAMERASTREAM2_H


#include <io/ImageStream.h>
#include "Lepton.h"

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
    std::chrono::time_point<std::chrono::system_clock> _lastCaptureTime;
    double _periodSeconds;

    uint16_t *_frameBuffer;
};


#endif //OBSTACLE_DETECTION_THERMALCAMERASTREAM2_H
