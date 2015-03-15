
#include <opencv2/core/core.hpp>
#include "Lepton.h"
#include <iostream>
#include <string>

using namespace std;


int main() {
    Lepton lepton;
    cout << "Starting Capture" << endl;

    bool trackingEnabled = false;
    bool debugModeEnabled = false;
    cv::Mat frame;

    const string windowName = "Capture";

    while (1) {

        frame = lepton.GetFrame();

        // We must convert the frame to 8 bit display it properly
        cv::Mat eightBit(240, 180, CV_8UC1);
        frame.convertTo(eightBit, CV_8UC1);
        cv::resize(eightBit, eightBit, eightBit.size(), 3, 3, cv::INTER_NEAREST);

        imshow(windowName, eightBit);

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
