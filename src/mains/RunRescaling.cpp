//
// Created by paul on 14/06/15.
//

#include <string>
#include <iostream>

#include "imageProc/rescale/Rescaling.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    if (argc < 3 || argc > 4) {
        cout    << "===============================================\n"
                << "Usage: rescale <type=1> <imuLogfile> <frameDir>\n"
                << "===============================================\n"
                << "\n"
                << "\"type\" argument may be any of:\n"
                << "\t1: horizon median rescaling\n"
                << "\t2: horizon modal rescaling\n"
                << "\t3: simple rescaling\n"
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