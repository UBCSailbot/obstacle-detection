//
// Created by denis on 09/07/16.
//

#ifndef OBSTACLE_DETECTION_MOCKBOATSTREAM_H
#define OBSTACLE_DETECTION_MOCKBOATSTREAM_H


#include "BoatDataStream.h"

class MockBoatDataStream : public BoatDataStream {

public:
    virtual CurrentData getBoatData() override;

    MockBoatDataStream(double bearing);

    double _bearing;

};


#endif //OBSTACLE_DETECTION_MOCKBOATSTREAM_H
