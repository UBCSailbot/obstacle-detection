#ifndef OBSTACLE_DETECTION_DANGERZONESENDER_H
#define OBSTACLE_DETECTION_DANGERZONESENDER_H

class DangerZoneSender {

public:

    DangerZoneSender(zmq::context_t &context, const std::string &dangerZonePubAddress);

    void sendDangerZone(const std::vector<DangerZone> &dangerZone);

private:
    zmq::socket_t _socket;
};


#endif //OBSTACLE_DETECTION_DANGERZONESENDER_H
