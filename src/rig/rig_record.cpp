//
// Created by paul on 09/05/15.
//

#include "rig_record.h"
#include "../imu/IMU.h"


#include <iostream>

#include <opencv2/core/core.hpp>



int main()
{
    IMU imu;

    int sampleCount = 0;
    int sampleRate = 0;
    uint64_t rateTimer;
    uint64_t displayTimer;
    uint64_t now;

    //  set up for rate timer
    rateTimer = displayTimer = RTMath::currentUSecsSinceEpoch();

    while (1) {

        sampleCount++;

        now = RTMath::currentUSecsSinceEpoch();

        //  display 10 times per second
        if ((now - displayTimer) > 100000) {
            printf("Sample rate %d: %s\r", sampleRate, imu.toString().c_str());
            fflush(stdout);
            displayTimer = now;
        }

        //  update rate every second
        if ((now - rateTimer) > 1000000) {
            sampleRate = sampleCount;
            sampleCount = 0;
            rateTimer = now;
        }
    }
}
