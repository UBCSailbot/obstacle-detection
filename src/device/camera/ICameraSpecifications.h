//
// Created by paul on 17/01/16.
//

#ifndef OBSTACLE_DETECTION_ICAMERASPECIFICATIONS_H
#define OBSTACLE_DETECTION_ICAMERASPECIFICATIONS_H

/**
 * A data type for storing the parameters of cameras.
 *
 * When defining an instance of this data type, it is important
 *  to define it in a header file so that it can be
 *  included in the core compilation unit without having to include
 *  the rest of the device-specific code. For that to work, make
 *  sure your instance is a const variable so that it can be
 *  included in multiple files.
 */
struct ICameraSpecifications {
    unsigned int pixelHeight;
    unsigned int pixelWidth;

    double FOVDegreesVertical;
    double FOVDegreesHorizontal;
};

#endif //OBSTACLE_DETECTION_ICAMERASPECIFICATIONS_H
