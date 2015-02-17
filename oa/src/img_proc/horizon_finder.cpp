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
 * angle is defined in the range (-90, 90) degrees (non-inclusive).
 * angle > 180 rolls over into the bottom of the negative range, and vice versa.
 *
 */
int find_horizon(cv::Mat& img, float angle_deg) {

//	angle_deg = normalize_angle(angle_deg);



//	const uchar* image = img.ptr();
//	int width = img.cols;
//	int height = img.rows;
//
//	float slope = tan(angle_deg) * 180 / PI;
//
//
	return NO_HORIZON;

}


void normalize_angle(float& angle_deg) {

	while (angle_deg >= 180)
		angle_deg -= 360;

	while (angle_deg < -180)
		angle_deg += 360;

}

// XXX this shouldn't be necessary if we do bounds checking on our input angles
// make sure they're in the range (-90, 90) non-inclusive
float normalize_angle_ret(float angle_deg) {
	float new_angle = angle_deg;
	normalize_angle(new_angle);
	return new_angle;
}

HorizonFoundImg* findHorizon(cv::Mat img, float horizon_angle) {

	float slope = tan(horizon_angle * 180 / PI);
	normalize_angle(horizon_angle);

	if (abs(horizon_angle) < slope ) {
		return new HorizontalHorizon(&img, horizon_angle);
	}

	return new VerticalHorizon(&img, horizon_angle);

}

/**
 * Given an x coordinate, a slope, and a y-intercept, find the corresponding y coordinate.
 */
int f(int x, float m, int b) {
	return b - floor(x*m);
}

void getAngledGradient(cv::Mat* src, cv::Mat dst, float slope) {
	cv::Mat gradx, grady;
	getDerivKernels(gradx, grady, 1, 1, 3);

	for(int i=0; i < src->rows; i++) {
		for(int j=0; j< src->cols; j++) {
			float x = gradx.at<float>(i,j);
			float y = grady.at<float>(i,j);
			float dot_product = x + slope * y;
			float magnitude = sqrt(x*x + y*y);
			dst.at<uint16_t>(i,j) = dot_product / magnitude;
		}
	}
}

