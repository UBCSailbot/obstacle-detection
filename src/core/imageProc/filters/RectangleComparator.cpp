#include "RectangleComparator.h"

double RectangleComparator::kIntersectionOverUnionThreshold = 0.6; // TODO: find optimal threshold valued

std::vector<cv::Rect> RectangleComparator::getCommonRectangles(std::vector<cv::Rect> rects1,
                                                               std::vector<cv::Rect> rects2) {
    std::vector<cv::Rect> goodPairs;
    std::vector<cv::Rect>::iterator iter;

    for (cv::Rect rect1 : rects1) {
        for (iter = rects2.begin(); iter != rects2.end();) {
            cv::Rect intersection = *iter & rect1;
            cv::Rect union_ = *iter | rect1;
            if (union_.area() != 0) {
                double intersectionOverUnion = (double) intersection.area() / (double) union_.area();
                if (intersectionOverUnion > kIntersectionOverUnionThreshold) {
                    goodPairs.push_back(union_);
                    iter = rects2.erase(iter);
                    continue;
                }
            }
            ++iter;
        }
    }
    
    return goodPairs;
}
