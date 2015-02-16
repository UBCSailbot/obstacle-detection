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
