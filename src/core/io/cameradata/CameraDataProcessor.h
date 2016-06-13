//
// Created by denis on 09/06/16.
//

#ifndef OBSTACLE_DETECTION_CAMERADATAPROCESESSOR_H
#define OBSTACLE_DETECTION_CAMERADATAPROCESESSOR_H

#include <imageProc/dlib/DLibProcessor.h>
#include "CameraDataStream.h"
#include "CameraDataHandler.h"
#include <memory>
#include <vector>
#include <imu/ParallelIMU.h>


/*
 * This class encapsulates the common functionality for receiving streams CameraData objects.
 * This handles all of the logic of processing images and the calls that recieved function when that is complete
 */
    class CameraDataProcessor {
    public:
        CameraDataProcessor(CameraDataStream *stream, ParallelIMU *imu,
                                      DLibProcessor *dLibProcessor, CameraDataHandler* cameraDataHandler);

        volatile bool getKeepRecording() const;

        void setKeepRecording(volatile bool keepRecording);

        void run();

    private:

        DLibProcessor*_dlibProcessor;

        CameraDataHandler*_cameraDataHandler;

        CameraDataStream *_stream;

        volatile bool _keepRecording;

    };

#endif //OBSTACLE_DETECTION_CAMERADATAPROCESESSOR_H
