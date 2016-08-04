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
#include <comm/DangerZoneSender.h>
#include <imu/StubIMU.h>
#include <config/BadConfigException.h>
#include <comm/CurrentDataConnection.h>
#include <io/MockBoatDataStream.h>
#include <logger/Logger.h>
#include <config/Config.h>

namespace {

void printUsage(int argc, char **argv) {
    std::cout << "Usage:\n"
            "adaVision config.txt" << std::endl;
    std::cout << "You entered: " << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i];
    }
    std::cout << std::endl;
}

} // anonymous namespace

namespace od {

/*
 * This class is the core handler of events while processing images on Ada.
 */
class AdaVisionHandler : public CameraDataHandler {

public:

    AdaVisionHandler(const Config &config) :
            CameraDataHandler(),
            _zmqfeed(ZmqContextSingleton::getContext()),
            _imageOutputDir(config.adavision().output().data_dir()),
            _debug(config.adavision().debug()),
            _frameSkip(config.adavision().output().frame_skip()),
            _dangerZoneSender(ZmqContextSingleton::getContext(), config.comms().dangerzone_channel()) {

        _zmqfeed.init(config.comms().live_feed_pub_port());

        const auto imageOutputDir = config.adavision().output().data_dir();
        if (!QDir(imageOutputDir.c_str()).exists()) {
            QDir().mkdir(imageOutputDir.c_str());
        }

        const auto logOutputDir = config.adavision().output().log_dir();
        if (!QDir(logOutputDir.c_str()).exists()) {
            QDir().mkdir(logOutputDir.c_str());
        }

        imuLog.open(logOutputDir + "/imulog.txt");
    }

    void onImageProcessed(const std::vector<CameraData> &cameraData, const std::vector<cv::Rect> &detectedRectangles, const Horizon &horizon) {
        _skippedCounter++;
        if (_frameSkip <= 0 || _skippedCounter % _frameSkip == 0) {
            if (cameraData.size() == 1) {
                onSingleImageProcessed(cameraData[0], detectedRectangles, horizon);
            } else {
                onMultiImageProcessed(cameraData, detectedRectangles, horizon);
            }
        }
    }

    void onMultiImageProcessed(const std::vector<CameraData> &cameraData, const std::vector<cv::Rect> detectedRectangles, const Horizon &horizon) {
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
        sendProcessedImage(detectedRectangles, buff, horizon);
    }

    void onSingleImageProcessed(const CameraData &cameraData, std::vector<cv::Rect> detectedRectangles, const Horizon &horizon) {
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
        sendProcessedImage(detectedRectangles, buff, horizon);
    }

    void sendProcessedImage(const std::vector<cv::Rect> &detectedRectangles, std::vector<uchar> &buff, const Horizon &horizon) {
        std::string encoded = base64_encode(buff.data(), buff.size());
        std::string json(JSONSerializer::makeJSON(encoded, detectedRectangles, IMAGE16BIT, horizon));
        _zmqfeed.sendFrame(json);
    }

    void onDangerZoneProcessed(const std::vector<DangerZone> &dangerZones) {
        std::ostringstream stringStream;
        if (_debug) {
            for (const auto &dangerZone : dangerZones) {
                stringStream << "dangerzone:" << std::endl;
                stringStream << " sb :" << dangerZone.getStarboardAngleDeg();
                stringStream << " p:" << dangerZone.getPortAngleDeg();
                stringStream << " l:" << dangerZone.getLateralOffsetMeters() << std::endl;
            }
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

    int _skippedCounter = 0;

    bool _debug;

    int _frameSkip;

    std::ofstream imuLog;

};

std::shared_ptr<IMU> getImu(const Config &masterConfig) {
    typedef Config::adavision_config::imu_config::ImuMode ImuMode;

    switch (masterConfig.adavision().imu().mode()) {
        case ImuMode::REAL:
            return std::shared_ptr<IMU>(new ParallelIMU());

        case ImuMode::STUB:
            return std::shared_ptr<IMU>(new StubIMU(0, 0, 0));

        case ImuMode::FILE:
            //TODO add file reader for IMU
            throw BadConfigException("file reading isn't currently supported for IMU's");

        default:
            throw BadConfigException("This imuConfig is unsupported");
    }
}

std::shared_ptr<BoatDataStream> getBoatDataStream(const Config &masterConfig) {
    typedef Config::adavision_config::current_data_config::CurrentDataMode CurrentDataMode;

    switch (masterConfig.adavision().current_data().mode()) {
        case CurrentDataMode::REAL:
            return std::shared_ptr<BoatDataStream>(
                    new CurrentDataConnection(
                            ZmqContextSingleton::getContext(),
                            masterConfig.comms().current_data_channel()));
        case CurrentDataMode::STUB:
            return std::shared_ptr<BoatDataStream>(
                    new MockBoatDataStream());
        default:
            throw BadConfigException("This config is unsupported");
    }
}

void runAdaVisionFromFiles(const Config &masterConfig) {

    const auto &fileConfig = masterConfig.adavision().file_input();
    DLibProcessor dLibProcessor(masterConfig.perception().boat_detection().models().all());

    AdaVisionHandler adaVisionHandler(masterConfig);

    FileSystemImageStream fileStream(fileConfig.input_frame_dir(), "*.png");
    ImageStreamCameraDataAdapter imageStreamCameraDataAdapter(fileStream, fileConfig.double_up());
    CameraDataStream &cameraDataStream = imageStreamCameraDataAdapter;

    std::shared_ptr<IMU> pIMU = getImu(masterConfig);
    std::shared_ptr<BoatDataStream> boatDataStream = getBoatDataStream(masterConfig);

    CameraDataProcessor cameraDataProcessor(cameraDataStream, dLibProcessor, adaVisionHandler, *pIMU,
                                            *boatDataStream);
    try {
        cameraDataProcessor.run();
    } catch (std::exception &e) {
        std::cout << e.what() << endl;
    }
}

void runAdaVisionFromNetwork(const Config &masterConfig) {
    const auto &commsConfig = masterConfig.comms();

    DLibProcessor dLibProcessor(masterConfig.perception().boat_detection().models().all());

    AdaVisionHandler adaVisionHandler(masterConfig);

    CameraDataNetworkStream cameraDataNetworkStream(commsConfig.camera_server_ip(),
                                                    commsConfig.camera_server_pub_port());

    std::shared_ptr<IMU> pIMU = getImu(masterConfig);
    std::shared_ptr<BoatDataStream> boatDataStream = getBoatDataStream(masterConfig);

    CameraDataProcessor cameraDataProcessor(cameraDataNetworkStream, dLibProcessor, adaVisionHandler, *pIMU,
                                            *boatDataStream);

    try {
        cameraDataProcessor.run();
    }
    catch (std::exception &e) {
        std::cout << e.what() << endl;
    }
}

} // od

int main(int argc, char **argv) {
    if (argc < 2) {
        printUsage(argc, argv);
        return 1;
    }

    od::Config config(argv[1]);
    const auto &adaVisionConfig = config.adavision();

    typedef od::Config::adavision_config::ImageSource AdaVisionImageSource;

    switch (adaVisionConfig.image_source()) {
        case AdaVisionImageSource::FILE:
            od::runAdaVisionFromFiles(config);
            break;
        case AdaVisionImageSource::NETWORK:
            od::runAdaVisionFromNetwork(config);
            break;
        default:
            printUsage(argc, argv);
            break;
    }

}
