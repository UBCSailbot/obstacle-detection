//
// Created by paul on 11/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_ROBOPEAKUSBDISPLAY_H
#define OBSTACLE_AVOIDANCE_ROBOPEAKUSBDISPLAY_H

#include <memory>
#include <vector>
#include <stdint.h>

#include <rp/infra_config.h>
#include <rp/deps/libusbx_wrap/libusbx_wrap.h>
#include <rp/drivers/display/rpusbdisp/rpusbdisp.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Display.h"

using namespace rp::util;
using namespace rp::deps::libusbx_wrap;
using namespace rp::drivers::display;

class RoboPeakUSBDisplay : public Display {

public:
    RoboPeakUSBDisplay();
    ~RoboPeakUSBDisplay();
    void displayFrame(Image8bit image);

    const static int DISPLAY_HEIGHT = 240;
    const static int DISPLAY_WIDTH = 320;

private:
    void convertMatToUnsignedIntArray(Image8bit image);
    uint16_t* frameBuffer;
    std::shared_ptr<RoboPeakUsbDisplayDevice> display;


};


#endif //OBSTACLE_AVOIDANCE_DISPLAY_H
