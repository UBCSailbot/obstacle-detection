#ifndef OBSTACLE_DETECTION_DANGERZONESENDER_H
#define OBSTACLE_DETECTION_DANGERZONESENDER_H

class DangerZoneSender {

public:

    DangerZoneSender(zmq::context_t &context);

    void sendDangerZone(const std::vector<DangerZone> &dangerZone);

private:
    zmq::socket_t _socket;

    static const std::string routemakingIpcAddress;
};


#endif //OBSTACLE_DETECTION_DANGERZONESENDER_H
