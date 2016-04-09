#ifndef OBSTACLE_DETECTION_CAMERADATADESERIALIZER_H
#define OBSTACLE_DETECTION_CAMERADATADESERIALIZER_H

#include "types/CameraData.h"
#include <stdlib.h>
#include <vector>
#include <zmq.hpp>
#include <string.h>
#include <types/Image16bit.h>

class CameraDataDeserializer {
public:
    static std::vector<CameraData> deserializeFromZmq(zmq::message_t &message);
};


#endif //OBSTACLE_DETECTION_CAMERADATADESERIALIZER_H
