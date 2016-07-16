#include "camera/lepton/LeptonI2CConnection.h"
#include <unistd.h>
#include <iostream>


void runSingleLepton(int waitTime, int i2cPin) {

    std::cout << "Wait time: " << waitTime << " i2cPin: " << i2cPin << std::endl;

    LeptonI2CConnection i2cLepton(i2cPin);

    i2cLepton.closeShutter();
    sleep(waitTime);
    i2cLepton.openShutter();
}

void runBothLeptons(int waitTime) {

    std::cout << "Wait time: " << waitTime << " Using both leptons\n";
	
    LeptonI2CConnection i2cLepton0(0);
    LeptonI2CConnection i2cLepton1(1);

    i2cLepton0.closeShutter();
    i2cLepton1.closeShutter();
    sleep(waitTime);
    i2cLepton0.openShutter();
    i2cLepton1.openShutter();
}

int main(int argc, char *argv[]) {
   if(argc != 3) {
	std::cout << "Usage is './leptonShutterTest <waitTime> <i2cPin>' or './leptonShutterTest <waitTime> -d' to run both leptons\n";
	return 0; 
   }

    int waitTime = atoi(argv[1]);

    if(argv[2][0] == '-' && argv[2][1] == 'd') {
	runBothLeptons(waitTime);
    } else {
        int i2cPin = atoi(argv[2]);
	runSingleLepton(waitTime, i2cPin);
    }

}

