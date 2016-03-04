#ifndef OBSTACLE_AVOIDANCE_LEPTON_H
#define OBSTACLE_AVOIDANCE_LEPTON_H


#include "LeptonSPIConnection.h"
#include "LeptonCameraSpecifications.h"
#include <opencv2/core/core.hpp>

#include <iostream>
#include <memory>
#include <chrono>
#include <ctime>
#include <mutex>
#include <thread>
#include <condition_variable>


#include <stdint.h>
#include <io/ImageStream.h>

#include "LeptonI2CConnection.h"

#include "types/Image16bit.h"


class Lepton {

  public:

    static const int FPS = 27;
    static const int REPEATING_FRAMES = 3;

    /**
     * Defaults to initializing a Lepton on i2c-1 and spi0.
     */
    Lepton();

    /**
     * @param: spiChipSelect - the number of the SPI chip select pin that
     *  enables or disables this Lepton
     * @param: i2cBusID - the ID of the i2c bus used to control this Lepton
     *
     * @throws: LeptonSPIOpenException if the connection to the SPI device
     *  fails to be opened.
     */
    Lepton(int spiChipSelect, int i2cBusID);

    /**
     * Returns the frame most recently recorded by the Lepton.
     */
    Image16bit captureFrame();

    /**
     * Perform Flat Field Correction, recalibrating the Lepton's sensor array
     *  based on the thermally level surface of the inside of the shutter.
     */
    void performFFC();

    void openShutter();

    void closeShutter();

  private:
    LeptonSPIConnection _spiConnection;
    LeptonI2CConnection _i2cConnection;

    static const int PACKET_SIZE = 164;
    static const int PACKET_SIZE_UINT16 = PACKET_SIZE/2;
    static const int PACKETS_PER_FRAME = 60;
    static const int FRAME_SIZE_UINT16 = PACKET_SIZE_UINT16 * PACKETS_PER_FRAME;

    char _device[15];
    uint8_t _result[PACKET_SIZE * PACKETS_PER_FRAME];

    uint16_t *_frameBuffer;
};

#endif //OBSTACLE_AVOIDANCE_LEPTON_H
