#ifndef OBSTACLE_DETECTION_MOCKBOATSTREAM_H
#define OBSTACLE_DETECTION_MOCKBOATSTREAM_H


#include "BoatDataStream.h"

class MockBoatDataStream : public BoatDataStream {

public:
    static constexpr double DEFAULT_MOCK_HEADING = 90.0;

    MockBoatDataStream();

    MockBoatDataStream(double heading);

    virtual CurrentData getBoatData() override;

    double heading_;

};


#endif //OBSTACLE_DETECTION_MOCKBOATSTREAM_H
