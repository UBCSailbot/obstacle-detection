//

#include "HorizonFactory.h"

//
// Created by paul on 17/01/16.

HorizonFactory::HorizonFactory(ICameraSpecifications specs) : _cameraSpecs(specs) { }


Horizon HorizonFactory::makeHorizon(Orientation o) const {
    double pitchShift = pitchHorizonPixelShift(o.pitchRadians, _cameraSpecs);
    double heightLeft = (int) (pitchShift + _cameraSpecs.pixelHeight / 2);
    double heightRight = (int) (pitchShift + _cameraSpecs.pixelHeight / 2);

    double rollShift = rollHorizonPixelShift(o.rollRadians, _cameraSpecs);
    heightLeft -= rollShift;
    heightRight += rollShift;

    // XXX: Assumes that the horizon intersects both
    //  vertical edges of the frame
    return Horizon(cv::Point2f(0, heightLeft),
                   cv::Point2f(_cameraSpecs.pixelWidth, heightRight));
}

double HorizonFactory::pitchHorizonPixelShift(double angle, ICameraSpecifications spec) const {
    return angle * 180 / (spec.FOVDegreesVertical * M_PI) * spec.pixelHeight;
}

double HorizonFactory::rollHorizonPixelShift(double angle, ICameraSpecifications spec) const {
    if (std::abs(angle - M_PI / 2) < 0.0001) {
        return std::numeric_limits<double>::max();
    } else {
        return tan(angle) * (double) spec.pixelWidth / 2.0;
    }
}

Horizon HorizonFactory::makeNeutralHorizon() const {
    return Horizon(cv::Point2f(0, _cameraSpecs.pixelHeight / 2),
                   cv::Point2f(_cameraSpecs.pixelWidth / 2, _cameraSpecs.pixelHeight / 2));
}
