//
// Created by paul on 09/05/15.
//

#include "imu/IMUTest.h"
#include "features/HorizonTest.h"
#include "features/SunImageTest.h"

int main() {

//    testIMU();
    HorizonTest().testHorizon();
    SunImageTest().testSunImage();

    return 0;
}
