#ifndef OBSTACLE_DETECTION_DANGERZONESERIALIZER_H
#define OBSTACLE_DETECTION_DANGERZONESERIALIZER_H

#include <zmq.hpp>
#include <detect/DangerZone.h>

class DangerZoneSerializer {
public:

    static zmq::message_t serializeToZmq(const std::vector<DangerZone> &dangerZones);
};


#endif //OBSTACLE_DETECTION_DANGERZONESERIALIZER_H
