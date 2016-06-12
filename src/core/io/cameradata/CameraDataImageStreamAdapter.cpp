//
// Created by denis on 04/06/16.
//

#include "CameraDataImageStreamAdapter.h"

CameraDataImageStreamAdapter::CameraDataImageStreamAdapter(CameraDataStream *cameraDataStream) :
        _cameraDataStream(cameraDataStream) { }

Image16bit CameraDataImageStreamAdapter::nextImage() {
    return _cameraDataStream->nextImage()[0].frame;
}

bool CameraDataImageStreamAdapter::hasNext() const {
    return _cameraDataStream->hasNext();
}

int CameraDataImageStreamAdapter::getImageWidth() const {
    return _cameraDataStream->nextImage()[0].imageSpecs.pixelWidth;
}

int CameraDataImageStreamAdapter::getImageHeight() const {
    return _cameraDataStream->nextImage()[0].imageSpecs.pixelHeight;
}
