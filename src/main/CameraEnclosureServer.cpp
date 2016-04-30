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
void run(string endpointAddress, string portNumber, bool debug) {

    ICameraMultiplexer *mux;

    if(debug) {
        mux = new MockCameraMultiplexer();
    }
    else {
        // TODO: set more fine-grained controls on which leptons are used
        mux = new LeptonMultiplexer(true, true);
    }

    zmq::context_t context;
    TCPCameraCommsPub publisher(context, endpointAddress, portNumber, *mux);

    for (;;) {
        pause();
    }

}

int main(int argc, char **argv) {

    if (argc < 3) {
        std::cout << std::endl;
        std::cout << "Usage: " << APPNAME << " [IPv4_address] [port#]" << std::endl;
        std::cout << std::endl;
        std::cout << "e.g. ./" << APPNAME << " " << "'*' 5555" << std::endl;
        std::cout << std::endl;
        std:: cout << "This binds an instance of cameraServer to any available interface "
            "on this device, on port 5555, connecting to two Leptons: one on "
            "SPI_CS_0, the other on SPI_CS_1." << std::endl;
        exit(0);
    }

    std::string address(argv[1]), port(argv[2]);

    bool debug = false;
    if (argc == 4) {
        debug = true;
    }
    run(address, port, debug);

    return 0;
}
