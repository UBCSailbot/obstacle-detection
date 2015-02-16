/*
 * VerticalHorizon.h
 *
 *  Created on: Feb 16, 2015
 *      Author: paul
 */

#ifndef VERTICALHORIZON_H_
#define VERTICALHORIZON_H_

#include "HorizonFoundImg.h"

class VerticalHorizon: public HorizonFoundImg {
public:
	VerticalHorizon(cv::Mat* img, float angle);
	virtual ~VerticalHorizon();
	void showHorizon();
};

#endif /* VERTICALHORIZON_H_ */
