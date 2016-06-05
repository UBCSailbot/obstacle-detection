//
// Created by denis on 04/06/16.
//

#include "CameraDataImageStreamAdapter.h"

CameraDataImageStreamAdapter::CameraDataImageStreamAdapter(CameraDataStream *cameraDataStream) :
        cameraDataStream(cameraDataStream) { }

Image16bit CameraDataImageStreamAdapter::nextImage() {
    return cameraDataStream->nextImage()[0].frame;
}

bool CameraDataImageStreamAdapter::hasNext() const {
    return cameraDataStream->hasNext();
}

int CameraDataImageStreamAdapter::getImageWidth() const {
    return cameraDataStream->getImageWidth();
}

int CameraDataImageStreamAdapter::getImageHeight() const {
    return cameraDataStream->getImageHeight();
}
