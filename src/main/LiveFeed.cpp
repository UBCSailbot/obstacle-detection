//
// Created by paul on 2015/05/09

#include <io/ImageStream.h>
#include <io/FileSystemImageStream.h>
#include "LiveFeed.h"

#define APP_NAME "live_feed"


vector<uchar> imgToBuff(Image8bit img) {
    vector<uchar> buff;//buffer for coding
    vector<int> param = vector<int>(2);

    param[0] = CV_IMWRITE_PNG_COMPRESSION;

    param[1] = 3;//default(3)  0-9.
    imencode(".png", img, buff, param);
    std::cout << "coded file size(png)" << buff.size() << endl;
    return buff;
}

LiveFeed::LiveFeed(const DLibProcessor &dLibProcessor, char *output_dir) : dLibProcessor(dLibProcessor),
                                                                           zmqfeed(ZmqContextSingleton::getContext()) {

}

void LiveFeed::beforeCapture() {

    std::cout << "Starting Capture" << endl;
    zmqfeed.init();
    char imuFileName[128];
    sprintf(imuFileName, "%s/imuLog.txt", this->output_dir);
    imuLog.open(imuFileName);

    std::cout << "Starting Capture" << endl;
}

void LiveFeed::onImageRead(Image16bit image) {
    frame_counter++;

    Image8bit frameRescaled(VIEWPORT_HEIGHT_PIX, VIEWPORT_WIDTH_PIX);

    // convert to 8 bit and display
    rescaler.scale16bitTo8bit(image, frameRescaled);

    sprintf(image_name, "%s/raw/img_%06d.png", output_dir, frame_counter);
    imwrite(image_name, image);
    imuLog << imu.getOrientation().toDataString();

    vector<uchar> buff = imgToBuff(frameRescaled);
    string encoded = base64_encode(buff.data(), buff.size());
    std::vector<dlib::rectangle> dets = dLibProcessor.getObjectedDetectionBoxes(frameRescaled);

    string JSON = makeJSON(encoded, dets);
    zmqfeed.sendFrame((const uint8_t *) JSON.c_str(), JSON.size());
}

void LiveFeed::printUsage(int argc, char **argv) {
    std::cout << "Usage: live Feed <output_dir> -silent/verbose model.svm ..." << endl;
    std::cout << "You entered: " << endl;
    for (int i = 0; i < argc; i++)
        std::cout << argv[i];
    std::cout << endl;
}

int main(int argc, char **argv) {
    dlib::object_detector<DLibProcessor::image_scanner_type> detector;
    std::vector<dlib::object_detector<DLibProcessor::image_scanner_type> > detectors;
    for (int i = 3; i < argc; i++) {
        dlib::deserialize(argv[i]) >> detector;
        detectors.push_back(detector);
    }

    DLibProcessor dLibProcessor(detectors);

    LiveFeed liveFeed(dLibProcessor, argv[1]);

    ImageStream *stream = new FileSystemImageStream("/images", "png");
    liveFeed.setStream(stream);
    while (1) {
        try {
            if (argc < 3) {
                liveFeed.printUsage(argc, argv);
                return 1;
            }
            char *arg2 = argv[2];
            if (!strcmp(arg2, "--silent")) {
                liveFeed.record();
            }
            else {
                liveFeed.record();
            }

        } catch (LeptonSPIOpenException &e) {
            std::cout << e.what() << endl;
            // wait 5 seconds and try to record
            sleep(5);
        }
    }

    return 0;
}
