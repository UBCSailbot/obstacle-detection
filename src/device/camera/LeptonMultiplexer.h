#ifndef OBSTACLE_DETECTION_LEPTONMULTIPLEXER_H
#define OBSTACLE_DETECTION_LEPTONMULTIPLEXER_H

#include <config/Config.h>
#include "ICameraMultiplexer.h"
#include <comm/AStoppableWorker.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <features/SunImage.h>
#include <logger/Logger.h>

class LeptonMultiplexer : public ICameraMultiplexer, public AStoppableWorker {
public:
    static constexpr unsigned int DEFAULT_RESET_TIME_DELAY_MILLIS = 5000;
    static constexpr double DEFAULT_SUN_DUTY_CYCLE = 0.50;

    typedef od::Config::camera_enclosure_config::lepton_config LeptonConfig;
    typedef od::Config::perception_config::sun_detection_config SunConfig;

    LeptonMultiplexer(LeptonConfig leptonConfig, SunConfig sunConfig);

    std::vector<CameraData> getLatestCameraData();

private:
    // Configuration variables
    const bool useLepton0_;
    const bool useLepton1_;
    const unsigned int resetTimeDelayMillis_;
    const unsigned int statusCheckIntervalSeconds_;
    const unsigned int sunDutyCyclePercent_;
    const unsigned int sunPixelThreshold_;

    // State variables
    int frameCount_ = 0;
    volatile bool lepton0Connected_ = true;
    volatile bool lepton1Connected_ = true;
    bool sunDetected_ = false;

    void checkLeptonStatus();

    bool imageHasSun(Image16bit image);
};


#endif //OBSTACLE_DETECTION_LEPTONMULTIPLEXER_H
