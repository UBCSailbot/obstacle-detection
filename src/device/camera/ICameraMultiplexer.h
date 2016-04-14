#ifndef OBSTACLE_DETECTION_ICAMERAMUX_H
#define OBSTACLE_DETECTION_ICAMERAMUX_H


#include <types/CameraData.h>

class ICameraMultiplexer {
public:
    virtual std::vector<CameraData> getLatestCameraData() = 0;
};


#endif //OBSTACLE_DETECTION_ICAMERAMUX_H
