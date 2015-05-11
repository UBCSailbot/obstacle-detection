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

extern int spi_cs0_fd;
extern int spi_cs1_fd;
extern unsigned char spi_mode;
extern unsigned char spi_bitsPerWord;
extern unsigned int spi_speed;

int SpiOpenPort(int spi_device);
int SpiClosePort(int spi_device);

#endif //OBSTACLE_AVOIDANCE_LEPTONSPI_H
