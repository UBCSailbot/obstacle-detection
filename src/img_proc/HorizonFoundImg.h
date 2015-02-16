/*
 * HorizonFoundImg.h
 *
 *  Created on: Feb 16, 2015
 *      Author: paul
 */

#ifndef HORIZONFOUNDIMG_H_
#define HORIZONFOUNDIMG_H_

#define HORIZONTAL 1
#define VERTICAL 2

#include <memory>

#include <opencv2/core/core.hpp>


struct HorizonLine {
		float slope;
		unsigned int start_index;
	} ;

class HorizonFoundImg {
public:
	HorizonFoundImg(cv::Mat* img, float horizon_angle);
	virtual ~HorizonFoundImg();
	virtual void showHorizon() = 0;

	/**
	 * TODO:
	 * implement some way of iterating over a subset of the pixels in an image,
	 * 	given the position of the horizon
	 */

protected:
	//HorizonFoundImg();

	cv::Mat* img;
	float horizon_angle;
	HorizonLine horizon_line;
};

#endif /* HORIZONFOUNDIMG_H_ */
