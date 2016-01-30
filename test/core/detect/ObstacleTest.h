//
// Created by paul on 15/01/16.
//

#ifndef OBSTACLE_DETECTION_OBSTACLETEST_H
#define OBSTACLE_DETECTION_OBSTACLETEST_H

#include <gtest/gtest.h>
#include <geometry/Horizon.h>
#include <geometry/HorizonFactory.h>
#include <camera/lepton/LeptonCameraSpecifications.h>

class ObstacleTest : public ::testing::Test {
public:
    HorizonFactory _factory = HorizonFactory(LeptonCameraSpecifications);

};


#endif //OBSTACLE_DETECTION_OBSTACLETEST_H
