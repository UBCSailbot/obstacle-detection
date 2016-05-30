//
// Created by paul on 2015/05/09

#include <camera/lepton/ThermalCameraStream.h>
#include <camera/lepton/LeptonRegistry.h>
#include <io/TCPImageStream.h>
#include "LiveFeed.h"

#define APP_NAME "live_feed"


vector<uchar> imgToBuff(cv::Mat img) {
    vector<uchar> buff;//buffer for coding
    vector<int> param = vector<int>(2);

    param[0] = CV_IMWRITE_PNG_COMPRESSION;

    param[1] = 3;//default(3)  0-9.
    imencode(".png", img, buff, param);
    std::cout << "coded file size(png)" << buff.size() << endl;
    return buff;
}

LiveFeed::LiveFeed(ImageStream *stream, const DLibProcessor &dLibProcessor, char *output_dir,
                   bool runImu) : FeedReader(stream), dLibProcessor(dLibProcessor),
                                  zmqfeed(ZmqContextSingleton::getContext()), runImu(runImu), output_dir(output_dir) {

}

void LiveFeed::beforeCapture() {

    std::cout << "Starting Capture" << endl;
    zmqfeed.init(5555);
    if (runImu) {
        imu = new ParallelIMU;
        char imuFileName[128];
        sprintf(imuFileName, "%s/imuLog.txt", this->output_dir);
        imuLog.open(imuFileName);
    }
}

void LiveFeed::onImageRead(Image16bit image) {
    frame_counter++;
    char image_name[128];

    Image8bit frameRescaled(LeptonCameraSpecifications.pixelHeight, LeptonCameraSpecifications.pixelWidth);
    rescaler.scale16bitTo8bit(image, frameRescaled);

    sprintf(image_name, "%s/img_%06d.png", output_dir, frame_counter);
    imwrite(image_name, image);

    if (runImu) {
        imuLog << imu->getOrientation().toDataString();
    }

    vector<uchar> buff = imgToBuff(image);
    string encoded = base64_encode(buff.data(), buff.size());
    std::vector<dlib::rectangle> detectedRectangles = dLibProcessor.getObjectDetectionBoxes(frameRescaled);
    string *JSON = new string(makeJSON(encoded, detectedRectangles, IMAGE16BIT));
    zmqfeed.sendFrame((const uint8_t *) JSON->c_str(), JSON->size());
}

void LiveFeed::printUsage(int argc, char **argv) {
    std::cout << "Usage:\n"
            "liveFeeder file <input dir> <output dir> dlib_model.svm ...\n"
            "liveFeeder lepton imu_enabled/imu_disabled <output dir> dlib_model.svm ...\n"
            "liveFeeder network ip_address port <output dir> dlib_model.svm" << endl;
    std::cout << "You entered: " << endl;
    for (int i = 0; i < argc; i++)
        std::cout << argv[i];
    std::cout << endl;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        LiveFeed::printUsage(argc, argv);
        return 1;
    }

    dlib::object_detector<DLibProcessor::image_scanner_type> detector;
    std::vector<dlib::object_detector<DLibProcessor::image_scanner_type>> detectors;

    if (string(argv[1]) == "file") {
        for (int i = 4; i < argc; i++) {
            dlib::deserialize(argv[i]) >> detector;
            detectors.push_back(detector);
        }
        DLibProcessor dLibProcessor(detectors);

        LiveFeed liveFeed(new FileSystemImageStream(argv[2], "*.png"), dLibProcessor, argv[3], false);
        try {
            liveFeed.record();
        } catch (exception &e) {
            std::cout << e.what() << endl;
            //This is to give time for zeromq to finish sending when reading from file system
            sleep(5);
        }
    } else if (string(argv[1]) == "lepton") {
        for (int i = 4; i < argc; i++) {
            dlib::deserialize(argv[i]) >> detector;
            detectors.push_back(detector);
        }
        DLibProcessor dLibProcessor(detectors);
        while (1) {
            LiveFeed liveFeed(new ThermalCameraStream(LeptonRegistry::getLepton0()),
                              dLibProcessor, argv[3], string(argv[2]) == "imu_enabled");

            try {
                liveFeed.record();
            } catch (LeptonSPIOpenException &e) {
                std::cout << e.what() << endl;
                // wait 5 seconds and try to record
                sleep(5);
            }
        }
    } else if (string(argv[1]) == "network") {
        for (int i = 5; i < argc; i++) {
            dlib::deserialize(argv[i]) >> detector;
            detectors.push_back(detector);
        }
        DLibProcessor dLibProcessor(detectors);
        LiveFeed liveFeed(new TCPImageStream(argv[2], argv[3]), dLibProcessor, argv[4], false);
        try {
            liveFeed.record();
        } catch (exception &e) {
            std::cout << e.what() << endl;
        }

    } else {
        LiveFeed::printUsage(argc, argv);
    }

    return 0;
}
