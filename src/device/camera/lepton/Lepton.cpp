#include "Lepton.h"

Lepton::Lepton() : Lepton(0) {

}

Lepton::Lepton(int spiChipSelect) : _spiID(spiChipSelect) {
    // TODO: Error handling in case opening SPI port fails
    SpiOpenPort(_spiID);

    int ret = 0;
    int fd;

    sprintf(_device, "/dev/spidev0.%d", spiChipSelect);

    if (spiChipSelect) {
        _spiFileDescriptor = spi_cs1_fd;
    } else {
        _spiFileDescriptor = spi_cs0_fd;
    }

    fd = open(_device, O_RDWR);
    if (fd < 0) {
        pabort("can't open device");
    }

    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1) {
        pabort("can't set spi mode");
    }

    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if (ret == -1) {
        pabort("can't get spi mode");
    }

    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1) {
        pabort("can't set bits per word");
    }

    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1) {
        pabort("can't get bits per word");
    }

    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1) {
        pabort("can't set max speed hz");
    }

    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1) {
        pabort("can't get max speed hz");
    }

}

Lepton::~Lepton() {
    SpiClosePort(_spiID);
}

Image16bit Lepton::captureFrame() {

    // Read data packets from lepton over SPI
    int resets = 0;
    for (int j = 0; j < PACKETS_PER_FRAME; j++) {
        // If it's a drop packet, reset j to 0, set to -1 so he'll be at 0 again loop
        ssize_t result = read(_spiFileDescriptor,
                              _result + sizeof(uint8_t) * PACKET_SIZE * j,
                              sizeof(uint8_t) * PACKET_SIZE);

        // TODO: check that read was successful
        int packetNumber = _result[j * PACKET_SIZE + 1];
        if (packetNumber != j) {
            j = -1;
            resets += 1;
            usleep(1000);
            if (resets == 750) {
                SpiClosePort(_spiID);
                usleep(750000);
                SpiOpenPort(_spiID);
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
    lepton_perform_ffc();
}
