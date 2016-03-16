#ifndef OBSTACLE_AVOIDANCE_SUNIMAGETESTER_H
#define OBSTACLE_AVOIDANCE_SUNIMAGETESTER_H

#include <gtest/gtest.h>

#include <iostream>

#include "paths/Resources.h"
#include "geometry/Horizon.h"
#include "features/SunImage.h"
#include "camera/lepton/LeptonCameraSpecifications.h"

class SunImageTest {
public:
    void testSunImage();

private:
    void testFindSun() const;
};

#endif
