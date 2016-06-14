#ifndef OBSTACLE_DETECTION_CAMERADATAIMAGESTREAMADAPTER_H
#define OBSTACLE_DETECTION_CAMERADATAIMAGESTREAMADAPTER_H


#include "io/ImageStream.h"
#include "CameraDataStream.h"

/*
 * This class is meant to provide and interface the old ImageStream and the new CameraDataStream interface
 */
class CameraDataImageStreamAdapter : ImageStream {

public:

    CameraDataImageStreamAdapter(CameraDataStream *cameraDataStream);

    virtual ~CameraDataImageStreamAdapter();

    virtual Image16bit nextImage() override;

    virtual bool hasNext() const override;

    virtual int getImageWidth() const override;

    virtual int getImageHeight() const override;

protected:
    CameraDataStream *_cameraDataStream;

    int _imageHeight;

    int _imageWidth;

};


#endif //OBSTACLE_DETECTION_CAMERADATAIMAGESTREAMADAPTER_H
