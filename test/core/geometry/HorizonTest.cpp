//
// Created by paul on 11/05/15.
//

#include "HorizonTest.h"


TEST_F(HorizonTest, centeredHorizon) {
    cv::Point2f pointOfInterest;
    Horizon h = hf.makeNeutralHorizon();

    pointOfInterest = cv::Point2f(69,20);
    testIsPointAbove(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(30,31);
    testIsPointAbove(pointOfInterest, h, false);

    pointOfInterest = cv::Point2f(79,30);
    testIsPointAbove(pointOfInterest, h, false);
}

TEST_F(HorizonTest, positiveRollOnly) {
    cv::Point2f pointOfInterest;
    Horizon h(cv::Point2f(0, 0), cv::Point2f(80,60));

    pointOfInterest = cv::Point2f(30,20);
    testIsPointAbove(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(30,29);
    testIsPointAbove(pointOfInterest, h, false);

    pointOfInterest = cv::Point2f(30,22.5);
    testIsPointAbove(pointOfInterest, h, false);
}

TEST_F(HorizonTest, NegativeRollOnly) {
    cv::Point2f pointOfInterest;
    Horizon h(cv::Point2f(0, 60), cv::Point2f(80,0));

    pointOfInterest = cv::Point2f(60,10);
    testIsPointAbove(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(60,29);
    testIsPointAbove(pointOfInterest, h, false);

    pointOfInterest = cv::Point2f(60,15);
    testIsPointAbove(pointOfInterest, h, false);
}

TEST_F(HorizonTest, positivePitchOnly) {
    cv::Point2f pointOfInterest;
    Horizon h(cv::Point2f(0, 40), cv::Point2f(80, 40));

    pointOfInterest = cv::Point2f(25,20);
    testIsPointAbove(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(25,50);
    testIsPointAbove(pointOfInterest, h, false);

    pointOfInterest = cv::Point2f(25,40);
    testIsPointAbove(pointOfInterest, h, false);
}

TEST_F(HorizonTest, negativePitchOnly) {
    cv::Point2f pointOfInterest;
    Horizon h(cv::Point2f(0, 20), cv::Point2f(80, 20));

    pointOfInterest = cv::Point2f(18,18);
    testIsPointAbove(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(47,29);
    testIsPointAbove(pointOfInterest, h, false);

    pointOfInterest = cv::Point2f(18,20);
    testIsPointAbove(pointOfInterest, h, false);
}

TEST_F(HorizonTest, positiveRollNegativePitch) {
    cv::Point2f start(10,0);
    cv::Point2f end(80,40);
    Horizon h(start, end);

    cv::Point2f pointOfInterest;

    pointOfInterest = cv::Point2f(60,2);
    testIsPointAbove(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(5,30);
    testIsPointAbove(pointOfInterest, h, false);
}

TEST_F(HorizonTest, negativeRollPositivePitch) {
    cv::Point2f start(40,60);
    cv::Point2f end(80,40);
    Horizon h(start, end);

    cv::Point2f pointOfInterest;

    pointOfInterest = cv::Point2f(30,59);
    testIsPointAbove(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(76,55);
    testIsPointAbove(pointOfInterest, h, false);
}

TEST_F(HorizonTest, positiveRollpositivePitch) {
    cv::Point2f start(0,35);
    cv::Point2f end(50,60);
    Horizon h(start, end);

    cv::Point2f pointOfInterest;

    pointOfInterest = cv::Point2f(43, 40);
    testIsPointAbove(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(55, 40);
    testIsPointAbove(pointOfInterest, h, true);

    pointOfInterest = cv::Point2f(3,55);
    testIsPointAbove(pointOfInterest, h, false);
}

TEST_F(HorizonTest, steepHorizonPositiveSlope) {
    cv::Point2f start(17,60);
    cv::Point2f end(68,0);
    Horizon h(start, end);

    cv::Point2f p1(12, 30);
    cv::Point2f p2(23, 30);
    cv::Point2f p3(52, 30);
    cv::Point2f p4(77, 30);

    testIsPointAbove(p1, h, true);
    testIsPointAbove(p2, h, true);
    testIsPointAbove(p3, h, false);
    testIsPointAbove(p4, h, false);
}

TEST_F(HorizonTest, steepHorizonNegativeSlope) {
    cv::Point2f start(17,0);
    cv::Point2f end(68,60);
    Horizon h(start, end);

    cv::Point2f p1(12, 30);
    cv::Point2f p2(23, 30);
    cv::Point2f p3(52, 30);
    cv::Point2f p4(77, 30);

    testIsPointAbove(p1, h, false);
    testIsPointAbove(p2, h, false);
    testIsPointAbove(p3, h, true);
    testIsPointAbove(p4, h, true);
}

void HorizonTest::testIsPointAbove(const cv::Point2f &pointOfInterest, const Horizon &h, const bool &isAbove)
{
    EXPECT_EQ(isAbove, h.isPointAbove(pointOfInterest));
}