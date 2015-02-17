#ifndef HORIZONTALHORIZON_H_
#define HORIZONTALHORIZON_H_

#include "HorizonFoundImg.h"

class HorizontalHorizon: public HorizonFoundImg {
public:

	HorizontalHorizon(cv::Mat* img, float angle);
	~HorizontalHorizon();
	void showHorizon();

};

#endif /* HORIZONTALHORIZON_H_ */
