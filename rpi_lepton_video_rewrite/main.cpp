
#include "Lepton.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>

using namespace std;


#define APP_NAME "Lepton Capture"
#define WIN_ZOOM_FACTOR 8
#define WIN_WIDTH 80 * WIN_ZOOM_FACTOR
#define WIN_HEIGHT 60 * WIN_ZOOM_FACTOR
#define EIGHT_BITS 256

int main() {
    Lepton lepton;
    cout << "Starting Capture" << endl;

    bool trackingEnabled = false;
    bool debugModeEnabled = false;
    cv::Mat frame;
    cv::Mat eightBit;


    while (1) {

        frame = lepton.GetFrame();

        // We must convert the frame to 8 bit display it properly

        double minVal_orig;
        double maxVal_orig;
        cv::minMaxLoc(frame, &minVal_orig, &maxVal_orig);
        cv::Mat displayed(WIN_HEIGHT, WIN_WIDTH, CV_8UC1);

        int range = maxVal_orig - minVal_orig;

        int minVal_trackbar = 128;
        int maxVal_trackbar = range + 128;

        // Convert input image to 8-bit and resize
        frame.convertTo(eightBit, CV_8UC1, 255.0/(maxVal_orig - minVal_orig), -minVal_orig * 255.0/(maxVal_orig - minVal_orig));
        cv::resize(eightBit, displayed, displayed.size(), 0, 0, cv::INTER_NEAREST);

        imshow(APP_NAME, displayed);

        // Check to see if a button has been pressed.
        // this 10ms delay is necessary for proper operation of this program
        // if removed, frames will not have enough time to refresh and a blank
        // image will appear.
        switch (cv::waitKey(30)) {
            case 113:
            case 27: //'esc' or 'q' key has been pressed, exit program.
                return 0;
            case 116: //'t' has been pressed. this will toggle tracking
                trackingEnabled = !trackingEnabled;
                cout << (!debugModeEnabled ? "Tracking disabled." : "Tracking enabled.") << endl;
                break;
            case 100: //'d' has been pressed. this will debug mode
                debugModeEnabled = !debugModeEnabled;
                cout << (!debugModeEnabled ? "Debug mode disabled." : "Debug mode enabled.") << endl;
                break;
            case 112: //'p' has been pressed. this will pause/resume the code.
                cout << "Code paused, press 'p' again to resume" << endl;
                while (true) {
                    if (cv::waitKey() == 112) {
                        cout << "Code Resumed" << endl;
                        break;
                    }
                }

            default:
                break;
        }
    }
}
