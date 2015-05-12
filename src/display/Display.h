//
// Created by paul on 11/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_DISPLAY_H
#define OBSTACLE_AVOIDANCE_DISPLAY_H

#define DISPLAY_HEIGHT 240

#define DISPLAY_WIDTH 320

#include <memory>
#include <vector>
#include <stdint.h>

#include <rp/infra_config.h>
#include <rp/deps/libusbx_wrap/libusbx_wrap.h>
#include <rp/drivers/display/rpusbdisp/rpusbdisp.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace rp::util;
using namespace rp::deps::libusbx_wrap;
using namespace rp::drivers::display;

class Display {

public:
    Display();
    ~Display();

    void displayFrame(cv::Mat image);

private:
    void convertMatToUnsignedIntArray(cv::Mat image);
    uint16_t* frameBuffer;
    std::shared_ptr<RoboPeakUsbDisplayDevice> display;

};


#endif //OBSTACLE_AVOIDANCE_DISPLAY_H
