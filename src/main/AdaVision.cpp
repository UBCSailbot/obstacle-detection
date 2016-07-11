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
#include <config/BadConfigException.h>
#include <comm/CurrentDataConnection.h>
#include <io/MockBoatDataStream.h>
#include <logger/Logger.h>

/*
 * This class is the core handler of events while processing images on Ada.
 */
class AdaVisionHandler : public CameraDataHandler {

public:

    AdaVisionHandler(std::string imageOutputDir, std::string logOutputDir, const int imageFeedZmqPort, const bool debug,
                     const int frameSkip)
            : CameraDataHandler(), _zmqfeed(ZmqContextSingleton::getContext()),
              _zmqPort(imageFeedZmqPort), _imageOutputDir(imageOutputDir), _debug(debug), _frameSkip(frameSkip),
              _dangerZoneSender(ZmqContextSingleton::getContext()) {

        _zmqfeed.init(imageFeedZmqPort);
        if (!QDir(imageOutputDir.c_str()).exists()) {
            QDir().mkdir(imageOutputDir.c_str());
        }
        if (!QDir(logOutputDir.c_str()).exists()) {
            QDir().mkdir(logOutputDir.c_str());
        }

        imuLog.open(logOutputDir + "/imulog.txt");

    }

    void onImageProcessed(const std::vector<CameraData> &cameraData,
                          const std::vector<cv::Rect> &detectedRectangles) {
        _skippedCounter++;
        if (_frameSkip <= 0 || _skippedCounter % _frameSkip == 0) {
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
            if (detectedRectangles.size() > 0) {
                std::cout << "rectangles:" << std::endl;
                for (auto const &rectangle: detectedRectangles) {
                    std::cout << rectangle << std::endl;
                }
            }
        }

        Image16bit img = cameraData[0].frame;
        _frameCounter++;
        std::ostringstream leftImageName;
        leftImageName << _imageOutputDir << "/img_" << _frameCounter << "_L" << ".png";
        cv::imwrite(leftImageName.str(), img);

        std::ostringstream rightImageName;
        rightImageName << _imageOutputDir << "/img_" << _frameCounter << "_R" << ".png";
        cv::imwrite(rightImageName.str(), cameraData[1].frame);

        //TODO something smarter than this...
        int cameraToUse = _frameCounter % 2;
        std::vector<uchar> buff = Compressor::imgToBuff(cameraData[cameraToUse].frame, 3);
        sendProcessedImage(detectedRectangles, buff);
    }

    void onSingleImageProcessed(const CameraData &cameraData, std::vector<cv::Rect> detectedRectangles) {
        if (_debug) {
            std::cout << "single received image" << std::endl;
            if (detectedRectangles.size() > 0) {
                std::cout << "rectangles:" << std::endl;
                for (auto const &rectangle: detectedRectangles) {
                    std::cout << rectangle << std::endl;
                }
            }
        }

        _frameCounter++;
        std::ostringstream stringStream;
        stringStream << _imageOutputDir << "/img_" << _frameCounter << ".png";
        cv::imwrite(stringStream.str(), cameraData.frame);

        std::vector<uchar> buff = Compressor::imgToBuff(cameraData.frame, 3);
        sendProcessedImage(detectedRectangles, buff);
    }

    void sendProcessedImage(const std::vector<cv::Rect> &detectedRectangles, std::vector<uchar> &buff) {
        std::string encoded = base64_encode(buff.data(), buff.size());
        std::string json(JSONSerializer::makeJSON(encoded, detectedRectangles, IMAGE16BIT));
        _zmqfeed.sendFrame((const uint8_t *) json.c_str(), json.size());
    }

    void onDangerZoneProcessed(const std::vector<DangerZone> &dangerZones) {
        std::ostringstream stringStream;
        for (auto const &dangerZone: dangerZones) {
            stringStream << "dangerzone:" << std::endl;
            stringStream << " sb :" << dangerZone.getStarboardAngleDeg();
            stringStream << " p:" << dangerZone.getPortAngleDeg();
            stringStream << " l:" << dangerZone.getLateralOffsetMeters() << std::endl;
        }
        od::Logger::log(od::Logger::INFO, stringStream.str(), _debug);

        _dangerZoneSender.sendDangerZone(dangerZones);
    }

    virtual void onOrientationReceived(const Orientation &orientation) override {
        if (_frameSkip <= 0 || _skippedCounter % _frameSkip == 0) {

            imuLog << "frame:" << _frameCounter << " " << orientation.toDataString();
            imuLog.flush();

        }
    }


private:
    int _frameCounter = 0;

    std::string _imageOutputDir;

    ImageFeedZmq _zmqfeed;

    DangerZoneSender _dangerZoneSender;

    int _zmqPort;

    int _skippedCounter = 0;

    bool _debug;

    int _frameSkip;

    std::ofstream imuLog;

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

std::shared_ptr<IMU> getImu(const AdaVisionConfig::Imu &imuConfig) {
    switch (imuConfig.mode()) {
        case AdaVisionConfig::Imu::REAL: {
            return std::shared_ptr<IMU>(new ParallelIMU());
        }
        case AdaVisionConfig::Imu::STUB: {
            return std::shared_ptr<IMU>(new StubIMU(0, 0, 0));
        }
        case AdaVisionConfig::Imu::FILE:
            //TODO add file reader for IMU
            throw BadConfigException("file reading isn't currently supported for IMU's");
        default:
            throw BadConfigException("This imuConfig is unsupported");

    }
}

std::shared_ptr<BoatDataStream> getBoatDataStream(const AdaVisionConfig::CurrentData &currentDataConfig) {
    switch (currentDataConfig.mode()) {
        case AdaVisionConfig::CurrentData::REAL: {
            return std::shared_ptr<BoatDataStream>(
                    new CurrentDataConnection(ZmqContextSingleton::getContext(), currentDataConfig.zmqAddress()));
        }
        case AdaVisionConfig::CurrentData::STUB: {
            return std::shared_ptr<BoatDataStream>(
                    new MockBoatDataStream(currentDataConfig.mockHeading()));
        }
        default:
            throw BadConfigException("This config is unsupported");

    }
}


void runAdaVisionFromFiles(const AdaVisionConfig &config) {
    const auto &fileConfig = config.imageSource().file();
    DLibProcessor dLibProcessor(config.machineLearning().models().all());
    AdaVisionHandler adaVisionHandler(config.output().dataDir(),
                                      config.output().logDir(),
                                      std::stoi(config.output().liveFeedPort()),
                                      config.global().debug(),
                                      config.output().frameSkip());
    FileSystemImageStream fileStream(fileConfig.inputDir(), "*.png");
    ImageStreamCameraDataAdapter imageStreamCameraDataAdapter(fileStream, fileConfig.doubleUp());
    CameraDataStream &cameraDataStream = imageStreamCameraDataAdapter;

    std::shared_ptr<IMU> pIMU = getImu(config.imu());
    std::shared_ptr<BoatDataStream> boatDataStream = getBoatDataStream(config.currentData());

    CameraDataProcessor cameraDataProcessor(cameraDataStream, dLibProcessor, adaVisionHandler, *pIMU, *boatDataStream);
    try {
        cameraDataProcessor.run();
    } catch (std::exception &e) {
        std::cout << e.what() << endl;
    }
}


void runAdaVisionFromNetwork(const AdaVisionConfig &config) {
    const auto &networkConfig = config.imageSource().network();
    DLibProcessor dLibProcessor(config.machineLearning().models().all());
    AdaVisionHandler adaVisionHandler(config.output().dataDir(),
                                      config.output().logDir(),
                                      std::stoi(config.output().liveFeedPort()),
                                      config.global().debug(),
                                      config.output().frameSkip());
    CameraDataNetworkStream cameraDataNetworkStream(networkConfig.imagePubIP(), networkConfig.imagePubPort());
    std::shared_ptr<IMU> pIMU = getImu(config.imu());
    std::shared_ptr<BoatDataStream> boatDataStream = getBoatDataStream(config.currentData());

    CameraDataProcessor cameraDataProcessor(cameraDataNetworkStream, dLibProcessor, adaVisionHandler, *pIMU,
                                            *boatDataStream);

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

