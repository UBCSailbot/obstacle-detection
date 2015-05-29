//
// Created by paul on 11/05/15.
//

#include <features/HorizonTest.h>


TEST_F(HorizonTest, centeredHorizon) {
    Point2f pointOfInterest;
    Horizon h(0, 0);

    pointOfInterest = Point2f(69,20);
    testPointPosition(pointOfInterest, h, true);

    pointOfInterest = Point2f(30,31);
    testPointPosition(pointOfInterest, h, false);

    pointOfInterest = Point2f(79,30);
    testPointPosition(pointOfInterest, h, false);
}

TEST_F(HorizonTest, positiveRollOnly) {
    Point2f pointOfInterest;
    Horizon h = generateHorizonFromEndpoints(Point2f(0, 0), Point2f(80,60));

    pointOfInterest = Point2f(30,20);
    testPointPosition(pointOfInterest, h, true);

    pointOfInterest = Point2f(30,29);
    testPointPosition(pointOfInterest, h, false);

    pointOfInterest = Point2f(30,22.5);
    testPointPosition(pointOfInterest, h, false);
}

TEST_F(HorizonTest, NegativeRollOnly) {
    Point2f pointOfInterest;
    Horizon h = generateHorizonFromEndpoints(Point2f(0, 60), Point2f(80,0));

    pointOfInterest = Point2f(60,10);
    testPointPosition(pointOfInterest, h, true);

    pointOfInterest = Point2f(60,29);
    testPointPosition(pointOfInterest, h, false);

    pointOfInterest = Point2f(60,15);
    testPointPosition(pointOfInterest, h, false);
}

TEST_F(HorizonTest, positivePitchOnly) {
    Point2f pointOfInterest;
    Horizon h = generateHorizonFromEndpoints(Point2f(0, 40), Point2f(80, 40));

    pointOfInterest = cv::Point2f(25,20);
    testPointPosition(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(25,50);
    testPointPosition(pointOfInterest, h, false);

    pointOfInterest = cv::Point2f(25,40);
    testPointPosition(pointOfInterest, h, false);
}

TEST_F(HorizonTest, negativePitchOnly) {
    Point2f pointOfInterest;
    Horizon h = generateHorizonFromEndpoints(Point2f(0, 20), Point2f(80, 20));

    pointOfInterest = cv::Point2f(18,18);
    testPointPosition(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(47,29);
    testPointPosition(pointOfInterest, h, false);

    pointOfInterest = cv::Point2f(18,20);
    testPointPosition(pointOfInterest, h, false);
}

TEST_F(HorizonTest, positiveRollNegativePitch) {
    Point2f start(10,0);
    Point2f end(80,40);
    Horizon h = generateHorizonFromEndpoints(start, end);

    Point2f pointOfInterest;

    pointOfInterest = cv::Point2f(60,2);
    testPointPosition(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(5,30);
    testPointPosition(pointOfInterest, h, false);
}

TEST_F(HorizonTest, negativeRollPositivePitch) {
    Point2f start(40,60);
    Point2f end(80,40);
    Horizon h = generateHorizonFromEndpoints(start, end);

    Point2f pointOfInterest;

    pointOfInterest = cv::Point2f(30,59);
    testPointPosition(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(76,55);
    testPointPosition(pointOfInterest, h, false);
}

TEST_F(HorizonTest, positiveRollpositivePitch) {
    Point2f start(0,35);
    Point2f end(50,60);
    Horizon h = generateHorizonFromEndpoints(start, end);

    Point2f pointOfInterest;

    pointOfInterest = cv::Point2f(43, 40);
    testPointPosition(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(55, 40);
    testPointPosition(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(3,55);
    testPointPosition(pointOfInterest, h, false);

}

TEST_F(HorizonTest, generateHorizonFromEndpoints1) {
    // level
    testGenerateHorizonFromEndpoints(Point2f(0, 30), Point2f(80,30));
    // pure roll
    testGenerateHorizonFromEndpoints(Point2f(0, 0), Point2f(80,60));
    testGenerateHorizonFromEndpoints(Point2f(0, 60), Point2f(80,0));
    // pure pitch
    testGenerateHorizonFromEndpoints(Point2f(0, 20), Point2f(80,20));
    testGenerateHorizonFromEndpoints(Point2f(0, 45), Point2f(80,65));

    // roll, pitch:
    // pos neg
    testGenerateHorizonFromEndpoints(Point2f(0, 0), Point2f(80,40));
    // neg pos
//    testGenerateHorizonFromEndpoints(Point2f(40, 60), Point2f(80,40));

    // hard test cases?
//    testGenerateHorizonFromEndpoints(Point2f(0, 35), Point2f(50,60));
//    testGenerateHorizonFromEndpoints(Point2f(40, 60), Point2f(80,40));

}


/**
 * Assumes that the line is not vertical; if it were, this would cause a divide-by-zero error.
 */
double HorizonTest::calculatePitchAngleFromEndpoints(const Point2f &start, const Point2f &end) {
    double middleHeight = start.y +
            (end.y - start.y) / (end.x - start.x) *
                    ( (VIEWPORT_WIDTH_PIX / 2) - start.x) ;
    double delta = middleHeight - (double) VIEWPORT_HEIGHT_PIX/2;
    double fovVerticalRad = (double) VIEWPORT_FOV_DEGREES_VERTICAL / 180 * M_PI;
    return delta * fovVerticalRad / VIEWPORT_HEIGHT_PIX ;
}

Horizon HorizonTest::generateHorizonFromEndpoints(const Point2f &start, const Point2f &end) {

    double pitchRad = calculatePitchAngleFromEndpoints(start, end);
    double rollRad = calculateRollAngleFromEndpoints(start, end);
    Horizon h(rollRad, pitchRad);
    return h;
}

double HorizonTest::calculateRollAngleFromEndpoints(const Point2f &start, const Point2f &end) {
    double rollRad = atan2(end.y - start.y, end.x - start.x);
    return rollRad;
}

void HorizonTest::testPointPosition(const Point2f &pointOfInterest, const Horizon &h, const bool &isAbove)
{
    EXPECT_EQ(isAbove, h.isPointAbove(pointOfInterest));
}

void HorizonTest::testGenerateHorizonFromEndpoints(const Point2f &start, const Point2f &end) {
    Horizon h = generateHorizonFromEndpoints(start, end);
    EXPECT_EQ(start.x, h.getStart().x);
    EXPECT_EQ(start.y, h.getStart().y);
    EXPECT_EQ(end.x, h.getEnd().x);
    EXPECT_EQ(end.y, h.getEnd().y);
}
