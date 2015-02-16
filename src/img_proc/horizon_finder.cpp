/*
 * horizon_finder.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: paul
 */

#include <math.h>

#include "horizon_finder.h"
#include "HorizonFoundImg.h"
#include "HorizontalHorizon.h"
#include "VerticalHorizon.h"

#define HORIZON_FOUND 0
#define NO_HORIZON 1

#define PI 3.14159265

struct HorizontalLine {

	int start_row;
	int length;
	int gradAccumulator;

};

struct VerticalLine {

	int start_col;
	int length;
	int gradAccumulator;

};

/**
 * Input Mat is modified in place.
 *
 * angle of 0 means that the horizon should be completely horizontal.
 * angle is defined in the range [-180, 180) degrees.
 * angle > 180 rolls over into the bottom of the negative range, and vice versa.
 *
 */
int find_horizon(cv::Mat& img, float angle_deg) {

//	angle_deg = normalize_angle(angle_deg);



	const uchar* image = img.ptr();
	int width = img.cols;
	int height = img.rows;

	float slope = atan(angle_deg) * 180 / PI;


	return NO_HORIZON;

}


void normalize_angle(float& angle_deg) {

	while (angle_deg >= 180)
		angle_deg -= 360;

	while (angle_deg < -180)
		angle_deg += 360;

}

float normalize_angle_ret(float angle_deg) {
	float new_angle = angle_deg;
	normalize_angle(new_angle);
	return new_angle;
}

HorizonFoundImg* findHorizon(cv::Mat img, float horizon_angle) {

	int width = img.cols;
	int height = img.rows;

	float slope = atan(horizon_angle) * 180 / PI;
	normalize_angle(horizon_angle);

	if (abs(horizon_angle) < slope ) {
		return new HorizontalHorizon(&img, horizon_angle);
	}
	else {
		return new VerticalHorizon(&img, horizon_angle);
	}

}
