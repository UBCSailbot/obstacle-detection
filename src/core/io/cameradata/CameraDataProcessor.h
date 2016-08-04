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
#include <detect/SimpleDangerZoneEncoder.h>
#include <io/BoatDataStream.h>

/*
 * This class encapsulates the common functionality for receiving streams CameraData objects.
 * This handles all of the logic of processing images and the calls that recieved function when that is complete
 */
class CameraDataProcessor {
public:
    CameraDataProcessor(CameraDataStream &_stream, DLibProcessor &dLibProcessor,
                        CameraDataHandler &cameraDataHandler, IMU &imu,
                        BoatDataStream &boatDataStream);

    volatile bool getKeepRecording() const;

    void setKeepRecording(volatile bool keepRecording);

    void run();

    static void filterRectanglesByHorizon(std::vector<cv::Rect> *rectangles, const Horizon &horizon);

private:
    std::vector<DangerZone> getDangerZones(const std::vector<cv::Rect> &detectedRectangles,
                   const std::vector<std::shared_ptr<cv::Mat>> &frames,
                   const CurrentData &latestData,
                   const std::chrono::duration<uint64_t, std::ratio<1, 1>> &imageReceiveTime,
                   const Horizon &horizon,
                   const CameraSpecifications &specs);

    DLibProcessor &_dlibProcessor;

    CameraDataHandler &_cameraDataHandler;

    CameraDataStream &_stream;

    volatile bool _keepRecording;

    SimpleDangerZoneEncoder _simpleDangerZoneEncoder;

    IMU &_imu;

    BoatDataStream &_boatDataStream;

    Obstacle rectToObstacle(cv::Rect rect, Horizon horizon);
};

#endif //OBSTACLE_DETECTION_CAMERADATAPROCESESSOR_H
