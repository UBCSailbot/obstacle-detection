//
// Created by paul on 20/01/16.
//

#ifndef OBSTACLE_DETECTION_REDUNDANTLEPTON_H
#define OBSTACLE_DETECTION_REDUNDANTLEPTON_H


#include <types/Image16bit.h>

class RedundantLepton {

public:
    RedundantLepton(int spiChipSelect);
    ~RedundantLepton();

    void getFrame(Image16bit &frame);

private:
    char _device[15];
    uint8_t _result[PACKET_SIZE*PACKETS_PER_FRAME];
    uint16_t *_frameBuffer;
};


#endif //OBSTACLE_DETECTION_REDUNDANTLEPTON_H
