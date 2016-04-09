#ifndef OBSTACLE_DETECTION_ICAMERASPECIFICATIONS_H
#define OBSTACLE_DETECTION_ICAMERASPECIFICATIONS_H

#include <stddef.h>

/**
 * A data type for storing the parameters of cameras.
 *
 * When defining an instance of this data type, it is important
 *  to define it in a header file so that it can be
 *  included in the core compilation unit without having to include
 *  the rest of the device-specific code. For that to work, make
 *  sure your instance is a const variable so that it can be
 *  included in multiple files. For an example of how to do this,
 *  see device/camera/lepton/LeptonCameraSpecifications.h
 */
struct CameraSpecifications {
public:
    const unsigned int pixelHeight;
    const unsigned int pixelWidth;
    const size_t bytesPerPixel;

    const double FOVDegreesVertical;
    const double FOVDegreesHorizontal;
};

/**
 * Returns whether two CameraSpecifications objects are identical by comparing
 *  each of their fields for equality. This function makes it possible to use
 *  the '==' operator to compare two instances of CameraSpecifications.
 */
bool operator==(const CameraSpecifications &lhs, const CameraSpecifications &rhs);

#endif //OBSTACLE_DETECTION_ICAMERASPECIFICATIONS_H
