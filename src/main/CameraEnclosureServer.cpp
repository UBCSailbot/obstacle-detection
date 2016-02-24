#include <string>
#include <comm/TCPImageServer.h>
#include <io/Paths.h>
#include <Resources.h>
#include <io/FileSystemImageStream.h>
#include <camera/lepton/ThermalCameraStream.h>

#define APPNAME "cameraServer"

int run(std::string endpointAddress, std::string portNumber, int leptonID) {

    ImageStream *stream;

#ifdef DEBUG
    std::string inputFrameDir = Paths::join(Resources::RESOURCE_DIR, "img/16bit");
    stream = new FileSystemImageStream(inputFrameDir, "*.png");
#else
    stream = new ThermalCameraStream(Lepton(leptonID));
#endif

    TCPImageServer server(*stream, endpointAddress, portNumber);

    while (true) {
        // block indefinitely, keeping the server thread alive
    }

    return 0;
}

int main(int argc, char **argv) {

    if (argc < 3) {
        std::cout << "Usage: " << APPNAME << " [IPv4_address] [port#] [leptonID]" << std::endl;
        exit(0);
    }

    std::string address(argv[1]), port(argv[2]);
    int leptonID = atoi(argv[3]);

    run(address, port, leptonID);

    return 0;
}
