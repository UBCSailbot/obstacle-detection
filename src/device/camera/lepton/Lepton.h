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
#include "gpio/GPIO.h"

#include "types/Image16bit.h"


class Lepton {

public:

    /*
     * Destructor needed to unexport GPIO pin.
     */
    ~Lepton();

    /**
     * This allows the LeptonRegistry class to call the Lepton's private constructor.
     */
    friend class LeptonRegistry;

    /**
     * Number of frames per second recorded by the Lepton.
     */
    static const int FPS = 27;

    /**
     * Number of frames in a row that are identical to each other.
     */
    static const int REPEATING_FRAMES = 3;

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

    void resetVideoStream(unsigned int timeDelay);

    /**
     * Delete the copy constructor to make sure it doesn't inadvertently get used.
     */
    Lepton(Lepton const &) = delete;

    /**
     * Delete the assignment operator to make sure it doesn't inadvertently get used.
     */
    void operator=(Lepton const &) = delete;

private:

    /**
     * This constructor is private so that it can only be called by LeptonRegistry,
     *  which is a friend class of Lepton. This is to avoid inadvertently
     *  creating multiple instances of the same Lepton connection, as each
     *  Lepton object must have sole ownership of the resources it acquires
     *  in terms of SPI and I2C connections.
     *
     * @param: spiChipSelect - the number of the SPI chip select pin that
     *  enables or disables this Lepton
     * @param: i2cBusID - the ID of the i2c bus used to control this Lepton
     * @param: CAPTURE_FRAME_TIMEOUT - number of seconds before captureFrame() 
     *  will throw an exception. This will occur if the SPI connection is broken.
     *
     * @throws: LeptonException if the connection to the SPI device
     *  fails to be opened.
     */
    Lepton(int spiChipSelect, int i2cBusID, const int CAPTURE_FRAME_TIMEOUT = 8);

    LeptonSPIConnection _spiConnection;
    LeptonI2CConnection _i2cConnection;
    GPIO *_gpio;
    const int _CAPTURE_FRAME_TIMEOUT;

    static const int PACKET_SIZE = 164;
    static const int PACKET_SIZE_UINT16 = PACKET_SIZE / 2;
    static const int PACKETS_PER_FRAME = 60;
    static const int FRAME_SIZE_UINT16 = PACKET_SIZE_UINT16 * PACKETS_PER_FRAME;

    char _device[15];
    uint8_t _result[PACKET_SIZE * PACKETS_PER_FRAME];

    uint16_t *_frameBuffer;

};

#endif //OBSTACLE_AVOIDANCE_LEPTON_H
