//
// Created by paul on 25/01/16.
//

#include "HorizonImage.h"

HorizonImage::HorizonImage(cv::Mat image, const Horizon &h) :
    _image(image), _horizon(h) { }

Horizon HorizonImage::getHorizon() const {
    return _horizon;
}

cv::Mat HorizonImage::getImage() const {
    return _image;
}

Line HorizonImage::calculateCenterLine() const {
    Vector2d horizonVector = _horizon.getVector();

    Vector2d normalToHorizon(-horizonVector.y, horizonVector.x);

    cv::Point2f centerOfFrame(_image.cols / 2, _image.rows / 2);
    Line centerline(centerOfFrame, cv::Point2d(centerOfFrame.x + normalToHorizon.x,
                                               centerOfFrame.y + normalToHorizon.y));
    return centerline;
}
