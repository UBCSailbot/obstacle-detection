#include <zmq.hpp>
#include <io/DangerZoneSerializer.h>
#include "DangerZoneSender.h"

DangerZoneSender::DangerZoneSender(zmq::context_t &context, const std::string &dangerZonePubAddress) :
        _socket(zmq::socket_t(context, ZMQ_PUB)) {

    _socket.bind(dangerZonePubAddress);
}


void DangerZoneSender::sendDangerZone(const std::vector<DangerZone> &dangerZone) {

    _socket.send(DangerZoneSerializer::serializeToZmq(dangerZone));
}



