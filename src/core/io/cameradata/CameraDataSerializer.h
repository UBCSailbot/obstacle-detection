#ifndef OBSTACLE_DETECTION_CAMERADATASERIALIZER_H
#define OBSTACLE_DETECTION_CAMERADATASERIALIZER_H

#include "types/CameraData.h"
#include <stdlib.h>
#include <vector>
#include <zmq.hpp>
#include <string.h>
#include <types/Image16bit.h>
#include "types/message_types.h"

class CameraDataSerializer {
public:
    static zmq::message_t serializeToZmq (std::vector<CameraData> dataVector);

private:
    static size_t calculateMessageSize(const std::vector<CameraData> &dataVector, uint8_t numCameraData);
};


#endif //OBSTACLE_DETECTION_CAMERADATASERIALIZER_H
