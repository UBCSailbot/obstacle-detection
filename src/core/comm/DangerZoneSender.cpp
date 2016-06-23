#include <zmq.hpp>
#include <detect/DangerZone.h>
#include <io/DangerZoneSerializer.h>
#include "DangerZoneSender.h"

const std::string DangerZoneSender::tcpBaseAddress = "tcp://127.0.0.1:";

DangerZoneSender::DangerZoneSender(zmq::context_t &context, const int &port) :
        _socket(zmq::socket_t(context, ZMQ_PUB)) {
    std::string port_str = std::to_string(port);

    std::string zmq_base = tcpBaseAddress;
    _socket.bind(zmq_base + port_str);
}


void DangerZoneSender::sendDangerZone(std::vector<DangerZone> &dangerZone) {

    _socket.send(DangerZoneSerializer::serializeToZmq(dangerZone));
}



