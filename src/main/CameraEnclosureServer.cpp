#include <string>
#include <comm/TCPImageServer.h>
#include <comm/TCPCameraCommsSub.h>
#include <paths/Paths.h>
#include <paths/Resources.h>
#include <io/FileSystemImageStream.h>
#include <camera/lepton/ThermalCameraStream.h>
#include <camera/lepton/LeptonRegistry.h>
#include <camera/ICameraMultiplexer.h>
#include <camera/LeptonMultiplexer.h>
#include <camera/MockCameraMultiplexer.h>
#include <comm/TCPCameraCommsPub.h>
#include <config/Config.h>
#include <comm/ZmqContextSingleton.h>

#define APPNAME "cameraServer"

using namespace std;

/**
 * Spins up an instance of a server that publishes zmq messages carrying
 *  one or more 16bit grayscale images obtained from a CameraMultiplexer.
 * In debug mode, sends test images saved in a local directory;
 *  otherwise, attempts to connect to one or more Leptons and streams
 *  ouptut from them.
 *
 * For usage notes, see those that are printed out in main().
 */
void runFileStream(const od::Config &topLevelConfig) {
    const auto &enclosureConfig = topLevelConfig.camera_enclosure();
    const auto &commsConfig = topLevelConfig.comms();

    // TODO: (low priority for now) Make mock camera mux use an input directory
    MockCameraMultiplexer mux;
    TCPCameraCommsPub publisher(ZmqContextSingleton::getContext(),
                                "*",
                                commsConfig.camera_server_pub_port(),
                                mux);

    for (;;) {
        pause();
    }
}

void runLeptonStream(const od::Config &topLevelConfig) {
    const auto &leptonConfig = topLevelConfig.camera_enclosure().lepton();
    const auto &sunConfig = topLevelConfig.perception().sun_detection();
    const auto &commsConfig = topLevelConfig.comms();

    LeptonMultiplexer mux(leptonConfig, sunConfig);
    TCPCameraCommsPub publisher(ZmqContextSingleton::getContext(),
                                "*",
                                commsConfig.camera_server_pub_port(),
                                mux);

    for (;;) {
        pause();
    }
}

void printUsage(int argc, char **argv) {
    std::cout << "Usage:\n" <<
            APPNAME << " [path/to/config.txt]" << std::endl;
    std::cout << "You entered: " << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i];
    }
    std::cout << std::endl;
}

int main(int argc, char **argv) {

    if (argc < 2) {
        printUsage(argc, argv);
        return 1;
    }

    od::Config config(argv[1]);

    typedef od::Config::camera_enclosure_config::ImageSource EnclosureImageSource;

    switch (config.camera_enclosure().image_source()) {
        case EnclosureImageSource::FILE:
            runFileStream(config);
            break;
        case EnclosureImageSource::LEPTON:
            runLeptonStream(config);
            break;
        default:
            printUsage(argc, argv);
    }

    return 0;
}
