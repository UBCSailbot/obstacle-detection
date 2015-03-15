
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

int main() {
    Lepton lepton;
    cout << "Starting Capture" << endl;

    bool trackingEnabled = false;
    bool debugModeEnabled = false;
    cv::Mat frame(60, 80, CV_16UC1);
    cv::Mat eightBit(60, 80, CV_8UC1);
    cv::Mat displayed(WIN_HEIGHT, WIN_WIDTH, CV_8UC1);
    cv::Mat output(60, 80, CV_8UC1);

    while (1) {

        lepton.GetFrame(frame, eightBit);

        cv::Mat displayed(WIN_HEIGHT, WIN_WIDTH, CV_8UC1);
//        cv::resize(eightBit, displayed, displayed.size(), 0, 0, cv::INTER_NEAREST);

        if (trackingEnabled) {
            cv::GaussianBlur(eightBit, output, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
            cv::Laplacian(output, output, CV_16S, 3, 1, 0, cv::BORDER_DEFAULT);
            cv::convertScaleAbs(output, output);

            imshow("Filtered", output);
        }

//        imshow(APP_NAME, displayed);
        imshow(APP_NAME, eightBit);

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
