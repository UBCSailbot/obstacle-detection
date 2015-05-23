#include "SunImage.h"

SunImage::SunImage(Horizon horizon, cv::Mat frame, uint minSunPixelValue, int margin) {
}

SunImage::~SunImage() {

}

void findSun() {
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            int value = frame.at<uint16_t>(row, col);

            if (value >= minSunPixelValue) {
            	if (row > sunBottom)
            		sunBottom = row;
            	else if (row < sunTop)
            		sunTop = row;
            	if (col < sunLeft)
            		sunLeft = col;
            	else if (col > sunRight)
            		sunRight = col;
            }
        }
    }


}

// uint sunRadius() {
// }