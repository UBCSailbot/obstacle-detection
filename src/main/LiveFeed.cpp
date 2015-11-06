//
// Created by paul on 2015/05/09 

#include "LiveFeed.h"
#define APP_NAME "live_feed"


bool makeConnection = true;
ImageFeedZmq zmqfeed(ZmqContextSingleton::getContext());

vector<uchar> imgToBuff(Image8bit img){
    vector<uchar> buff;//buffer for coding
    vector<int> param = vector<int>(2);

    param[0]=CV_IMWRITE_PNG_COMPRESSION;

    param[1]=3;//default(3)  0-9.
    imencode(".png",img,buff,param);
    std::cout<<"coded file size(png)"<<buff.size()<<endl;
    return buff;
}


void record(char* output_dir, bool verbose) {
    Lepton lepton;
    // Connection made, set to 0 so doesn't try to connect again
    makeConnection = false;
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

    std::cout << "Starting Capture" << endl;

    zmqfeed.init();

    while (1) {

        start = std::chrono::system_clock::now();

        // read only every 3rd frame ( the frames are triplets)
        if ((frame_counter % 3) == 0) {
            lepton.getFrame(frame);

            // save the current frame as a .png file
            sprintf(img_name, "%s/raw/img_%06d.png", output_dir, frame_counter/3);
            imwrite(img_name, frame);
            imuLog << imu.toDataString();

            // convert to 8 bit and display
            rescaler.scale16bitTo8bit(frame, displayed);

            //encode the frame for livefeed
            vector<uchar> buff = imgToBuff(displayed);
            string encoded = base64_encode(buff.data(), buff.size());
            zmqfeed.sendFrame((const uint8_t *) encoded.c_str(), encoded.size());

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
    std::cout << "Recording received stopping signal " <<
    "and terminated gracefully." << endl;

}

void printUsage(int argc, char** argv) {
    std::cout << "Usage: live Feed <output_dir>" << endl;
    std::cout << "You entered: " << endl;
    for (int i=0; i<argc; i++)
        std::cout << argv[i];
    std::cout << endl;
}

int main(int argc, char** argv) {

    while(makeConnection){
        try{
            if(argc < 2){
	        printUsage(argc, argv);
                return 1;
            }

            char* output_dir = argv[1];

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
        } catch (LeptonSPIException& e){
            // try to reconnect
            makeConnection = true;
            std::cout << e.what() << endl;
            sleep(5);
        }
     }
    return 0;
}

