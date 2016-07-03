#include <zmq.hpp>
#include <io/DangerZoneSerializer.h>
#include "DangerZoneSender.h"

const std::string DangerZoneSender::routemakingIpcAddress = "ipc:////tmp/sailbot-obstacle-detection";

DangerZoneSender::DangerZoneSender(zmq::context_t &context) :
        _socket(zmq::socket_t(context, ZMQ_PUB)) {

    _socket.bind(routemakingIpcAddress);
}


void DangerZoneSender::sendDangerZone(std::vector<DangerZone> &dangerZone) {

    _socket.send(DangerZoneSerializer::serializeToZmq(dangerZone));
}



