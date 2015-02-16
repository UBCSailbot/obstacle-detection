/*
 * VerticalHorizon.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: paul
 */

#include "VerticalHorizon.h"
#include <iostream>



VerticalHorizon::VerticalHorizon(cv::Mat* in_img, float angle)
: HorizonFoundImg(in_img, angle)
{
//	std::cout << "New vertical horizon of angle " << angle << std::endl;
//	horizon_angle = angle;
//	img = in_img;
}

VerticalHorizon::~VerticalHorizon() {
	// TODO Auto-generated destructor stub
}

void VerticalHorizon::showHorizon() {

}
