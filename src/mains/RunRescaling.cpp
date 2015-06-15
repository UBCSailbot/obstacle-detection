//
// Created by paul on 14/06/15.
//

#include <string>
#include <iostream>

#include "imageProc/rescale/Rescaling.h"

#include <tclap/CmdLine.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    if (argc < 3 || argc > 4) {
        cout    << "=======================================\n"
                << "Usage: rescale <input-dir> <output-dir>\n"
                << "=======================================\n"
                << "\n"
                << "Default:\n"
                << "\tPerforms simple rescaling of the form val' = (val - min ) / (max - min)\n"
                << "\n"
                << "Options:\n"
                << "\t-h <imu-logfile> <type>\n"
                << "\t\tRescales to a value based on the position of the horizon. "
                << "<type> argument may be any of:\n"
                << "\t\t1: horizon median rescaling\n"
                << "\t\t2: horizon modal rescaling\n"
                << "\n"
                << "Please consult the source code for more details on the "
                << "functionality of each of these rescaling algorithms."
                ;

        return 1;
    }

    string imuLogfile(argv[1]);
    string frameDir(argv[2]);

//    videoTest(imuLogfile, frameDir);

}