//
// Created by paul on 10/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_LEPTON_H
#define OBSTACLE_AVOIDANCE_LEPTON_H


#include "LeptonSPI.h"
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

#include "LeptonI2C.h"

#include "types/Image16bit.h"

#define PACKET_SIZE 164
#define PACKET_SIZE_UINT16 (PACKET_SIZE/2)
#define PACKETS_PER_FRAME 60
#define FRAME_SIZE_UINT16 (PACKET_SIZE_UINT16*PACKETS_PER_FRAME)

#define LEPTON_FPS 27
#define LEPTON_IDENTICAL_FRAMES 3
#define FFC_FREQ_SEC 30

static const char *device = "/dev/spidev0.0";
static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 16000000;

class Lepton {
public:
    Lepton();
    Lepton(int spi_cs);
    virtual ~Lepton();

    /**
     * Delegates memory allocated by this class to a new Image16bit object,
     *  and sends it off via unique_ptr to communicate to the receiver
     *  that they should take care of memory from there on out.
     */


    void captureFrame(uint16_t *frame);

    /**
     * Perform Flat Field Correction, recalibrating the Lepton's sensor array
     *  based on the thermally level surface of the inside of the shutter.
     */
    void performFFC();

private:
    uint8_t _result[PACKET_SIZE*PACKETS_PER_FRAME];

    uint16_t *_frameBuffer;
};

static void pabort(const char *s)
{
    perror(s);
    abort();
}

#endif //OBSTACLE_AVOIDANCE_LEPTON_H
