#ifndef OBSTACLE_DETECTION_CAMERADATAHANDLER_H
#define OBSTACLE_DETECTION_CAMERADATAHANDLER_H

#include <imageProc/dlib/DLibProcessor.h>
#include "CameraDataStream.h"
#include <detect/DangerZone.h>
#include <memory>
#include <vector>

/*
 * This class is composed of handles to various events in image processing
 */
class CameraDataHandler {

public:

    virtual void onImageProcessed(std::vector<CameraData> cameraData,
                                  std::vector<cv::Rect> detectedRectangles) = 0;

    virtual void onDangerZoneProcessed(std::vector<DangerZone> cameraData) = 0;


};


#endif //OBSTACLE_DETECTION_CAMERADATAHANDLER_H
