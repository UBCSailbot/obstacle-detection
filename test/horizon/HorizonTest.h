//
// Created by paul on 11/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_HORIZONTEST_H
#define OBSTACLE_AVOIDANCE_HORIZONTEST_H

#include "../../src/horizon/Horizon.h"

using namespace std;
using namespace cv;


class HorizonTest {
public:
    void testHorizon();

private:
    void testIsAboveHorizon();
    void testPointPosition(const Point2f &pointOfInterest, const Horizon &h,
                           const bool &isAbove, const string &testTitle) const;

    Horizon generateHorizonFromEndpoints(const Point2f &start, const Point2f &end) const;

    double calculatePitchAngleFromEndpoints(const Point2f &start, const Point2f &end) const;
    double calculateRollAngleFromEndpoints(const Point2f &start, const Point2f &end) const;

    void testStable() const;

    void testOnlyPositiveRoll() const;
    void testOnlyNegativeRoll() const;

    void testOnlyPositivePitch() const;
    void testOnlyNegativePitch() const;

    void testPositiveRollNegativePitch() const;
    void testNegativeRollPositivePitch() const;
};

#endif //OBSTACLE_AVOIDANCE_HORIZONTEST_H
