/*
 * HorizonFoundImg.h
 *
 *  Created on: Feb 16, 2015
 *      Author: paul
 */

#ifndef HORIZONFOUNDIMG_H_
#define HORIZONFOUNDIMG_H_

#include <memory>

#include <opencv2/core/core.hpp>

class HorizonFoundImg {
public:
	HorizonFoundImg(cv::Mat* img, float horizon_angle);
	virtual ~HorizonFoundImg();
	virtual void showHorizon() = 0;

private:
	//HorizonFoundImg();

	cv::Mat* img;
	float horizon_angle;
};

#endif /* HORIZONFOUNDIMG_H_ */
