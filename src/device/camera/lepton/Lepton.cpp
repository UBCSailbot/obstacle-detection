#include "Lepton.h"

Lepton::Lepton() : Lepton(0, 1) {

}

Lepton::Lepton(int spiChipSelect, int i2cBusID) : _spiConnection(spiChipSelect),
                                                  _i2cConnection(i2cBusID)
{

}

Image16bit Lepton::captureFrame() {

    // Read data packets from lepton over SPI
    int resets = 0;
    for (int j = 0; j < PACKETS_PER_FRAME; j++) {
        // If it's a drop packet, reset j to 0, set to -1 so he'll be at 0 again loop
        ssize_t result = read(_spiConnection.getFileDescriptor(),
                              _result + sizeof(uint8_t) * PACKET_SIZE * j,
                              sizeof(uint8_t) * PACKET_SIZE);

        // TODO: check that read was successful
        int packetNumber = _result[j * PACKET_SIZE + 1];
        if (packetNumber != j) {
            j = -1;
            resets += 1;
            usleep(1000);
            if (resets == 750) {
                _spiConnection.reset(750000);
            }
        }
    }

    if (resets >= 30) {
        std::cout << "Done reading, resets: " << resets << std::endl;
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


