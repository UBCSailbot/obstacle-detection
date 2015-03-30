#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <string.h>
#include <iostream>
#include <signal.h>

#include "../imu/imu.h"
#include "../lepton_video/Lepton.h"


using namespace std;
using namespace cv;

#define APP_NAME "rig_record"


bool stop_record = false;

static void hangup_handler(int signum) {
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

void record(char* output_dir, bool verbose=true ) {
	
	// Lepton lepton;
	Imu imu;
	
	Mat eightBit(60, 80, CV_8UC1);
	Mat frame(60, 80, CV_16UC1);
	int frame_counter = 0;
	char img_name[50];

	std::ofstream imuLog;
	imuLog.open ("imu.txt");

	cout << "Starting Capture" << endl;

	while (!stop_record) {

		ImuData imuData = imu.getData();
		// lepton.GetFrame(frame, eightBit);

		// save the current frame as a .png file		
		// sprintf(file_name, "img_%06d.png", frame_counter);
		// cv::imwrite(output_dir + "/" + file_name, frame);

		imuLog << imuData.to_raw_str();
		if (verbose)
			cout << imuData.to_pretty_str();
	}

	imuLog.close();
	cout << "Recording received stopping signal\
			 and terminated gracefully." << endl;

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

	if (argc == 3) {
		char* arg2 = argv[2];
		if (!strcmp(arg2, "--silent"))
			record(output_dir, false);
	}

	else
		printUsage(argc, argv);
}