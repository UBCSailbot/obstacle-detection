#include "SunImage.h"

SunImage::SunImage(const Horizon &horizon, const cv::Mat &frame, unsigned int minSunPixelValue,
                   unsigned int minGlintPixelValue, float glintColumnMargin) :
    _horizon(horizon),
    _frame(frame),
    _minSunPixelValue(minSunPixelValue),
    _minGlintPixelValue(minGlintPixelValue),
    _margin(glintColumnMargin),
    HorizonImage(frame, horizon) {
    findSunPosition();
    findGlintColumn();
}

SunImage::~SunImage() {
    delete _leftMargin;
    delete _rightMargin;
}

void SunImage::findSunPosition() {
    float sunLeft = std::numeric_limits < unsigned
    int > ::max();
    float sunRight = 0;
    float sunTop = std::numeric_limits < unsigned
    int > ::max();
    float sunBottom = 0;

    for (float row = 0.0; row < _frame.rows; row++) {
        for (float col = 0.0; col < _frame.cols; col++) {
            unsigned int value = _frame.at<uint16_t>(row, col);

            if (value >= _minSunPixelValue && _horizon.isPointAbove(row, col)) {
                if (row > sunBottom)
                    sunBottom = row;
                if (row < sunTop)
                    sunTop = row;
                if (col < sunLeft)
                    sunLeft = col;
                if (col > sunRight)
                    sunRight = col;
            }
        }
    }

    if (sunLeft != std::numeric_limits < unsigned
    int > ::max())
    _sunPosition = Rect2f(cv::Point2f(sunLeft, sunTop), cv::Point2f(sunRight, sunBottom));
}

bool SunImage::containsSun() const {
    return _sunPosition != Rect2f(-1.0f, -1.0f, -1.0f, -1.0f);
}

Rect2f SunImage::getSunPosition() const {
    return _sunPosition;
}

void SunImage::findGlintColumn() {
    float offset = _horizon.getStartPoint().y;
    float y = _horizon.getEndPoint().y - _horizon.getStartPoint().y;
    float x = LeptonCameraSpecifications.pixelWidth - 1;

    float magnitude = pow((pow(x, 2) + pow(y, 2)), 0.5);
    x = x / magnitude;
    y = y / magnitude;

    float leftLimit = std::numeric_limits<float>::max();
    float rightLimit = std::numeric_limits<float>::min();
    cv::Point2f leftPoint;
    cv::Point2f rightPoint;

    if (_sunPosition.x != -1.0) {
        leftPoint = cv::Point2f(_sunPosition.x + _sunPosition.width + _sunPosition.width * _margin, _sunPosition.y);
        rightPoint = cv::Point2f(_sunPosition.x - _sunPosition.width * _margin, _sunPosition.y);
    } else {
        //calculate dot product
        for (float yValue = 0.0; yValue < _frame.rows; yValue++) {
            for (float xValue = 0.0; xValue < _frame.cols; xValue++) {
                if (_frame.at<uint16_t>(yValue, xValue) >= _minGlintPixelValue
                    && !_horizon.isPointAbove(xValue, yValue)) {

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
        || _sunPosition.x != -1.0) {
        if (y != 0.0) {
            _leftMargin = new Line(cv::Point2f((leftPoint.y + leftPoint.x * (x / y)) / (x / y),
                                               0.0),
                                   cv::Point2f(
                                       (leftPoint.y + leftPoint.x * (x / y) - (LeptonCameraSpecifications.pixelHeight - 1)) / (x / y),
                                       static_cast<float>(LeptonCameraSpecifications.pixelHeight - 1)));

            _rightMargin = new Line(cv::Point2f((rightPoint.y + rightPoint.x * (x / y)) / (x / y),
                                                0.0),
                                    cv::Point2f(
                                        (rightPoint.y + rightPoint.x * (x / y) - (LeptonCameraSpecifications.pixelHeight - 1)) / (x / y),
                                        static_cast<float>(LeptonCameraSpecifications.pixelHeight - 1)));
        } else {
            _leftMargin = new Line(cv::Point2f(leftPoint.x, 0.0),
                                   cv::Point2f(leftPoint.x, LeptonCameraSpecifications.pixelHeight - 1));

            _rightMargin = new Line(cv::Point2f(rightPoint.x, 0.0),
                                    cv::Point2f(rightPoint.x, LeptonCameraSpecifications.pixelHeight - 1));
        }
    }
}

Line *SunImage::getLeftGlintMargin() const {
    return _leftMargin;
}

Line *SunImage::getRightGlintMargin() const {
    return _rightMargin;
}

bool SunImage::containsGlint() const {
    //TODO: Implement this function.
    return false;
}

void SunImage::findMeanVariance() {
    float offset = _horizon.getStartPoint().y;
    float y = _horizon.getEndPoint().y - _horizon.getStartPoint().y;
    float x = LeptonCameraSpecifications.pixelWidth - 1;

    float magnitude = pow((pow(LeptonCameraSpecifications.pixelWidth - 1, 2) + pow(y, 2)), 0.5);
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
    totalPix = tempResults.size();
    _mean = totalSum / static_cast<float>(totalPix);

    //calculate variance
    while (!tempResults.empty()) {
        float tempResult = static_cast<float>(tempResults.top());
        tempResults.pop();
        _variance += pow((tempResult - _mean), 2);
    }

    _variance = _variance / static_cast<float>(totalPix);
}

float SunImage::getVariance() const {
    return _variance;
}

float SunImage::getMean() const {
    return _mean;
}

cv::Mat SunImage::render() const {
    cv::Mat sunImage(_frame.rows, _frame.cols, CV_8UC3);
    cv::cvtColor(_frame, sunImage, cv::COLOR_GRAY2BGR);

    rectangle(sunImage, getSunPosition(), cv::Scalar(0, 0, 0xFFFF));
    line(sunImage, _horizon.getStartPoint(), _horizon.getEndPoint(), cv::Scalar(0xFFFF, 0, 0));
    line(sunImage,
         getLeftGlintMargin()->getStartPoint(),
         getLeftGlintMargin()->getEndPoint(),
         cv::Scalar(0, 0xFFFF, 0));
    line(sunImage,
         getRightGlintMargin()->getStartPoint(),
         getRightGlintMargin()->getEndPoint(),
         cv::Scalar(0, 0xFFFF, 0));

    return sunImage;
}