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
	std::cout << "New horizontal horizon of angle " << horizon_angle << std::endl;


}

HorizontalHorizon::~HorizontalHorizon() {

}

