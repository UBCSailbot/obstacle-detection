//
// Created by paul on 25/01/16.
//

#ifndef OBSTACLE_DETECTION_HORIZONIMAGETEST_H
#define OBSTACLE_DETECTION_HORIZONIMAGETEST_H


#include <gtest/gtest.h>

#include <geometry/HorizonFactory.h>
#include <geometry/Vector2d.h>
#include <features/HorizonImage.h>

class HorizonImageTest : public ::testing::Test {

public:
    HorizonFactory _factory = HorizonFactory(LeptonCameraSpecifications);


};


#endif //OBSTACLE_DETECTION_HORIZONIMAGETEST_H
