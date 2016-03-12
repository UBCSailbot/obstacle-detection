#ifndef OBSTACLE_DETECTION_LEPTONMULTIPLEXER_H
#define OBSTACLE_DETECTION_LEPTONMULTIPLEXER_H

#include "ICameraMultiplexer.h"
#include <comm/AStoppableWorker.h>
#include <iostream>
#include <thread>
#include <unistd.h>

class LeptonMultiplexer : public ICameraMultiplexer, public AStoppableWorker {
public:
    std::vector<CameraData> getLatestCameraData();

    LeptonMultiplexer(bool useLepton0, bool useLepton1, const int _RESET_TIME_DELAY = 5000);

private:
    void checkLeptonStatus();
    bool _useLepton0;
    bool _useLepton1;
    volatile bool _lepton0Connected = true;
    volatile bool _lepton1Connected = true;
    const int _RESET_TIME_DELAY;
    static const int LEPTON_CHECK_WAIT_TIME_SECONDS = 5;
};


#endif //OBSTACLE_DETECTION_LEPTONMULTIPLEXER_H
