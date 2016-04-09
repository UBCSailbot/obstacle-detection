//
// Created by chantelle on 24/03/16.
//

#ifndef OBSTACLE_DETECTION_CAMERADATA_H
#define OBSTACLE_DETECTION_CAMERADATA_H

#include "CameraSpecifications.h"
#include "Image16bit.h"


enum CameraStatus {
    OK,
    SHUTTER_CLOSED,
    FAILED,
    OFF
};

struct CameraData {
    CameraStatus status;
    CameraSpecifications imageSpecs;
    Image16bit frame;

};

#endif //OBSTACLE_DETECTION_CAMERADATA_H