#include <io/cameradata/CameraDataProcessor.h>
#include "CameraDataProcessorTest.h"

TEST_F (CameraDataProcessorTest, filterHorizon) {
    cv::Point2f start(0, 30);
    cv::Point2f end(80, 30);
    Horizon horizon(start, end);

    cv::Rect isAboveHorizon(21, -11, 17, 33);
    cv::Rect isBelowHorizon(20, 60, 20, 3);
    std::vector<cv::Rect> rectangles;
    rectangles.push_back(isAboveHorizon);
    rectangles.push_back(isBelowHorizon);

    CameraDataProcessor::filterRectanglesByHorizon(&rectangles, horizon);

    EXPECT_EQ(rectangles.size(), 1);
    EXPECT_EQ(rectangles[0], isBelowHorizon);
}