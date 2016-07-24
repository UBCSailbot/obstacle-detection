#ifndef OBSTACLE_DETECTION_LEPTONMULTIPLEXER_H
#define OBSTACLE_DETECTION_LEPTONMULTIPLEXER_H

#include "ICameraMultiplexer.h"
#include <comm/AStoppableWorker.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <features/SunImage.h>
#include <logger/Logger.h>

class LeptonMultiplexer : public ICameraMultiplexer, public AStoppableWorker {
public:
    std::vector<CameraData> getLatestCameraData();

    /*
     *  @param: useLepton0 - True if Lepton0 is to be used, false otherwise
     *  @param: useLepton1 - True if Lepton1 is to be used, false otherwise
     *  @param: _RESET_TIME_DELAY - If a Lepton is disconnected, how long (milliseconds) to
     *                        reset the Lepton for (how long it is turned off).
     */
    LeptonMultiplexer(bool useLepton0, bool useLepton1, const int _resetTimeDelay = 5000, const int sunPixelThreshold = 10000, const double sunDutyCycle = 0.50);

private:
    void checkLeptonStatus();

    bool imageHasSun(Image16bit image);

    bool _useLepton0;
    bool _useLepton1;
    volatile bool _lepton0Connected = true;
    volatile bool _lepton1Connected = true;
    const int _resetTimeDelay;
    static const int LEPTON_CHECK_WAIT_TIME_SECONDS = 5;

    int _frameCount = 0;
    bool _sunDetected = false;
    const int _sunPixelThreshold;
    const double _sunDutyCycle;
};


#endif //OBSTACLE_DETECTION_LEPTONMULTIPLEXER_H
