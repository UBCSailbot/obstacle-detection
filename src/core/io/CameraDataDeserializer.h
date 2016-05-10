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

private:
    static void checkNonEmptyMessage(zmq::message_t &message);

    static void checkNumberOfCameraDatas(size_t expected, size_t actual);

    static void checkForOverflow(char *currentPos, char *endPoint);
};


#endif //OBSTACLE_DETECTION_CAMERADATADESERIALIZER_H
