//
// Created by paul on 12/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_RIGRUNNER_H
#define OBSTACLE_AVOIDANCE_RIGRUNNER_H

#include "imu/IMU.h"
#include "imu/ParallelIMU.h"
#include "lepton/Lepton.h"
#include "features/SunImage.h"
#include "display/Display.h"
#include "display/RoboPeakUSBDisplay.h"
#include "types/Image8bit.h"
#include "types/Image16bit.h"
#include "geometry/Horizon.h"
#include "imageProc/rescale/SimpleRescaler.h"

#include "imageProc/liveFeed/base64EncDec.h"

#include <unistd.h>
#include <signal.h>
#include <fstream>
#include <display/DisplayUtils.h>



using namespace std;
using namespace cv;

static void hangup_handler(int signum);
void setup_sighandler();

void record(char* output_dir, bool verbose=true );
void displayFrameWithHorizonLine(Image8bit image, double roll, double pitch, Display &d);

void printUsage(int argc, char** argv);

#endif //OBSTACLE_AVOIDANCE_RIGRUNNER_H
