//
// Created by paul on 10/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_LEPTONSPI_H
#define OBSTACLE_AVOIDANCE_LEPTONSPI_H


#include <string>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "exceptions/LeptonSPIOpenException.h"
#include "exceptions/LeptonSPICloseException.h"

class LeptonSPIConnection {

public:

    /**
     * @param: the ID of the SPI chip select pin that controls this connection
     *
     * @throws: LeptonSPIOpenException if any part of opening the SPI connection
     *  to this Lepton failed for any reason.
     */
    LeptonSPIConnection(int spiDeviceID);

    virtual ~LeptonSPIConnection();

    /**
     * @return the file descriptor used to read from the current SPI device
     */
    int getFileDescriptor() const;

    /**
     * Closes the SPI connection, sleeps for 750 milliseconds, then re-opens
     *  the connection.
     */
    void reset(unsigned int timeDelay);

private:
    bool _connected = false;

    int _spiDeviceID;
    int _spi_cs_fd;

    //SPI_MODE_0 (0,0)  CPOL=0 (Clock Idle low level), CPHA=0 (SDO transmit/change edge active to idle)
    //SPI_MODE_1 (0,1)  CPOL=0 (Clock Idle low level), CPHA=1 (SDO transmit/change edge idle to active)
    //SPI_MODE_2 (1,0)  CPOL=1 (Clock Idle high level), CPHA=0 (SDO transmit/change edge active to idle)
    //SPI_MODE_3 (1,1)  CPOL=1 (Clock Idle high level), CPHA=1 (SDO transmit/change edge idle to active)
    unsigned char _spi_mode = SPI_MODE_3;

    unsigned char _spi_bitsPerWord = 8;

    unsigned int _spi_speed = 8000000;

    void init();
    void close();

};


#endif //OBSTACLE_AVOIDANCE_LEPTONSPI_H
