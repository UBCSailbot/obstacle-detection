//
// Created by Aditi Chakravarthi on 15-06-20.
//

#include "camera/lepton/LeptonI2CConnection.h"
#include <unistd.h>


int main() {

    LeptonI2CConnection i2cLepton;

    i2cLepton.openShutter();

    i2cLepton.closeShutter();

    sleep(5);

    i2cLepton.openShutter();

}




