//
// Created by paul on 10/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_LEPTON_H
#define OBSTACLE_AVOIDANCE_LEPTON_H


#include "LeptonSPI.h"

#include <opencv2/core/core.hpp>

#include <iostream>
#include <ctime>
#include <stdint.h>

#include "LeptonI2C.h"

#include "../imageTypes/Image16bit.h"

#define PACKET_SIZE 164
#define PACKET_SIZE_UINT16 (PACKET_SIZE/2)
#define PACKETS_PER_FRAME 60
#define FRAME_SIZE_UINT16 (PACKET_SIZE_UINT16*PACKETS_PER_FRAME)

#define VIEWPORT_HEIGHT_PIX 60
#define VIEWPORT_WIDTH_PIX 80
#define VIEWPORT_FOV_DEGREES_VERTICAL 37
#define VIEWPORT_FOV_DEGREES_HORIZONTAL 51

#define LEPTON_FPS 27
#define FFC_FREQ_SEC 30

static const char *device = "/dev/spidev0.0";
static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 16000000;

class Lepton {
public:
    Lepton();
    ~Lepton();

    void captureFrame(Image16bit &frame);
    void performFFC();

private:

    uint8_t result[PACKET_SIZE*PACKETS_PER_FRAME];
    uint16_t *frameBuffer;

};

static void pabort(const char *s)
{
    perror(s);
    abort();
}

#endif //OBSTACLE_AVOIDANCE_LEPTON_H
