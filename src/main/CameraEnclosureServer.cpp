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
void run(string endpointAddress, string portNumber, bool debug,
         bool useLepton0, bool useLepton1) {

    ICameraMultiplexer *mux;

    if(debug) {
        mux = new MockCameraMultiplexer();
    }
    else {
        mux = new LeptonMultiplexer(useLepton0, useLepton1);
    }

    zmq::context_t context;
    TCPCameraCommsPub publisher(context, endpointAddress, portNumber, *mux);

    for (;;) {
        pause();
    }

}

int main(int argc, char **argv) {

    if (argc < 4) {
        std::cout << std::endl;
        std::cout << "Usage: " << APPNAME << " [IPv4_address] [port#] [debug/lepton]" << std::endl;
        std::cout << std::endl;
        std::cout << "e.g. ./" << APPNAME << " " << "'*' 5555 lepton 1 1" << std::endl;
        std::cout << std::endl;
        std:: cout << "This binds an instance of cameraServer to any available interface "
            "on this device, on port 5555, connecting to two Leptons: one on "
            "SPI_CS_0, the other on SPI_CS_1." << std::endl;
        exit(0);
    }

    std::string address(argv[1]), port(argv[2]);

    char* mode = argv[3];

    if (!strcmp(mode, "lepton")) {
        if (argc < 6) {
            std::cout << "If lepton is specified, must include two more arguments"
                                 " both binary (i.e. 0 or 1): [useLepton0] and "
                                 "[useLepton1]." << std::endl;
            exit(0);
        }
        bool useLepton0 = atoi(argv[4]) != 0;
        bool useLepton1 = atoi(argv[5]) != 0;
        run(address, port, false, useLepton0, useLepton1);
    }
    else if (!strcmp(mode, "debug")) {
        run(address, port, true, 0, 0);
    }
    else {
        std::cout << "Error: Fourth argument must be one of 'debug' or 'lepton'." << std::endl;
    }

    return 0;
}
