//
// Created by Derek Lun on 5/23/2015.
//

#ifndef OBSTACLE_AVOIDANCE_SUNIMAGETESTER_H
#define OBSTACLE_AVOIDANCE_SUNIMAGETESTER_H
#include "features/Horizon.h"
#include "TestClass.h"

class SunImageTest : public TestClass {

public:
    void runTests();

    void testFindSun();
};

#endif