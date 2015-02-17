/*
 * horizon_finder.h
 *
 *  Created on: Feb 16, 2015
 *      Author: paul
 */

#ifndef HORIZON_FINDER_H_
#define HORIZON_FINDER_H_

#include "HorizonFoundImg.h"

int find_horizon(const cv::Mat& img, float angle_deg);

void normalize_angle(float& angle);
float normalize_angle_ret(float angle);
int f(int x_coordinate, float slope, int y_intercept);

// these belong in the horizon line parent class, but i can't resolve the inheritance right now
void getAngledGradient(cv::Mat* src, cv::Mat dst, float slope);
int f(int x, float slope, int y_intercept);


HorizonFoundImg* findHorizon(cv::Mat img, float horizon_angle);

#endif /* HORIZON_FINDER_H_ */
