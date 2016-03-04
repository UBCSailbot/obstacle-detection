#include <string>
#include <comm/TCPImageServer.h>
#include <io/Paths.h>
#include <Resources.h>
#include <io/FileSystemImageStream.h>
#include <camera/lepton/ThermalCameraStream.h>

#define APPNAME "cameraServer"

/**
 * Spins up an instance of a server that listens for client requests for
 *  16bit grayscale images, and replies by sending images drawn from a
 *  stream. In DEBUG mode, sends test images saved in a local directory;
 *  otherwise, attempts to connect to the specified Lepton and streams
 *  ouptut from that device.
 *
 * For help on understanding this program, please see the usage notes printed
 *  in main().
 */

int run(std::string endpointAddress, std::string portNumber, int leptonID) {

    ImageStream *stream;

#ifdef DEBUG
    std::string inputFrameDir = Paths::join(Resources::RESOURCE_DIR, "img/16bit");
    stream = new FileSystemImageStream(inputFrameDir, "*.png");
#else
    stream = new ThermalCameraStream(Lepton(leptonID));
#endif

    TCPImageServer server(*stream, endpointAddress, portNumber);

    pause();

    return 0;
}

int main(int argc, char **argv) {

    if (argc < 3) {
        std::cout << std::endl;
        std::cout << "Usage: " << APPNAME << " [IPv4_address] [port#] [leptonID]" << std::endl;
        std::cout << std::endl;
        std::cout << "e.g. ./" << APPNAME << " " << "'*' 5555 0" << std::endl;
        std::cout << std::endl;
        std:: cout << "This binds an instance of cameraServer to any available interface "
            "on this device, on port 5555, connecting to a Lepton object "
            "initialized to be controlled by SPI_CS_0." << std::endl;
        exit(0);
    }

    std::string address(argv[1]), port(argv[2]);
    int leptonID = atoi(argv[3]);

    run(address, port, leptonID);

    return 0;
}
