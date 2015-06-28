//
// Created by Aditi Chakravarthi on 15-06-20.
//

#include "lepton/LeptonI2C.h"
#include <unistd.h>



int main() {


    lepton_connect();

    lepton_closeShutter();

    sleep(5);

    lepton_openShutter();

}




