//
// Created by denis on 07/06/16.
//

#include <iostream>
#include <imageProc/dlib/DLibProcessor.h>
#include <io/cameradata/CameraDataHandler.h>
#include <opencv2/highgui/highgui.hpp>
#include <imageProc/liveFeed/base64EncDec.h>
#include <io/JSONSerializer.h>
#include <comm/ImageFeedZmq.h>
#include <imageProc/liveFeed/Compressor.h>
#include <io/cameradata/CameraDataProcessor.h>
#include <io/FileSystemImageStream.h>
#include <io/cameradata/ImageStreamCameraDataAdapter.h>
#include <io/cameradata/CameraDataImageStreamAdapter.h>
#include <io/cameradata/CameraDataNetworkStream.h>
#include <iostream>


class AdaVisionHandler : public CameraDataHandler {

public:

    AdaVisionHandler(char *output_dir, int zmqPort)
            : CameraDataHandler(), zmqfeed(ZmqContextSingleton::getContext()), output_dir(output_dir),
              zmqPort(zmqPort) {
        zmqfeed.init(zmqPort);
    }

    void onMultiImageProcessed(std::vector<CameraData> cameraData,
                               std::vector<dlib::rectangle> detectedRectangles) {
        std::cout << "received image" << std::endl;

        frame_counter++;
        char image_name[128];

        std::sprintf(image_name, "%s/img_%06d.png", output_dir, frame_counter);
        cv::imwrite(image_name, cameraData[0].frame);
    }

    void onSingleImageProcessed(CameraData cameraData, std::vector<dlib::rectangle> detectedRectangles) {
        frame_counter++;
        char image_name[128];

        std::sprintf(image_name, "%s/img_%06d.png", output_dir, frame_counter);
        cv::imwrite(image_name, cameraData.frame);

        //TODO add imu logging

        vector<uchar> buff = Compressor::imgToBuff(cameraData.frame, 3);
        string encoded = base64_encode(buff.data(), buff.size());
        unique_ptr<string> JSON(new string(makeJSON(encoded, detectedRectangles, IMAGE16BIT)));
        zmqfeed.sendFrame((const uint8_t *) JSON->c_str(), JSON->size());

    }

private:
    int frame_counter = 0;

    char *output_dir;

    ImageFeedZmq zmqfeed;

    int zmqPort;

};


void printUsage(int argc, char **argv) {
    std::cout << "Usage:\n"
            "adaVision file <input dir> <output dir> dlib_model.svm ...\n"
            "adaVision network ip_address port <output dir> dlib_model.svm" << std::endl;
    std::cout << "You entered: " << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i];
    }
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printUsage(argc, argv);
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

        CameraDataProcessor cameraDataProcessor(
                new ImageStreamCameraDataAdapter(new FileSystemImageStream(argv[2], "*.png"), false), NULL,
                &dLibProcessor, new AdaVisionHandler(argv[3], 5555));
        try {
            cameraDataProcessor.run();
        } catch (std::exception &e) {
            std::cout << e.what() << endl;
            //This is to give time for zeromq to finish sending when reading from file system
            sleep(5);
        }

    } else if (string(argv[1]) == "network") {

        for (int i = 5; i < argc; i++) {
            dlib::deserialize(argv[i]) >> detector;
            detectors.push_back(detector);
        }
        DLibProcessor dLibProcessor(detectors);

        CameraDataProcessor cameraDataProcessor(new CameraDataNetworkStream(argv[2], argv[3]), NULL, &dLibProcessor,new AdaVisionHandler(argv[4], 5555));

        try {
            cameraDataProcessor.run();
        } catch (exception &e) {
            std::cout << e.what() << endl;
        }

    } else {
        printUsage(argc, argv);
    }
}

