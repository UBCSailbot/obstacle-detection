//
// Created by paul on 09/05/15 (dd/mm/yy, of course)
//

#include "LiveFeed.h"

#define APP_NAME "rig_record"

bool stop_record = false;

static void hangup_handler(int signum) {
    if (signum == SIGHUP)
        stop_record = true;
}


vector<uchar> imgToBuff(Image8bit img){
    vector<uchar> buff;//buffer for coding
    vector<int> param = vector<int>(2);

    param[0]=CV_IMWRITE_PNG_COMPRESSION;

    param[1]=3;//default(3)  0-9.
    imencode(".png",img,buff,param);
    cout<<"coded file size(png)"<<buff.size()<<endl;
    return buff;
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

    Image16bit frame(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX);
    Image8bit displayed(60, 80);
    int frame_counter = 1;
    char img_name[128];
    char imu_file_name[128];

    std::ofstream imuLog;

    // timing
    std::chrono::time_point<std::chrono::system_clock> start, end;
    float leptonPeriodSeconds = 1 / LEPTON_FPS;

    sprintf(imu_file_name, "%s/imuLog.txt", output_dir);
    imuLog.open (imu_file_name);

    cout << "Connecting to screen" << endl;

    Display* display = DisplayUtils::connectToDisplay();


    cout << "Starting Capture" << endl;

    while (!stop_record) {

        // Perform FFC every FFC_FREQ_SEC seconds
/*        if ( (frame_counter / LEPTON_FPS) % FFC_FREQ_SEC == FFC_FREQ_SEC - 1) {
            cout << "Performing FFC" << endl;
            lepton.performFFC();
            usleep(600 * 1000);
        }
*/
        start = std::chrono::system_clock::now();

        // read only every 3rd frame
        if ((frame_counter % 3) == 0) {
            lepton.getFrame(frame);

            // save the current frame as a .png file
            sprintf(img_name, "%s/raw/img_%06d.png", output_dir, frame_counter/3);
            imwrite(img_name, frame);
            imuLog << imu.toDataString();

//            Image8bit displayed(frame, false);
//            cv::cvtColor(frame, displayed, cv::COLOR_GRAY2BGR);
//            line(displayed, Point(0,30), Point(80, 40), Scalar(255,0,0), 1);
//
//            d.displayColored(displayed);

            // convert to 8 bit and display
            rescaler.scale16bitTo8bit(frame, displayed);

            //encode the frame for livefeed
            vector<uchar> buff = imgToBuff(displayed);
            string encoded = base64_encode(buff.data(), buff.size());
            //zeroMQ here

//            cout << "size" << buff.size();
//            vector<uchar> decoded = base64_decode(encoded, buff.size());


//            Mat pngimage = imdecode(decoded,CV_LOAD_IMAGE_COLOR);
//            cout << pngimage << endl;
//            imwrite(outputFilePath, pngimage);



           // DisplayUtils::displayFrameWithHorizonLine(displayed, imu.getRollRad(), imu.getPitchRad(), *display);
        }

        frame_counter ++;

        end = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsed_seconds = end-start;

        if (elapsed_seconds.count() < leptonPeriodSeconds) {
            unsigned int sleepTimeMicros = (unsigned int) (leptonPeriodSeconds - elapsed_seconds.count()) * 1000000;
            usleep(sleepTimeMicros);
        }

    }

    imuLog.flush();
    imuLog.close();
    cout << "Recording received stopping signal " <<
    "and terminated gracefully." << endl;

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
