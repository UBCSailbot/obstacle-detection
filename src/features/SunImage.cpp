#include "SunImage.h"
#include "lepton/LeptonCameraDimensions.h"
#include <iostream>
#include <stack>

SunImage::SunImage(const Horizon &horizon, const cv::Mat &frame, unsigned int minSunPixelValue, float margin)
        : _horizon(horizon), _frame(frame), _minSunPixelValue(minSunPixelValue), _margin(margin) {
}

SunImage::~SunImage() {
}

void SunImage::findPosition() {
    //may implement blob detection for this method later
    for (int row = 0; row < _frame.rows; row++) {
        for (int col = 0; col < _frame.cols; col++) {
            unsigned int value = _frame.at<uint16_t>(row, col);

            if (value >= _minSunPixelValue && _horizon.isPointAbove(static_cast<float>(row), static_cast<float>(col))) {
//                std::cout << "value is " << value << std::endl;
//                std::cout << "row is " << row << std::endl;
//                std::cout << "col is " << col << std::endl;

            	if (row > _sunBottom)
            		_sunBottom = row;
            	else if (row < _sunTop)
            		_sunTop = row;
            	if (col < _sunLeft)
            		_sunLeft = col;
            	else if (col > _sunRight)
            		_sunRight = col;
            }
        }
    }
}

cv::Point2f SunImage::getPosition() const {
    if (_sunLeft != std::numeric_limits<unsigned int>::max() && _sunTop != std::numeric_limits<unsigned int>::max())
        return cv::Point2f((static_cast<float>(_sunLeft)+static_cast<float>(_sunRight))/2, (static_cast<float>(_sunTop)+static_cast<float>(_sunBottom))/2);
    return cv::Point2f();
}

void SunImage::findMeanVariance() {
    float offset = _horizon.getStartPoint().y;
    float y = _horizon.getEndPoint().y - _horizon.getStartPoint().y;
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
    for (int yValue = 0; yValue < _frame.rows; yValue++) {
        for (int xValue = 0; xValue < _frame.cols; xValue++) {
            if (_minSunPixelValue <= _frame.at<uint16_t>(yValue, xValue)) {

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
        _mean = -1;
        _variance = -1;
        return;
    }

    //calculate mean
    totalPix = tempResults.size();
    _mean = totalSum / static_cast<float>(totalPix);
//    std::cout << "totalSum is " << totalSum << std::endl;
//    std::cout << "totalPix is " << totalPix << std::endl;

    //calculate variance
    while (!tempResults.empty()) {
        float tempResult = static_cast<float>(tempResults.top());
        tempResults.pop();
        _variance += pow((tempResult - _mean), 2);
    }
    
    _variance = _variance /static_cast<float>(totalPix);
//    std::cout << "variance is " << variance << std::endl;
}

float SunImage::getVariance() const {
    return _variance;
}

float SunImage::getMean() const {
    return _mean;
}

void SunImage::findColumn() {
    float offset = _horizon.getStartPoint().y;
    float y = _horizon.getEndPoint().y - _horizon.getStartPoint().y;
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

    if (_sunLeft != std::numeric_limits<unsigned int>::max() && _sunTop != std::numeric_limits<unsigned int>::max()) {
        std::cout << "margin is " << _margin << std::endl;

        cv::Point2f sunPosition = getPosition();
        leftPoint = cv::Point2d(sunPosition.x - static_cast<int>((_sunRight - _sunLeft) * _margin), sunPosition.y);
        rightPoint = cv::Point2d(sunPosition.x + static_cast<int>((_sunRight - _sunLeft) * _margin), sunPosition.y);
    }

    else {
        //calculate dot product
        for (int yValue = 0; yValue < _frame.rows; yValue++) {
            for (int xValue = 0; xValue < _frame.cols; xValue++) {
                if (_minSunPixelValue <= _frame.at<uint16_t>(yValue, xValue)
                    && !_horizon.isPointAbove(static_cast<float>(xValue), static_cast<float>(yValue))) {

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
            || (_sunLeft != std::numeric_limits<unsigned int>::max() && _sunTop != std::numeric_limits<unsigned int>::max())) {
        if (y != 0.0) {
            std::cout << "Horizon is not flat" << std::endl;

            std::cout << "leftPoint.x is " << leftPoint.x << std::endl;
            std::cout << "leftPoint.y is " << leftPoint.y << std::endl;
            std::cout << "rightPoint.x is " << rightPoint.x << std::endl;
            std::cout << "rightPoint.y is " << rightPoint.y << std::endl;
            std::cout << "bottom is " << (VIEWPORT_HEIGHT_PIX - 1) << std::endl;

            _leftDelimTop.y = 0.0;
            _leftDelimTop.x = (leftPoint.y + leftPoint.x*(x/y))/(x/y);

            _leftDelimBottom.y = VIEWPORT_HEIGHT_PIX - 1;
            _leftDelimBottom.x = (leftPoint.y + leftPoint.x*(x/y) - (VIEWPORT_HEIGHT_PIX - 1))/(x/y);

            _rightDelimTop.y = 0.0;
            _rightDelimTop.x = (rightPoint.y + rightPoint.x*(x/y))/(x/y);

            _rightDelimBottom.y = VIEWPORT_HEIGHT_PIX - 1;
            _rightDelimBottom.x = (rightPoint.y + rightPoint.x*(x/y) - (VIEWPORT_HEIGHT_PIX - 1))/(x/y);
        }
        else {
            std::cout << "Horizon is flat" << std::endl;
            _leftDelimTop = cv::Point2f(leftPoint.x, 0.0);
            _leftDelimBottom = cv::Point2f(leftPoint.x, VIEWPORT_HEIGHT_PIX - 1);

            _rightDelimTop = cv::Point2f(rightPoint.x, 0.0);
            _rightDelimBottom = cv::Point2f(rightPoint.x, VIEWPORT_HEIGHT_PIX - 1);
        }
    }
}

Line SunImage::getLeftMargin() const {
    return Line(_leftDelimTop, _leftDelimBottom);
}

Line SunImage::getRightMargin() const {
    return Line(_rightDelimTop, _rightDelimBottom);
}