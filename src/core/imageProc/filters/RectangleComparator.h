#ifndef OBSTACLE_DETECTION_RECTANGLECOMPARATOR_H
#define OBSTACLE_DETECTION_RECTANGLECOMPARATOR_H

#include <opencv2/core/core.hpp>

class RectangleComparator {
public:

    /*
     * Takes two vectors of detected objects and finds common objects between the two filtering out false positives
     * The order does not matter
     */
    static std::vector<cv::Rect> getCommonRectangles(std::vector<cv::Rect> rects1, std::vector<cv::Rect> rects2);

private:
    static double kIntersectionOverUnionThreshold;
};


#endif //OBSTACLE_DETECTION_RECTANGLECOMPARATOR_H
