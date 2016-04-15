#ifndef OBSTACLE_DETECTION_MOCKCAMERAMULTIPLEXER_H
#define OBSTACLE_DETECTION_MOCKCAMERAMULTIPLEXER_H

#include <chrono>
#include <thread>

#include <types/CameraData.h>
#include <camera/lepton/LeptonCameraSpecifications.h>
#include <io/CameraDataSerializer.h>
#include <io/CameraDataDeserializer.h>
#include <camera/ICameraMultiplexer.h>
#include <opencv2/highgui/highgui_c.h>
#include <paths/Resources.h>
#include <opencv2/highgui/highgui.hpp>

class MockCameraMultiplexer : public ICameraMultiplexer{
public:
    MockCameraMultiplexer();
    std::vector<CameraData> getLatestCameraData() override;

private:
    int runNumber;
    cv::Mat _fishingBoatImg;
    cv::Mat _freighterSunImg;
    cv::Mat _garbledImg;
};


#endif //OBSTACLE_DETECTION_MOCKCAMERAMULTIPLEXER_H
