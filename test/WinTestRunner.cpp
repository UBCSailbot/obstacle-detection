//
// Created by Derek Lun on 5/23/2015.
//

#include "features/HorizonTest.h"
#include "sunImage/SunImageTest.h"

int main() {

//    testIMU();
    HorizonTest().runTests();
    testSunImage();

    return 0;
}
