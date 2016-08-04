#ifndef OBSTACLE_DETECTION_CAMERADATAHANDLER_H
#define OBSTACLE_DETECTION_CAMERADATAHANDLER_H

#include <geometry/Orientation.h>
#include "CameraDataStream.h"
#include <detect/DangerZone.h>
#include <vector>
#include <geometry/Horizon.h>

/*
 * This class is composed of handles to various events in image processing
 */
class CameraDataHandler {

public:

    virtual void onImageProcessed(const std::vector<CameraData> &cameraData, const std::vector<cv::Rect> &detectedRectangles,
                                  const Horizon &horizon) = 0;

    virtual void onDangerZoneProcessed(const std::vector<DangerZone> &dangerZones) = 0;

    virtual void onOrientationReceived(const Orientation &orientation) = 0;

};


#endif //OBSTACLE_DETECTION_CAMERADATAHANDLER_H
