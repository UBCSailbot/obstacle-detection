//
// Created by paul on 09/05/15.
//

#include "RigRunner.h"
#include "../imageProc/SimpleRescaler.h"

#define APP_NAME "rig_record"

bool stop_record = false;

static void hangup_handler(int signum) {
    if (signum == SIGHUP)
        stop_record = true;
}

void setup_sighandler() {
    struct sigaction sa;

    sa.sa_handler = hangup_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; /* Restart functions if interrupted by handler */
    if (sigaction(SIGHUP, &sa, NULL) == -1)
        cerr << "Failed to initialize signal handler for " << APP_NAME << endl;
}

void record(char* output_dir, bool verbose) {

    Lepton lepton;
    ParallelIMU imu;
    SimpleRescaler rescaler;

    Image8bit displayed(60, 80);
    Image16bit frame(60, 80);
    int frame_counter = 1;
    char img_name[128];
    char imu_file_name[128];

    std::ofstream imuLog;

    sprintf(imu_file_name, "%s/imuLog.txt", output_dir);
    imuLog.open (imu_file_name);

    cout << "Connecting to screen" << endl;

    RoboPeakUSBDisplay display;

    cout << "Starting Capture" << endl;

    while (!stop_record) {

        // Perform FFC every FFC_FREQ_SEC seconds
/*        if ( (frame_counter / LEPTON_FPS) % FFC_FREQ_SEC == FFC_FREQ_SEC - 1) {
            cout << "Performing FFC" << endl;
            lepton.performFFC();
            usleep(600 * 1000);
        }
*/
        lepton.captureFrame(frame);

        // save the current frame as a .png file
        sprintf(img_name, "%s/raw/img_%06d.png", output_dir, frame_counter);
        imwrite(img_name, frame);

        if (frame_counter % LEPTON_FPS == 0) {
            // convert to 8 bit and display
            rescaler.scale16bitTo8bit(frame, displayed);
            displayFrameWithHorizonLine(displayed, imu.getRollRad(), imu.getPitchRad(), display);
            //d.displayFrame(displayed);
        }

        imuLog << imu.toDataString();
//        if (verbose)
 //           cout << imu.toPrettyString();

        frame_counter ++;
    }

    imuLog.close();
    cout << "Recording received stopping signal " <<
    "and terminated gracefully." << endl;

}

void displayFrameWithHorizonLine(Image8bit frame, double roll, double pitch, Display &d) {
    Horizon h(roll, pitch);
    cv::Mat displayed(frame.rows, frame.cols, CV_16U);
    cv::cvtColor(frame, displayed, cv::COLOR_GRAY2BGR);
    line(displayed, h.getStart(), h.getEnd(), Scalar(255,0,0), 1);
    d.displayColorFrame(displayed);
}

void printUsage(int argc, char** argv) {
    cout << "Usage: rig_record <output_dir>" << endl;
    cout << "You entered: " << endl;
    for (int i=0; i<argc; i++)
        cout << argv[i];
    cout << endl;
}

int main(int argc, char** argv) {

    if(argc < 2) {
        printUsage(argc, argv);
        return 1;
    }

    char* output_dir = argv[1];
    setup_sighandler();

    if (argc == 2) {
        record(output_dir);
    }

    else if (argc == 3) {
        char* arg2 = argv[2];
        if (!strcmp(arg2, "--silent"))
            record(output_dir, false);
    }

    else
        printUsage(argc, argv);

    return 0;
}
