//
// Created by denis on 07/06/16.
//

#ifndef OBSTACLE_DETECTION_CAMERADATAHANDLER_H
#define OBSTACLE_DETECTION_CAMERADATAHANDLER_H

#include <imageProc/dlib/DLibProcessor.h>
#include "CameraDataStream.h"
#include <memory>
#include <vector>

/*
 * This class is composed of handles to various events in image processing
 */
class CameraDataHandler {

public:
     CameraDataHandler() {};

    virtual void onMultiImageProcessed(std::vector<CameraData> cameraData,
                                       std::vector<dlib::rectangle> detectedRectangles) = 0;


    virtual void onSingleImageProcessed(CameraData cameraData, std::vector<dlib::rectangle> detectedRectangles) = 0;


};


#endif //OBSTACLE_DETECTION_CAMERADATAHANDLER_H
