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


HorizonFoundImg* findHorizon(cv::Mat img, float horizon_angle);

#endif /* HORIZON_FINDER_H_ */
