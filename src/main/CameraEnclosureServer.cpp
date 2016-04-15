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

int run(std::string endpointAddress, std::string portNumber) {

    ICameraMultiplexer *mux;

#ifdef SAILBOT_DEBUG
    mux = new MockCameraMultiplexer();
#else
    // TODO: set more fine-grained controls on which leptons are used
    mux = new LeptonMultiplexer(true, true);
#endif
    zmq::context_t context;
    TCPCameraCommsPub publisher(context, endpointAddress, portNumber, *mux);

    for (;;) {
        pause();
    }

    return 0;
}

int main(int argc, char **argv) {

    if (argc < 2) {
        std::cout << std::endl;
        std::cout << "Usage: " << APPNAME << " [IPv4_address] [port#] [leptonID]" << std::endl;
        std::cout << std::endl;
        std::cout << "e.g. ./" << APPNAME << " " << "'*' 5555" << std::endl;
        std::cout << std::endl;
        std:: cout << "This binds an instance of cameraServer to any available interface "
            "on this device, on port 5555, connecting to two Leptons: one on "
            "SPI_CS_0, the other on SPI_CS_1." << std::endl;
        exit(0);
    }

    std::string address(argv[1]), port(argv[2]);

    run(address, port);

    return 0;
}
