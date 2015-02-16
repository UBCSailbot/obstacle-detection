/*
 * HorizontalHorizon.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: paul
 */

#include "HorizontalHorizon.h"
#include <iostream>

void HorizontalHorizon::showHorizon() {

}

HorizontalHorizon::HorizontalHorizon(cv::Mat* in_img, float angle)
: HorizonFoundImg(in_img, angle)
{
//	std::cout << "New horizontal horizon of angle " << angle << std::endl;
//	horizon_angle = angle;
//	img = in_img;
}

HorizontalHorizon::~HorizontalHorizon() {
	// TODO Auto-generated destructor stub
}

