//
// Created by paul on 09/05/15 (dd/mm/yy, of course)
//

#include <imageProc/rescale/SimpleRescaler.h>
#include "display/Display.h"
#include <display/DisplayUtils.h>
#include <lepton/RedundantLepton.h>
#include "types/Image8bit.h"
#include "types/Image16bit.h"
#include "imageProc/rescale/SimpleRescaler.h"

#define APP_NAME "TwoLeptons"

using namespace std;



void run() {

    RedundantLepton lepton0(0);
    //Lepton lepton1(1);
    SimpleRescaler rescaler;

    Image16bit frame(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX);
    Image8bit displayed(60, 80);
    int frame_counter = 1;

    // timing
    std::chrono::time_point<std::chrono::system_clock> start, end;
    float leptonPeriodSeconds = 1 / LEPTON_FPS;

    cout << "Connecting to screen" << endl;

    Display* display = DisplayUtils::connectToDisplay();

    cout << "Starting Capture" << endl;

    while (1) {

        start = std::chrono::system_clock::now();

        // read only every 3rd frame
        if ((frame_counter % 3) == 0) {
            lepton0.getFrame(frame);

            // convert to 8 bit and display
            rescaler.scale16bitTo8bit(frame, displayed);
            display->display8bitGray(displayed);
        }

        frame_counter ++;

        end = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsed_seconds = end-start;

        if (elapsed_seconds.count() < leptonPeriodSeconds) {
            unsigned int sleepTimeMicros = (unsigned int) (leptonPeriodSeconds - elapsed_seconds.count()) * 1000000;
            usleep(sleepTimeMicros);
        }

    }

}

int main(int argc, char** argv) {

    run();

    return 0;
}
