#include "CameraDataImageStreamAdapter.h"

CameraDataImageStreamAdapter::CameraDataImageStreamAdapter(CameraDataStream *cameraDataStream) :
        _cameraDataStream(cameraDataStream) {
    // This is necessary in order to get the real height and width
    CameraSpecifications &imageSpecs = cameraDataStream->nextImage()[0].imageSpecs;
    _imageHeight = imageSpecs.pixelHeight;
    _imageWidth = imageSpecs.pixelWidth;
}

Image16bit CameraDataImageStreamAdapter::nextImage() {
    return _cameraDataStream->nextImage()[0].frame;
}

bool CameraDataImageStreamAdapter::hasNext() const {
    return _cameraDataStream->hasNext();
}

int CameraDataImageStreamAdapter::getImageWidth() const {
    return _imageWidth;
}

int CameraDataImageStreamAdapter::getImageHeight() const {
    return _imageHeight;
}

CameraDataImageStreamAdapter::~CameraDataImageStreamAdapter() {
    delete (_cameraDataStream);
}


