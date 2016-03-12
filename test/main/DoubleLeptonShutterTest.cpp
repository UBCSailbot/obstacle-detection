#include "camera/lepton/LeptonI2CConnection.h"
#include <unistd.h>


int main() {

    LeptonI2CConnection leftLepton(0);
    LeptonI2CConnection rightLepton(1);

    leftLepton.closeShutter();
    rightLepton.closeShutter();

    sleep(5);

    leftLepton.openShutter();
    rightLepton.openShutter();

}

