#include "SunImage.h"
#include "lepton/LeptonCameraDimensions.h"
#include <iostream>
#include <stack>

SunImage::SunImage(const Horizon &horizon, const cv::Mat &frame, unsigned int minSunPixelValue, float margin) : horizon(horizon), frame(frame), minSunPixelValue(minSunPixelValue), margin(margin) {
}

SunImage::~SunImage() {
}

void SunImage::findPosition() {
    //may implement blob detection for this method later
    for (int row = 0; row < frame.rows; row++) {
        for (int col = 0; col < frame.cols; col++) {
            unsigned int value = frame.at<uint16_t>(row, col);

            if (value >= minSunPixelValue && horizon.isPointAbove(static_cast<float>(row), static_cast<float>(col))) {
//                std::cout << "value is " << value << std::endl;
//                std::cout << "row is " << row << std::endl;
//                std::cout << "col is " << col << std::endl;

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

cv::Point2f SunImage::getPosition() const {
    if (sunLeft != std::numeric_limits<unsigned int>::max() && sunTop != std::numeric_limits<unsigned int>::max())
        return cv::Point2f((static_cast<float>(sunLeft)+static_cast<float>(sunRight))/2, (static_cast<float>(sunTop)+static_cast<float>(sunBottom))/2);
    return cv::Point2f();
}

void SunImage::findMeanVariance() {
    float offset = horizon.getStartPoint().y;
    float y = horizon.getEndPoint().y - horizon.getStartPoint().y;
    float x = VIEWPORT_WIDTH_PIX - 1;

//    std::cout << "offset is " << offset << std::endl;
//    std::cout << "x is " << x << std::endl;
//    std::cout << "y is " << y << std::endl;

    float magnitude = pow((pow(VIEWPORT_WIDTH_PIX - 1, 2) + pow(y, 2)), 0.5);
    x = x / magnitude;
    y = y / magnitude;

//    std::cout << "x is " << x << std::endl;
//    std::cout << "y is " << y << std::endl;

    unsigned int totalPix = 0;
    float totalSum = 0.0;
    std::stack<float> tempResults;

    //calculate dot product
    for (int yValue = 0; yValue < frame.rows; yValue++) {
        for (int xValue = 0; xValue < frame.cols; xValue++) {
            if (minSunPixelValue <= frame.at<uint16_t>(yValue, xValue)) {

//                std::cout << "row is " << row << std::endl;
//                std::cout << "col is " << col << std::endl;
//                std::cout << "offset is " << offset << std::endl;
//                std::cout << "x is " << x << std::endl;
//                std::cout << "y is " << y << std::endl;

                float tempValue = (yValue - offset) * y + xValue * x;
                totalSum += tempValue;
                tempResults.push(tempValue);
                totalPix++;
            }
        }
    }

    if (totalPix == 0) {
        mean = -1;
        variance = -1;
        return;
    }

    //calculate mean
    totalPix = tempResults.size();
    mean = totalSum / static_cast<float>(totalPix);
//    std::cout << "totalSum is " << totalSum << std::endl;
//    std::cout << "totalPix is " << totalPix << std::endl;

    //calculate variance
    while (!tempResults.empty()) {
        float tempResult = static_cast<float>(tempResults.top());
        tempResults.pop();
        variance += pow((tempResult - mean), 2);
    }
    
    variance = variance/static_cast<float>(totalPix);
//    std::cout << "variance is " << variance << std::endl;
}

float SunImage::getVariance() const {
    return variance;
}

float SunImage::getMean() const {
    return mean;
}

void SunImage::findColumn() {
    float offset = horizon.getStartPoint().y;
    float y = horizon.getEndPoint().y - horizon.getStartPoint().y;
    float x = VIEWPORT_WIDTH_PIX - 1;

//    std::cout << "offset is " << offset << std::endl;
//    std::cout << "x is " << x << std::endl;
//    std::cout << "y is " << y << std::endl;

    float magnitude = pow((pow(x, 2) + pow(y, 2)), 0.5);
    x = x / magnitude;
    y = y / magnitude;

//    std::cout << "x is " << x << std::endl;
//    std::cout << "y is " << y << std::endl;

    float leftLimit = std::numeric_limits<float>::max();
    float rightLimit = std::numeric_limits<float>::min();
    cv::Point2d leftPoint;
    cv::Point2d rightPoint;

    if (sunLeft != std::numeric_limits<unsigned int>::max() && sunTop != std::numeric_limits<unsigned int>::max()) {
        std::cout << "margin is " << margin << std::endl;

        cv::Point2f sunPosition = getPosition();
        leftPoint = cv::Point2d(sunPosition.x - static_cast<int>((sunRight - sunLeft) * margin), sunPosition.y);
        rightPoint = cv::Point2d(sunPosition.x + static_cast<int>((sunRight - sunLeft) * margin), sunPosition.y);
    }

    else {
        //calculate dot product
        for (int yValue = 0; yValue < frame.rows; yValue++) {
            for (int xValue = 0; xValue < frame.cols; xValue++) {
                if (minSunPixelValue <= frame.at<uint16_t>(yValue, xValue)
                    && !horizon.isPointAbove(static_cast<float>(xValue), static_cast<float>(yValue))) {

    //                std::cout << "row is " << row << std::endl;
    //                std::cout << "col is " << col << std::endl;
    //                std::cout << "offset is " << offset << std::endl;
    //                std::cout << "x is " << x << std::endl;
    //                std::cout << "y is " << y << std::endl;

                    float tempValue = (yValue - offset) * y + xValue * x;

                    if (tempValue < leftLimit) {
    //                    std::cout << "row is " << yValue << std::endl;
    //                    std::cout << "col is " << xValue << std::endl;
    //                    std::cout << "value is " << tempValue << std::endl;

                        leftLimit = tempValue;
                        leftPoint = cv::Point2d(xValue, yValue);
                    }
                    if (tempValue > rightLimit) {
    //                    std::cout << "row is " << row << std::endl;
    //                    std::cout << "col is " << col << std::endl;

                        rightLimit = tempValue;
                        rightPoint = cv::Point2d(xValue, yValue);
                    }
                }
            }
        }
    }

    if ((leftLimit != std::numeric_limits<float>::max() && rightLimit != std::numeric_limits<float>::min())
            || (sunLeft != std::numeric_limits<unsigned int>::max() && sunTop != std::numeric_limits<unsigned int>::max())) {
        if (y != 0.0) {
            std::cout << "Horizon is not flat" << std::endl;

            std::cout << "leftPoint.x is " << leftPoint.x << std::endl;
            std::cout << "leftPoint.y is " << leftPoint.y << std::endl;
            std::cout << "rightPoint.x is " << rightPoint.x << std::endl;
            std::cout << "rightPoint.y is " << rightPoint.y << std::endl;
            std::cout << "bottom is " << (VIEWPORT_HEIGHT_PIX - 1) << std::endl;

            leftDelimTop.y = 0.0;
            leftDelimTop.x = (leftPoint.y + leftPoint.x*(x/y))/(x/y);

            leftDelimBottom.y = VIEWPORT_HEIGHT_PIX - 1;
            leftDelimBottom.x = (leftPoint.y + leftPoint.x*(x/y) - (VIEWPORT_HEIGHT_PIX - 1))/(x/y);

            rightDelimTop.y = 0.0;
            rightDelimTop.x = (rightPoint.y + rightPoint.x*(x/y))/(x/y);

            rightDelimBottom.y = VIEWPORT_HEIGHT_PIX - 1;
            rightDelimBottom.x = (rightPoint.y + rightPoint.x*(x/y) - (VIEWPORT_HEIGHT_PIX - 1))/(x/y);
        }
        else {
            std::cout << "Horizon is flat" << std::endl;
            leftDelimTop = cv::Point2f(leftPoint.x, 0.0);
            leftDelimBottom = cv::Point2f(leftPoint.x, VIEWPORT_HEIGHT_PIX - 1);

            rightDelimTop = cv::Point2f(rightPoint.x, 0.0);
            rightDelimBottom = cv::Point2f(rightPoint.x, VIEWPORT_HEIGHT_PIX - 1);
        }
    }
}

Line SunImage::getLeftMargin() const {
    return Line(leftDelimTop, leftDelimBottom);
}

Line SunImage::getRightMargin() const {
    return Line(rightDelimTop, rightDelimBottom);
}