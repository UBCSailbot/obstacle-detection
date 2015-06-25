//
// Created by Aditi Chakravarthi on 15-06-20.
//

#include "lepton/leptonI2C.h"
#include <unistd.h>



int main() {

    lepton_closeShutter();

    sleep(5);

    lepton_openShutter();

}




