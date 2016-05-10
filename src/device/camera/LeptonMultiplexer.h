#ifndef OBSTACLE_DETECTION_LEPTONMULTIPLEXER_H
#define OBSTACLE_DETECTION_LEPTONMULTIPLEXER_H

#include "ICameraMultiplexer.h"

class LeptonMultiplexer : public ICameraMultiplexer {
public:
    std::vector<CameraData> getLatestCameraData();

    LeptonMultiplexer(bool useLepton0, bool useLepton1);
private:
    bool _useLepton0;
    bool _useLepton1;
};


#endif //OBSTACLE_DETECTION_LEPTONMULTIPLEXER_H
