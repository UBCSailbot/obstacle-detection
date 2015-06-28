//
// Created by Derek Lun on 5/23/2015.
//

#ifndef OBSTACLE_AVOIDANCE_SUNIMAGETESTER_H
#define OBSTACLE_AVOIDANCE_SUNIMAGETESTER_H

#include "geometry/Horizon.h"
#include "features/SunImage.h"

class SunImageTest {
public:
    void testSunImage();

private:
    void testFindSun() const;
};

#endif