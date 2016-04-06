//
// Created by chantelle on 24/03/16.
//

#ifndef OBSTACLE_DETECTION_CAMERADATA_H
#define OBSTACLE_DETECTION_CAMERADATA_H

#include <camera/ICameraSpecifications.h>

/*replace bool cameraStatus with enum cameraStatus,
 * refer to notes & stackoverflow/cplusplus.com*/

enum CameraStatus {
    OK,
    SHUTTER_CLOSED,
    FAILED,
    OFF
};

struct CameraData {
    CameraStatus status;
    ICameraSpecifications imageSpecs;
    Image16bit frame;

};

#endif //OBSTACLE_DETECTION_CAMERADATA_H