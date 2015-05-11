//
// Created by paul on 10/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_LEPTON_H
#define OBSTACLE_AVOIDANCE_LEPTON_H


#include "LeptonSPI.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <ctime>
#include <stdint.h>

#define PACKET_SIZE 164
#define PACKET_SIZE_UINT16 (PACKET_SIZE/2)
#define PACKETS_PER_FRAME 60
#define FRAME_SIZE_UINT16 (PACKET_SIZE_UINT16*PACKETS_PER_FRAME)

class Lepton {
public:
    Lepton();
    ~Lepton();

    void GetFrame(cv::Mat &frame, cv::Mat &eightbit);

private:

    uint8_t result[PACKET_SIZE*PACKETS_PER_FRAME];
    uint16_t *frameBuffer;

};


#endif //OBSTACLE_AVOIDANCE_LEPTON_H
