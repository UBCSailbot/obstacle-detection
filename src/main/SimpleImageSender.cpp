#include <types/CameraData.h>
#include <io/cameradata/CameraDataStream.h>
#include <thread>
#include <imageProc/rescale/SimpleRescaler.h>
#include <iostream>
#include <config/Config.h>
#include <comm/ZmqContextSingleton.h>
#include <comm/ImageFeedZmq.h>
#include <QtCore/QDir>
#include <io/cameradata/ImageStreamCameraDataAdapter.h>
#include <io/FileSystemImageStream.h>
#include <io/cameradata/CameraDataNetworkStream.h>
#include <imageProc/liveFeed/base64EncDec.h>
#include <io/JSONSerializer.h>

static constexpr auto kFrameCountLog = "image_count";

class SimpleImageSender {
public:

    SimpleImageSender(CameraDataStream &stream, const od::Config &config) :
            zmqfeed_(ZmqContextSingleton::getContext()),
            imageOutputDir_(config.adavision().output().data_dir()),
            stream_(stream) {
        zmqfeed_.init(config.comms().live_feed_pub_port());

        const auto imageOutputDir = config.adavision().output().data_dir();
        if (!QDir(imageOutputDir.c_str()).exists()) {
            QDir().mkdir(imageOutputDir.c_str());
        }
        std::ifstream frameLogIn(kFrameCountLog);
        if (frameLogIn.is_open()) {
            std::string count;
            while (getline(frameLogIn, count)) {
                savedImageCount_ = std::stoi(count);
            }
            frameLogIn.close();
        }

    }


    void run() {
        int frame_counter = 0;

        while (true) {
            std::vector<CameraData> dataVector = stream_.nextImage();
            std::vector<std::string> encodedImages;
            frame_counter++;

            int i = 0;
            for (const CameraData &data : dataVector) {
                if (data.status != OK) {
                    continue;
                }
                auto frame = data.frame;
                Image8bit rescaled;
                rescaler_.scale16bitTo8bit(frame, rescaled);
                if (frame_counter % 60 == 0) {
                    saveImage(savedImageCount_, i, frame);
                    remove(kFrameCountLog);
                    frameCountLog_.open(kFrameCountLog);
                    frameCountLog_ << savedImageCount_;
                    frameCountLog_.close();
                }
                encodedImages.push_back(imageToBuffer(rescaled));
                i++;
            }
            if (frame_counter % 60 == 0) {
                savedImageCount_++;
            }

            std::string json(JSONSerializer::makeJSON(encodedImages));
            zmqfeed_.sendFrame(json);
            std::cout << "send image " << frame_counter << std::endl;


            std::this_thread::sleep_for(std::chrono::seconds(10));
        }

    }

private:
    void saveImage(int frame_counter, int image_count, const cv::Mat &image) const {
        std::ostringstream stringStream;
        std::vector<int> params(2);
        params[0] = CV_IMWRITE_PNG_COMPRESSION;
        params[1] = lPngCompressionLevel;
        stringStream << imageOutputDir_ << "/img_" << frame_counter << "_" << image_count << ".png";
        imwrite(stringStream.str(), image, params);
    }

    std::string imageToBuffer(cv::Mat img) {
        std::vector<uchar> buff;
        std::vector<int> params(2);
        params[0] = CV_IMWRITE_JPEG_QUALITY;
        params[1] = kJpegCompressionLevel;

        cv::imencode(".jpeg", img, buff, params);

        return base64_encode(buff.data(), buff.size());

    }

    static constexpr int lPngCompressionLevel = 9;
    static constexpr int kJpegCompressionLevel = 50;

    CameraDataStream &stream_;
    SimpleRescaler rescaler_;
    ImageFeedZmq zmqfeed_;
    std::string imageOutputDir_;
    std::ofstream frameCountLog_;
    int savedImageCount_ = 0;
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

void runSimpleImageSenderFromFile(const od::Config &masterConfig) {
    const auto &fileConfig = masterConfig.adavision().file_input();

    FileSystemImageStream fileStream(fileConfig.input_frame_dir(), "*.png");
    ImageStreamCameraDataAdapter imageStreamCameraDataAdapter(fileStream, fileConfig.double_up());
    CameraDataStream &cameraDataStream = imageStreamCameraDataAdapter;
    SimpleImageSender simpleImageSender(cameraDataStream, masterConfig);

    try {
        simpleImageSender.run();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void runSimpleImageSenderNetwork(const od::Config &masterConfig) {
    const auto &commsConfig = masterConfig.comms();
    CameraDataNetworkStream cameraDataNetworkStream(commsConfig.camera_server_ip(), commsConfig.camera_server_pub_port());
    SimpleImageSender simpleImageSender(cameraDataNetworkStream, masterConfig);

    try {
        simpleImageSender.run();
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}


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
            runSimpleImageSenderFromFile(config);
            break;
        case AdaVisionImageSource::NETWORK:
            runSimpleImageSenderNetwork(config);
            break;
        default:
            printUsage(argc, argv);
            break;
    }

}
