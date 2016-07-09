#ifndef OBSTACLE_DETECTION_BOATDATASTREAM_H
#define OBSTACLE_DETECTION_BOATDATASTREAM_H

#include <types/CurrentData.h>

class BoatDataStream {

public:
    /*
     * Returns the latest boat data
     */
    virtual CurrentData getBoatData() = 0;


};

#endif //OBSTACLE_DETECTION_BOATDATASTREAM_H
