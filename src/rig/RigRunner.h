//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_RIGRUNNER_H
#define OBSTACLE_AVOIDANCE_RIGRUNNER_H

#include "../imu/IMU.h"
#include "../imu/ParallelIMU.h"
#include "../lepton/Lepton.h"
#include "../geometry/Horizon.h"
#include "../display/Display.h"
#include "../display/RoboPeakUSBDisplay.h"

#include <signal.h>
#include <fstream>

using namespace std;
using namespace cv;

static void hangup_handler(int signum);
void setup_sighandler();

void record(char* output_dir, bool verbose=true );
void displayFrameWithHorizonLine(Image8bit image, double roll, double pitch, Display &d);

void printUsage(int argc, char** argv);

#endif //OBSTACLE_AVOIDANCE_RIGRUNNER_H
