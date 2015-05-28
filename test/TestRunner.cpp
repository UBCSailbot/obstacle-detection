//
// Created by paul on 09/05/15.
//

#include "imu/IMUTest.h"
#include "features/HorizonTest.h"
#include "imageProc/core/HorizonImageHistogramTest.h"

int main() {

//    testIMU();
    HorizonTest().runTests();
    HorizonImageHistogramTest().runTests();

    return 0;
}
