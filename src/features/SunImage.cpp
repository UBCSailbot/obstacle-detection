#include "SunImage.h"

SunImage::SunImage(const Horizon &horizon, const cv::Mat &frame,
                   unsigned int minSunPixelValue, float margin) :
            _horizon(horizon), _frame(frame),
            _minSunPixelValue(minSunPixelValue), _margin(margin)
{
    calcSunPosition();
    calcGlintColumn();
}

SunImage::~SunImage() {
}

cv::Point2f SunImage::getSunPosition() const {
    if (isSunInFrame())
        return cv::Point2f( (static_cast<float>(_sunLeft) + static_cast<float>(_sunRight)) / 2,
                            (static_cast<float>(_sunTop) + static_cast<float>(_sunBottom)) / 2 );
    return cv::Point2f();
}

bool SunImage::isSunInFrame() const {
    return _sunLeft != std::numeric_limits<unsigned int>::max() &&
            _sunTop != std::numeric_limits<unsigned int>::max();
}

Line SunImage::getGlintLeftMargin() const {
    return Line(_leftDelimTop, _leftDelimBottom);
}

Line SunImage::getGlintRightMargin() const {
    return Line(_rightDelimTop, _rightDelimBottom);
}

float SunImage::getMean() {
    if (_mean == 0.0) {
        calcMeanVariance();
    }
    return _mean;
}

float SunImage::getVariance() {
    if (_mean == 0.0) {
        calcMeanVariance();
    }
    return _variance;
}

void SunImage::calcSunPosition() {
    for (unsigned int row = 0; row < _frame.rows; row++) {
        for (unsigned int col = 0; col < _frame.cols; col++) {
            unsigned int value = _frame.at<uint16_t>(row, col);

            if (value >= _minSunPixelValue &&
                    _horizon.isPointAbove(static_cast<float>(row), static_cast<float>(col))) {
            	if (row > _sunBottom)
            		_sunBottom = row;
                if (row < _sunTop)
            		_sunTop = row;
            	if (col < _sunLeft)
            		_sunLeft = col;
            	if (col > _sunRight)
            		_sunRight = col;
            }
        }
    }
}

void SunImage::calcGlintColumn() {
    float offset = _horizon.getStartPoint().y;
    float y = _horizon.getEndPoint().y - _horizon.getStartPoint().y;
    float x = VIEWPORT_WIDTH_PIX - 1;

    float magnitude = (float) pow((pow(x, 2) + pow(y, 2)), 0.5);
    x = x / magnitude;
    y = y / magnitude;

    float leftLimit = std::numeric_limits<float>::max();
    float rightLimit = std::numeric_limits<float>::min();
    cv::Point2d leftPoint;
    cv::Point2d rightPoint;

    if (_sunLeft != std::numeric_limits<unsigned int>::max() && _sunTop != std::numeric_limits<unsigned int>::max()) {

        cv::Point2f sunPosition = getSunPosition();
        leftPoint = cv::Point2d(sunPosition.x - static_cast<int>((_sunRight - _sunLeft) * _margin), sunPosition.y);
        rightPoint = cv::Point2d(sunPosition.x + static_cast<int>((_sunRight - _sunLeft) * _margin), sunPosition.y);
    }

    else {
        //calculate dot product
        for (int yValue = 0; yValue < _frame.rows; yValue++) {
            for (int xValue = 0; xValue < _frame.cols; xValue++) {
                if (_minSunPixelValue <= _frame.at<uint16_t>(yValue, xValue)
                    && !_horizon.isPointAbove(static_cast<float>(xValue), static_cast<float>(yValue))) {

                    float tempValue = (yValue - offset) * y + xValue * x;

                    if (tempValue < leftLimit) {
                        leftLimit = tempValue;
                        leftPoint = cv::Point2d(xValue, yValue);
                    }
                    if (tempValue > rightLimit) {
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
            _leftDelimTop = cv::Point2f(leftPoint.x, 0.0);
            _leftDelimBottom = cv::Point2f(leftPoint.x, VIEWPORT_HEIGHT_PIX - 1);

            _rightDelimTop = cv::Point2f(rightPoint.x, 0.0);
            _rightDelimBottom = cv::Point2f(rightPoint.x, VIEWPORT_HEIGHT_PIX - 1);
        }
    }
}

void SunImage::calcMeanVariance() {
    float offset = _horizon.getStartPoint().y;
    float y = _horizon.getEndPoint().y - _horizon.getStartPoint().y;
    float x = VIEWPORT_WIDTH_PIX - 1;

    float magnitude = (float) pow((pow(VIEWPORT_WIDTH_PIX - 1, 2) + pow(y, 2)), 0.5);
    x = x / magnitude;
    y = y / magnitude;

    unsigned int totalPix = 0;
    float totalSum = 0.0;
    std::stack<float> tempResults;

    //calculate dot product
    for (int yValue = 0; yValue < _frame.rows; yValue++) {
        for (int xValue = 0; xValue < _frame.cols; xValue++) {
            if (_minSunPixelValue <= _frame.at<uint16_t>(yValue, xValue)) {

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
    totalPix = (unsigned int) tempResults.size();
    _mean = totalSum / static_cast<float>(totalPix);

    //calculate variance
    while (!tempResults.empty()) {
        float tempResult = static_cast<float>(tempResults.top());
        tempResults.pop();
        _variance += pow((tempResult - _mean), 2);
    }
    
    _variance = _variance /static_cast<float>(totalPix);
}