//
// Created by paul on 11/05/15.
//

#include "RoboPeakUSBDisplay.h"

static void onStatusUpdated(const rpusbdisp_status_normal_packet_t& status) {
    printf("Status: %02X, Touch: %02X, X: %d, Y: %d\n", status.display_status, status.touch_status, status.touch_x, status.touch_y);
}

RoboPeakUSBDisplay::RoboPeakUSBDisplay() {
    frameBuffer = (uint16_t*)malloc(DISPLAY_WIDTH* DISPLAY_HEIGHT*2);
    uint16_t* p = frameBuffer;

    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++, p++) {
            *p = 0x0000;
        }
    }

    display = RoboPeakUsbDisplayDevice::openFirstDevice();

    if (!display) {
        fprintf(stderr, "No display found\n");
    }
    else {
        printf("Display with S/N %s is chosen\n", display->getDevice()->getSerialNumber().c_str());

        display->setStatusUpdatedCallback(onStatusUpdated);
        display->enable();
    }
}

RoboPeakUSBDisplay::~RoboPeakUSBDisplay() {
    free(frameBuffer);
}

void RoboPeakUSBDisplay::displayFrame(cv::Mat image) {
    convertMatToUnsignedIntArray(image);
    display->bitblt(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, RoboPeakUsbDisplayBitOperationCopy, frameBuffer);

}

void RoboPeakUSBDisplay::convertMatToUnsignedIntArray(cv::Mat image) {
    cv::Mat displayed(DISPLAY_HEIGHT, DISPLAY_WIDTH, CV_16U);
    cv::resize(image, displayed, displayed.size(), 0, 0, cv::INTER_NEAREST);
    cv::cvtColor(displayed, displayed, cv::COLOR_GRAY2BGR565);

    uint16_t* p = frameBuffer;

    for(int y =0; y < DISPLAY_HEIGHT; y++) {
        for (int x =0; x < DISPLAY_WIDTH; x++, p++) {
            uint16_t value = displayed.at<uint16_t>(y, x);
            *p = value;
        }
    }
}

