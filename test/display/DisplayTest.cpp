//
// Created by paul on 12/05/15.
//

#include <dirent.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "../../src/display/RoboPeakUSBDisplay.h"

using namespace std;
using namespace cv;

RoboPeakUSBDisplay d;

bool startsWith (string const &fullString, string const &start) {
    if (fullString.length() >= start.length()) {
        return (0 == fullString.compare (0, start.length(), start));
    } else {
        return false;
    }
}

bool endsWith (string const &fullString, string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

bool validFrameFile(string fileName) {
    return startsWith(fileName, "img_") && endsWith(fileName, ".png");
}

void loopOverDir(string frameDir) {
    // Iterate over each frame in frameDir,
    //   and paint a horizon line over it
    DIR *dp;
    struct dirent *ep;
    dp = opendir (frameDir.c_str());

    int frameCounter = 0;
    if (dp != NULL) {
        while (ep = readdir (dp)) {
            string fileName(ep->d_name);
            if (!validFrameFile(fileName))
                continue;
//            cout << "displaying " << fileName << endl;
            if (frameCounter % 3 == 0) {
                d.displayFrame(imread(frameDir + "/" + fileName, -1));
            }
            frameCounter ++;
            waitKey(37);
        }
        (void) closedir (dp);
    }
    else
        cerr << "Couldn't open directory " << frameDir << endl;
}

void printUsage(int argc, char** argv) {
    cout << "Usage: displayTest <video_dir>" << endl;
    cout << "You entered: " << endl;
    for (int i=0; i<argc; i++)
        cout << argv[i];
    cout << endl;
}

int main(int argc, char** argv) {
    // "/home/paul/sailbot/expt/fluctus/data/02012627freighterCrossingSun/modal100"

    if (argc != 2) {
        printUsage(argc, argv);
        return 1;
    }
    string videoDir(argv[1]);
    loopOverDir(videoDir);

    return 0;
}