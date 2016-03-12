//
// Created by paul on 2015/05/09

#include <camera/lepton/ThermalCameraStream.h>
#include <camera/lepton/LeptonRegistry.h>
#include <io/TCPImageStream.h>
#include <imageProc/liveFeed/Compressor.h>
#include "LiveFeed.h"

#define APP_NAME "live_feed"

LiveFeed::LiveFeed(ImageStream *stream, const DLibProcessor &dLibProcessor, char *output_dir,
                   bool runImu) : FeedReader(stream), dLibProcessor(dLibProcessor),
                                  zmqfeed(ZmqContextSingleton::getContext()), runImu(runImu), output_dir(output_dir) {

}

void LiveFeed::beforeCapture() {

    std::cout << "Starting Capture" << std::endl;
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

    sprintf(image_name, "%s/img_%06d.png", output_dir, frame_counter);
    imwrite(image_name, image);

    if (runImu) {
        imuLog << imu->getOrientation().toDataString();
    }

    std::vector<uchar> buff = Compressor::imgToBuff(image, 3);
    std::string encoded = base64_encode(buff.data(), buff.size());
    std::vector<cv::Rect> detectedRectangles = dLibProcessor.getObjectDetectionBoxes(image);
    std::string JSON(JSONSerializer::makeJSON(encoded, detectedRectangles, IMAGE16BIT));
    zmqfeed.sendFrame((const uint8_t *) JSON.c_str(), JSON.size());
}

void LiveFeed::printUsage(int argc, char **argv) {
    std::cout << "Usage:\n"
            "liveFeeder file <input dir> <output dir> dlib_model.svm ...\n"
            "liveFeeder lepton imu_enabled/imu_disabled <output dir> dlib_model.svm ...\n"
            "liveFeeder network ip_address port <output dir> dlib_model.svm" << std::endl;
    std::cout << "You entered: " << std::endl;
    for (int i = 0; i < argc; i++)
        std::cout << argv[i];
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        LiveFeed::printUsage(argc, argv);
        return 1;
    }

    dlib::object_detector<DLibProcessor::image_scanner_type> detector;
    std::vector<dlib::object_detector<DLibProcessor::image_scanner_type>> detectors;

    if (std::string(argv[1]) == "file") {
        for (int i = 4; i < argc; i++) {
            dlib::deserialize(argv[i]) >> detector;
            detectors.push_back(detector);
        }
        DLibProcessor dLibProcessor(detectors);

        LiveFeed liveFeed(new FileSystemImageStream(argv[2], "*.png"), dLibProcessor, argv[3], false);
        try {
            liveFeed.record();
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            //This is to give time for zeromq to finish sending when reading from file system
            sleep(5);
        }
    } else if (std::string(argv[1]) == "lepton") {
        for (int i = 4; i < argc; i++) {
            dlib::deserialize(argv[i]) >> detector;
            detectors.push_back(detector);
        }
        DLibProcessor dLibProcessor(detectors);
        while (1) {
            LiveFeed liveFeed(new ThermalCameraStream(LeptonRegistry::getLepton0()),
                              dLibProcessor, argv[3], std::string(argv[2]) == "imu_enabled");

            try {
                liveFeed.record();
            } catch (LeptonException &e) {
                std::cout << e.what() << std::endl;
                // wait 5 seconds and try to record
                sleep(5);
            }
        }
    } else if (std::string(argv[1]) == "network") {
        for (int i = 5; i < argc; i++) {
            dlib::deserialize(argv[i]) >> detector;
            detectors.push_back(detector);
        }
        DLibProcessor dLibProcessor(detectors);
        LiveFeed liveFeed(new TCPImageStream(argv[2], argv[3]), dLibProcessor, argv[4], false);
        try {
            liveFeed.record();
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }

    } else {
        LiveFeed::printUsage(argc, argv);
    }

    return 0;
}
