#include "Lepton.h"

Lepton::Lepton(int spiChipSelect, int i2cBusID, int CAPTURE_FRAME_TIMEOUT) : _spiConnection(spiChipSelect),
                                                                             _i2cConnection(i2cBusID),
                                                                             _CAPTURE_FRAME_TIMEOUT(
                                                                                     CAPTURE_FRAME_TIMEOUT) {
    if (spiChipSelect == 0) {
        std::cout << "Lepton 0 Using gpio pin 20\n";
        _gpio = new GPIO("20");
    } else {
        std::cout << "Lepton 1 Using gpio pin 19\n";
        _gpio = new GPIO("19");
    }

    _gpio->exportGPIO();
    _gpio->setDirGPIO("out");
    _gpio->setValGPIO("1");

}

Lepton::~Lepton() {
    std::cout << "shutting off gpio\n";
    _gpio->setValGPIO("0");
    _gpio->unexportGPIO();
    delete _gpio;
}

Image16bit Lepton::captureFrame() {

    // keep track of start time, and current time. captureFrame will timeout after CAPTURE_FRAME_TIMEOUT seconds
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    // Read data packets from Lepton over SPI
    int resets = 0;
    for (int j = 0; j < PACKETS_PER_FRAME; j++) {
        ssize_t result = read(_spiConnection.getFileDescriptor(),
                              _result + sizeof(uint8_t) * PACKET_SIZE * j,
                              sizeof(uint8_t) * PACKET_SIZE);

        // TODO: check that read was successful
        int packetNumber = _result[j * PACKET_SIZE + 1];

        if (packetNumber != j) { // This suggests that a packet was dropped
            j = -1; // setting j to -1 means that it will be 0 again at the next iteration of the loop
            resets += 1;
            usleep(1000);
            if (resets == 750) {
                _spiConnection.reset(750000);
            }
        }

        // check to see if we timed out.
        end = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsed_seconds = end - start;

        if (elapsed_seconds.count() > _CAPTURE_FRAME_TIMEOUT) {
            // create an error message which includes the time:
            std::stringstream errorStream;
            errorStream << "captureFrame timed out after " << _CAPTURE_FRAME_TIMEOUT << " seconds.";
            std::string errorMsg = errorStream.str();
            throw LeptonException(errorMsg.c_str());

        }
    }

    _frameBuffer = (uint16_t *) _result;

    for (int i = 0; i < FRAME_SIZE_UINT16; i++) {
        // Skip the first 2 uint16_t's of every packet, they're 4 header bytes
        if (i % PACKET_SIZE_UINT16 < 2) {
            continue;
        }

        // Flip the MSB and LSB at the last second
        uint8_t temp = _result[i * 2];
        _result[i * 2] = _result[i * 2 + 1];
        _result[i * 2 + 1] = temp;

    }

    int row, column;
    Image16bit frame(LeptonCameraSpecifications.pixelHeight, LeptonCameraSpecifications.pixelWidth);

    for (int i = 0; i < FRAME_SIZE_UINT16; i++) {
        if (i % PACKET_SIZE_UINT16 < 2) {
            continue;
        }

        column = (i % PACKET_SIZE_UINT16) - 2;
        row = i / PACKET_SIZE_UINT16;
        frame.pixelAt(row, column) = _frameBuffer[i];
    }

    return frame;
}

void Lepton::performFFC() {
    _i2cConnection.performFFC();
}

void Lepton::openShutter() {
    _i2cConnection.openShutter();
}

void Lepton::closeShutter() {
    _i2cConnection.closeShutter();
}

void Lepton::resetVideoStream(unsigned int timeDelay) {
    _spiConnection.reset(timeDelay, _gpio);
}
