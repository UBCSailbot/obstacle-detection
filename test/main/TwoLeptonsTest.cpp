//
// Created by paul on 09/05/15 (dd/mm/yy, of course)
//

#include <imageProc/rescale/SimpleRescaler.h>
#include "display/Display.h"
#include <display/DisplayUtils.h>
#include <camera/lepton/RedundantLepton.h>
#include "types/Image8bit.h"
#include "types/Image16bit.h"
#include "imageProc/rescale/SimpleRescaler.h"

#define APP_NAME "TwoLeptons"

using namespace std;

void run_single(int lepton_cs) {

    RedundantLepton lepton0(lepton_cs);
    SimpleRescaler rescaler;

    Image16bit frame0(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX);
    Image8bit displayed0(60, 80);
    int frame_counter = 1;

    cout << "Connecting to screen" << endl;

    Display* display0 = new DesktopDisplay("Lepton0"); 

    cout << "Starting Capture" << endl;

    while (1) {

        // read only every 3rd frame
        if ((frame_counter % 3) == 0) {
            lepton0.getFrame(frame0);
            cout << "lepton " << lepton_cs << " got frame " << frame_counter << endl; 

            // convert to 8 bit and display
            rescaler.scale16bitTo8bit(frame0, displayed0);

            display0->display8bitGray(displayed0);

//            cout << "now displaying. can you see it?" << endl;
        }

        frame_counter ++;

    }

}

void run_double() {

    RedundantLepton lepton0(0);
    RedundantLepton lepton1(1);
    SimpleRescaler rescaler;

    Image16bit frame0(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX);
    Image16bit frame1(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX);
    Image8bit displayed0(60, 80);
    Image8bit displayed1(60, 80);
    int frame_counter = 1;

    cout << "Connecting to screen" << endl;

    Display* display0 = new DesktopDisplay("Lepton0"); 
    Display* display1 = new DesktopDisplay("Lepton1"); 

    cout << "Starting Capture" << endl;

    while (1) {

        // read only every 3rd frame
        //if ((frame_counter % 3) == 0) {
            lepton0.getFrame(frame0);
            //cout << "lepton0 got frame " << frame_counter << endl; 

            lepton1.getFrame(frame1);
            //cout << "lepton1 got frame " << frame_counter << endl; 

            // convert to 8 bit and display
            rescaler.scale16bitTo8bit(frame0, displayed0);
            rescaler.scale16bitTo8bit(frame1, displayed1);

            display0->display8bitGray(displayed0);
            display1->display8bitGray(displayed1);

//            cout << "now displaying. can you see it?" << endl;
        //}

        frame_counter ++;

    }

}

int main(int argc, char** argv) {
    if(argc < 2) {
        run_double();
    } 
    int lepton_cs = atoi(argv[1]);
    run_single(lepton_cs);

    return 0;
}
