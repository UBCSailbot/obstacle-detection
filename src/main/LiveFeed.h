
//
// Created by paul on 2015/05/12
//

#ifndef OBSTACLE_AVOIDANCE_LIVEFEED_H
#define OBSTACLE_AVOIDANCE_LIVEFEED_H

#include "imu/IMU.h"
#include "imu/ParallelIMU.h"
#include "lepton/Lepton.h"
#include "features/SunImage.h"

#include "types/Image8bit.h"
#include "types/Image16bit.h"
#include "geometry/Horizon.h"
#include "imageProc/rescale/SimpleRescaler.h"
#include "imageProc/liveFeed/base64EncDec.h"
#include "io/JSONSerializer.h"

#include "exceptions/LeptonSPIOpenException.h"
#include "comm/ZmqContextSingleton.h"
#include "comm/ImageFeedZmq.h"

#include <vector>
#include <unistd.h>
#include <signal.h>
#include <fstream>
#include <display/DisplayUtils.h>

#include <dlib/svm_threaded.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <dlib/data_io.h>
#include <dlib/opencv.h>


static void hangup_handler(int signum);
void setup_sighandler();

void record(char* output_dir, bool verbose=true );
void displayFrameWithHorizonLine(Image8bit image, double roll, double pitch, Display &d);

void printUsage(int argc, char** argv);

#endif //OBSTACLE_AVOIDANCE_LIVEFEED_H
