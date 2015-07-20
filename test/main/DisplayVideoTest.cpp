//
// Created by paul on 12/05/15.
//

#include <dirent.h>
#include <iostream>

#include <opencv2/highgui/highgui.hpp>

#include <display/DisplayUtils.h>
#include <lepton/Lepton.h>

using namespace std;
using namespace cv;

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

    RoboPeakUSBDisplay d;

    // timing
    bool previousReadSuccessful = true;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    float leptonPeriodSeconds = (float) 3 / LEPTON_FPS;

    cout << "Successfully instantiated RoboPeakUSBDisplay" << endl;
    cout << "Lepton period is " << leptonPeriodSeconds << " s" << endl;

    int frameCounter = 0;
    if (dp != NULL) {
        while (ep = readdir (dp)) {

            if (previousReadSuccessful) {
                start = std::chrono::system_clock::now();
            }

            previousReadSuccessful = false;

            if (frameCounter % 3 == 0   ) {
                string fileName(ep->d_name);

                if (!validFrameFile(fileName)) {
                    continue;
                }

                Mat frame = imread(frameDir + "/" + fileName, -1);

                Image8bit displayed(frame, false);
                cv::cvtColor(frame, displayed, cv::COLOR_GRAY2BGR);
                line(displayed, Point(0,30), Point(80, 40), Scalar(255,0,0), 1);

                d.displayColored(displayed);

                previousReadSuccessful = true;

                end = std::chrono::system_clock::now();
                std::chrono::duration<float> elapsed_seconds = end-start;

                if (elapsed_seconds.count() < leptonPeriodSeconds) {
                    float sleepTimeMicros = (leptonPeriodSeconds - elapsed_seconds.count()) * 1000000;
                    usleep((__useconds_t) sleepTimeMicros);
                }
            }

            frameCounter ++;

        }
        closedir(dp);
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

    if (argc != 2) {
        printUsage(argc, argv);
        return 1;
    }
    string videoDir(argv[1]);
    cout << "videoDir: " << videoDir << endl;
    loopOverDir(videoDir);

    return 0;
}