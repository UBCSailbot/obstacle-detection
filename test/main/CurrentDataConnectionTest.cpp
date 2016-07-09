#include <zmq.hpp>
#include <comm/CurrentDataConnection.h>
#include <iostream>
#include <zconf.h>

void printUsage(int argc, char **argv) {
    std::cout << "Usage:\n"
            "currentDataConnectionTest ipc:///tmp/sailbot-currentdata-from-pi-controller" << std::endl;
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

    zmq::context_t context(1);

    std::string receiveAddress(argv[1]);

    CurrentDataConnection currentDataConnection(context, receiveAddress);
    CurrentData currentData;

    while (true) {
        if (currentDataConnection.checkForCurrentData()) {
            currentData = currentDataConnection.getBoatData();
            std::cout << "CLIENT: New CurrentData received!" << std::endl;
            std::cout << currentData.bearing() << ", " << currentData.speed_over_ground() << std::endl;
        }
        usleep(1000 * 1000);
    }

}
