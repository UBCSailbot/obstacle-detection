#ifndef OBSTACLE_DETECTION_CAMERADATASERIALIZER_H
#define OBSTACLE_DETECTION_CAMERADATASERIALIZER_H

#include "types/CameraData.h"
#include <stdlib.h>
#include <vector>
#include <zmq.hpp>
#include <string.h>
#include <types/Image16bit.h>

class CameraDataSerializer {
public:
    static zmq::message_t serializeToZmq (std::vector<CameraData> dataVector);

};


#endif //OBSTACLE_DETECTION_CAMERADATASERIALIZER_H
