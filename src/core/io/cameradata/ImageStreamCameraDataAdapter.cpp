#include <camera/lepton/LeptonCameraSpecifications.h>
#include "ImageStreamCameraDataAdapter.h"


std::vector<CameraData> ImageStreamCameraDataAdapter::nextImage() {
    CameraData cameraData = {OK, LeptonCameraSpecifications, _imageStream->nextImage()};
    std::vector<CameraData> cameraDataVector;
    cameraDataVector.push_back(cameraData);
    if (_doubleUp) {
        cameraDataVector.push_back(cameraData);
    }
    return cameraDataVector;
}

bool ImageStreamCameraDataAdapter::hasNext() const {
    return _imageStream->hasNext();
}

ImageStreamCameraDataAdapter::ImageStreamCameraDataAdapter(ImageStream *imageStream, bool doubleUp)
        : _imageStream(imageStream), _doubleUp(doubleUp) { }

ImageStreamCameraDataAdapter::~ImageStreamCameraDataAdapter() {
    delete (_imageStream);
};
