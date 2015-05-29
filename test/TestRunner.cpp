//
// Created by paul on 09/05/15.
//

#include <gtest/gtest.h>
#include "imu/IMUTest.h"


int main(int argc, char **argv) {

    //    testIMU();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}