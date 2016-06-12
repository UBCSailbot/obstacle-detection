//
// Created by denis on 04/06/16.
//

#ifndef OBSTACLE_DETECTION_CAMERADATAIMAGESTREAMADAPTER_H
#define OBSTACLE_DETECTION_CAMERADATAIMAGESTREAMADAPTER_H


#include "io/ImageStream.h"
#include "CameraDataStream.h"

class CameraDataImageStreamAdapter : ImageStream {

public:

    CameraDataImageStreamAdapter(CameraDataStream *cameraDataStream);

    virtual Image16bit nextImage() override;

    virtual bool hasNext() const override;

    virtual int getImageWidth() const override;

    virtual int getImageHeight() const override;

protected:
    CameraDataStream *_cameraDataStream;

};


#endif //OBSTACLE_DETECTION_CAMERADATAIMAGESTREAMADAPTER_H
