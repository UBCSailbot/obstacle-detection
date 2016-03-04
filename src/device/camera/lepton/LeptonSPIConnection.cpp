//
// Created by paul on 10/05/15.
//

#include "LeptonSPIConnection.h"


LeptonSPIConnection::LeptonSPIConnection(int spiDeviceID) :
        _spiDeviceID(spiDeviceID)
{
    init();
}

LeptonSPIConnection::~LeptonSPIConnection() {
    // TODO: Closing a file handle in a destructor like this, and not checking
    //  the return status, is not kosher, but it's the best we can do for now.
    this->close();
}

int LeptonSPIConnection::getFileDescriptor() const {
    return _spi_cs_fd;
}

void LeptonSPIConnection::reset(unsigned int timeDelay) {
    // TODO: Verify that this is the best method of resetting.
    this->close();
    usleep(timeDelay);
    init();
}

void LeptonSPIConnection::close() {
    _connected = false;
    ::close(_spi_cs_fd);
}


void LeptonSPIConnection::init() {
    // Never attempt to open the connection if it is already open.
    if (_connected) {
        return;
    }

    std::string spiAddress = "/dev/spidev0." + _spiDeviceID;
    _spi_cs_fd = ::open(spiAddress.c_str(), O_RDWR);

    if (_spi_cs_fd < 0) {
        throw LeptonSPIOpenException("Error - Could not open SPI device");
    }

    int status_value;

    status_value = ioctl(_spi_cs_fd, SPI_IOC_WR_MODE, &_spi_mode);
    if (status_value < 0) {
        throw LeptonSPIOpenException("Could not set SPIMode (WR)...ioctl fail");
    }

    status_value = ioctl(_spi_cs_fd, SPI_IOC_RD_MODE, &_spi_mode);
    if (status_value < 0) {
        throw LeptonSPIOpenException("Could not set SPIMode (RD)...ioctl fail");
    }
    status_value = ioctl(_spi_cs_fd, SPI_IOC_WR_BITS_PER_WORD, &_spi_bitsPerWord);
    if (status_value < 0) {
        throw LeptonSPIOpenException("Could not set SPI bitsPerWord (WR)...ioctl fail");
    }

    status_value = ioctl(_spi_cs_fd, SPI_IOC_RD_BITS_PER_WORD, &_spi_bitsPerWord);
    if (status_value < 0) {
        throw LeptonSPIOpenException("Could not set SPI bitsPerWord(RD)...ioctl fail");
    }

    status_value = ioctl(_spi_cs_fd, SPI_IOC_WR_MAX_SPEED_HZ, &_spi_speed);
    if (status_value < 0) {
        throw LeptonSPIOpenException("Could not set SPI speed (WR)...ioctl fail");
    }

    status_value = ioctl(_spi_cs_fd, SPI_IOC_RD_MAX_SPEED_HZ, &_spi_speed);
    if (status_value < 0) {
        throw LeptonSPIOpenException("Could not set SPI speed (RD)...ioctl fail");
    }

    _connected = true;
}


