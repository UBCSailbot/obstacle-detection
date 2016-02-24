//
// Created by paul on 11/05/15.
//

#include "RoboPeakUSBDisplay.h"

static void onStatusUpdated(const rpusbdisp_status_normal_packet_t &status) {
    printf("Status: %02X, Touch: %02X, X: %d, Y: %d\n",
           status.display_status,
           status.touch_status,
           status.touch_x,
           status.touch_y);
}

RoboPeakUSBDisplay::RoboPeakUSBDisplay() {
    _frameBuffer = (uint16_t *) malloc(DISPLAY_WIDTH * DISPLAY_HEIGHT * 2);
    uint16_t *p = _frameBuffer;

    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++, p++) {
            *p = 0x0000;
        }
    }

    _display = RoboPeakUsbDisplayDevice::openFirstDevice();

    if (!_display) {
        fprintf(stderr, "No USB display found!\n");
        _connected = false;
    }
    else {
        printf("Display with S/N %s is chosen\n", _display->getDevice()->getSerialNumber().c_str());

        _display->setStatusUpdatedCallback(onStatusUpdated);
        _display->enable();
        _connected = true;
    }
}

RoboPeakUSBDisplay::~RoboPeakUSBDisplay() {
    free(_frameBuffer);
}

void RoboPeakUSBDisplay::display8bitGray(const Image8bit &image) {
    cv::Mat displayed(DISPLAY_HEIGHT, DISPLAY_WIDTH, CV_16U);
    resize(image, displayed, displayed.size(), 0, 0, cv::INTER_NEAREST);
    cvtColor(displayed, displayed, cv::COLOR_GRAY2BGR565);

    putMatIntoFrameBuffer(displayed);
    _display->bitblt(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, RoboPeakUsbDisplayBitOperationCopy, _frameBuffer);
}

void RoboPeakUSBDisplay::displayColored(const cv::Mat &image) {
    cv::Mat displayed(DISPLAY_HEIGHT, DISPLAY_WIDTH, CV_16U);
    cv::Mat bgr565(image.rows, image.cols, CV_16U);
    cv::cvtColor(image, bgr565, CV_BGR2BGR565);

    cv::resize(bgr565, displayed, displayed.size(), 0, 0, cv::INTER_NEAREST);
    putMatIntoFrameBuffer(displayed);
    _display->bitblt(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, RoboPeakUsbDisplayBitOperationCopy, _frameBuffer);
}


void RoboPeakUSBDisplay::putMatIntoFrameBuffer(const cv::Mat &displayed) {
    uint16_t *p = _frameBuffer;
    for (int y = 0; y < displayed.rows; y++) {
        for (int x = 0; x < displayed.cols; x++, p++) {
            uint16_t value = displayed.at<uint16_t>(y, x);
            *p = value;
        }
        p = _frameBuffer + (y * RoboPeakUSBDisplay::DISPLAY_WIDTH);
    }

    _frameCounter++;

//    uint16_t* p = _frameBuffer;
//    for(int y = 0; y < displayed.rows; y++) {
//        p += (y + _frameCounter) % 2;
//        for (int x = (y + _frameCounter) % 2; x < displayed.cols; x += 2, p += 2) {
//            uint16_t value = displayed.at<uint16_t>(y, x);
//            *p = value;
//        }
//        p = _frameBuffer + (y * RoboPeakUSBDisplay::DISPLAY_WIDTH);
//    }
//
//    _frameCounter ++;
}
