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
#include <io/cameradata/CameraDataNetworkStream.h>
#include <QtCore/QTS>
#include <config/AdaVisionConfig.h>
#include <comm/DangerZoneSender.h>
#include <imu/StubIMU.h>

/*
 * This class is the core handler of events while processing images on ada.
 */
class AdaVisionHandler : public CameraDataHandler {

public:

    AdaVisionHandler(std::string outputDir, const int imageFeedZmqPort, const bool debug, const int frameSkip,
                     int routemakingZmqPort)
            : CameraDataHandler(), _zmqfeed(ZmqContextSingleton::getContext()),
              _zmqPort(imageFeedZmqPort), _outputDir(outputDir), _debug(debug), _frameSkip(frameSkip),
              _dangerZoneSender(ZmqContextSingleton::getContext(), routemakingZmqPort) {

        _zmqfeed.init(imageFeedZmqPort);
        if (!QDir(outputDir.c_str()).exists()) {
            QDir().mkdir(outputDir.c_str());
        }
    }

    void onImageProcessed(std::vector<CameraData> cameraData,
                          std::vector<cv::Rect> detectedRectangles) {
        _skippedCounter++;
        if (_frameSkip <= 0 || _skippedCounter % _frameSkip == 0) {
            //TODO add imu logging
            if (cameraData.size() == 1) {
                onSingleImageProcessed(cameraData[0], detectedRectangles);
            } else {
                onMultiImageProcessed(cameraData, detectedRectangles);
            }
        }
    }

    void onMultiImageProcessed(const std::vector<CameraData> &cameraData,
                               const std::vector<cv::Rect> detectedRectangles) {
        if (_debug) {
            std::cout << "received two images" << std::endl;
            std::cout << "rectangles:" << std::endl;
            for (auto const &rectangle: detectedRectangles) {
                std::cout << rectangle << std::endl;
            }
        }

        Image16bit img = cameraData[0].frame;
        _frameCounter++;
        std::ostringstream leftImageName;
        leftImageName << _outputDir << "/img_" << _frameCounter << "_L" << ".png";
        cv::imwrite(leftImageName.str(), img);

        std::ostringstream rightImageName;
        rightImageName << _outputDir << "/img_" << _frameCounter << "_R" << ".png";
        cv::imwrite(rightImageName.str(), cameraData[1].frame);

        //TODO something smarter than this...
        int cameraToUse = _frameCounter % 2;
        std::vector<uchar> buff = Compressor::imgToBuff(cameraData[cameraToUse].frame, 3);
        sendProcessedImage(detectedRectangles, buff);
    }

    void onSingleImageProcessed(CameraData cameraData, std::vector<cv::Rect> detectedRectangles) {
        if (_debug) {
            std::cout << "single received image" << std::endl;
            std::cout << "rectangles:" << std::endl;
            for (auto const &rectangle: detectedRectangles) {
                std::cout << rectangle << std::endl;
            }
        }

        _frameCounter++;
        std::ostringstream stringStream;
        stringStream << _outputDir << "/img_" << _frameCounter << ".png";
        cv::imwrite(stringStream.str(), cameraData.frame);

        std::vector<uchar> buff = Compressor::imgToBuff(cameraData.frame, 3);
        sendProcessedImage(detectedRectangles, buff);
    }

    void sendProcessedImage(const std::vector<cv::Rect> &detectedRectangles, std::vector<uchar> &buff) {
        std::string encoded = base64_encode(buff.data(), buff.size());
        std::string json(JSONSerializer::makeJSON(encoded, detectedRectangles, IMAGE16BIT));
        _zmqfeed.sendFrame((const uint8_t *) json.c_str(), json.size());
    }

    void onDangerZoneProcessed(std::vector<DangerZone> cameraData) {
        if (_debug) {
            for (auto const &dangerZone: cameraData) {
                std::cout << "starboard angle:" << dangerZone.getStarboardAngleDeg() << std::endl;
                std::cout << "port angle:" << dangerZone.getPortAngleDeg() << std::endl;
                std::cout << "lateral offset:" << dangerZone.getLateralOffsetMeters() << std::endl;
            }
        }
        //TODO, add sending for dangerzones
    }

private:
    int _frameCounter = 0;

    std::string _outputDir;

    ImageFeedZmq _zmqfeed;

    DangerZoneSender _dangerZoneSender;

    int _zmqPort;

    int _skippedCounter = 0;

    bool _debug;

    int _frameSkip;

};


void printUsage(int argc, char **argv) {
    std::cout << "Usage:\n"
            "adaVision config.txt" << std::endl;
    std::cout << "You entered: " << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i];
    }
    std::cout << std::endl;
}

void runAdaVisionFromFiles(const AdaVisionConfig &config) {
    const auto &fileConfig = config.imageSource().file();
    DLibProcessor dLibProcessor(config.machineLearning().models().all());
    AdaVisionHandler adaVisionHandler(config.output().dataDir(),
                                      std::stoi(config.output().liveFeedPort()),
                                      config.global().debug(),
                                      config.output().frameSkip(),
                                      std::stoi(config.output().dangerZonePubPort()));
    FileSystemImageStream fileStream(fileConfig.inputDir(), "*.png");
    ImageStreamCameraDataAdapter imageStreamCameraDataAdapter(fileStream, fileConfig.doubleUp());
    CameraDataStream &cameraDataStream = imageStreamCameraDataAdapter;

    //TODO add real IMU code
    StubIMU stubIMU(0, 0, 0);
    CameraDataProcessor cameraDataProcessor(cameraDataStream, dLibProcessor, adaVisionHandler, stubIMU);
    try {
        cameraDataProcessor.run();
    } catch (std::exception &e) {
        std::cout << e.what() << endl;
        //This is to give time for zeromq to finish sending when reading from file system
        sleep(5);
    }
}

void runAdaVisionFromNetwork(const AdaVisionConfig &config) {
    const auto &networkConfig = config.imageSource().network();
    DLibProcessor dLibProcessor(config.machineLearning().models().all());
    AdaVisionHandler adaVisionHandler(config.output().dataDir(),
                                      std::stoi(config.output().liveFeedPort()),
                                      config.global().debug(),
                                      config.output().frameSkip(),
                                      std::stoi(config.output().dangerZonePubPort()));
    CameraDataNetworkStream cameraDataNetworkStream(networkConfig.imagePubIP(), networkConfig.imagePubPort());

    //TODO add real IMU code
    StubIMU mockImu = StubIMU(0, 0, 0);

    CameraDataProcessor cameraDataProcessor(cameraDataNetworkStream, dLibProcessor, adaVisionHandler, mockImu);

    try {
        cameraDataProcessor.run();
    } catch (std::exception &e) {
        std::cout << e.what() << endl;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printUsage(argc, argv);
        return 1;
    }

    AdaVisionConfig config(argv[1]);

    switch (config.imageSource().source()) {
        case AdaVisionConfig::ImageSource::FILE:
            runAdaVisionFromFiles(config);
            break;
        case AdaVisionConfig::ImageSource::NETWORK:
            runAdaVisionFromNetwork(config);
            break;
        default:
            printUsage(argc, argv);
            break;
    }

}

