/*
 * HorizonFoundImg.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: paul
 */

#include <cmath>

#include "HorizonFoundImg.h"
#include "HorizontalHorizon.h"
#include "VerticalHorizon.h"

#define PI 3.14159265

HorizonFoundImg::HorizonFoundImg(cv::Mat* in_img, float angle) {
	horizon_angle = angle;
	img = in_img;
}

HorizonFoundImg::~HorizonFoundImg() {
	img = NULL;
}



void HorizonFoundImg::showHorizon() {

}

void normalize_horizon_angle(float& angle_deg) {

	while (angle_deg >= 180)
		angle_deg -= 360;

	while (angle_deg < -180)
		angle_deg += 360;

}

/**
 * Given an x coordinate, a slope, and a y-intercept, find the corresponding y coordinate.
 */
//int f(int x, float m, int b) {
//	return b - floor(x*m);
//}
//
//void getAngledGradient(cv::Mat* src, cv::Mat dst, float slope) {
//	cv::Mat gradx, grady;
//	getDerivKernels(gradx, grady, 1, 1, 3);
//
//	for(int i=0; i < src->rows; i++) {
//		for(int j=0; j< src->cols; j++) {
//			float x = gradx.at<float>(i,j);
//			float y = grady.at<float>(i,j);
//			float dot_product = x + slope * y;
//			float magnitude = sqrt(x*x + y*y);
//			dst.at<uint16_t>(i,j) = dot_product / magnitude;
//		}
//	}
//}
