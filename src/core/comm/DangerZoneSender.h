#ifndef OBSTACLE_DETECTION_DANGERZONESENDER_H
#define OBSTACLE_DETECTION_DANGERZONESENDER_H

class DangerZoneSender {

public:

    DangerZoneSender(zmq::context_t &context, const int &port);

    void sendDangerZone(std::vector<DangerZone> &dangerZone);

private:
    zmq::socket_t _socket;

    static const std::string tcpBaseAddress;
};


#endif //OBSTACLE_DETECTION_DANGERZONESENDER_H
