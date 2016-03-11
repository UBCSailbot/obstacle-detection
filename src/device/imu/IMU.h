//
// Created by paul on 09/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_IMU_H
#define OBSTACLE_AVOIDANCE_IMU_H

#include <sstream>
#include <string>
#include <geometry/Orientation.h>

class IMU {

  public:
    virtual Orientation getOrientation() = 0;

};


#endif //OBSTACLE_AVOIDANCE_IMU_H
