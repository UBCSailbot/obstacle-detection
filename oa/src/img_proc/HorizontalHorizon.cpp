#include <math.h>

#include "HorizontalHorizon.h"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include "horizon_finder.h"

#define PI 3.14159265

void HorizontalHorizon::showHorizon() {

}


HorizontalHorizon::HorizontalHorizon(cv::Mat* in_img, float angle)
: HorizonFoundImg(in_img, angle)
{
	std::cout << "New horizontal horizon of angle " << horizon_angle << std::endl;

	cv::Mat angled_gradient;
	float slope = tan(angle) * 180 / PI;
	getAngledGradient(img, angled_gradient, slope);

	std::vector<HorizonLine> accum;

	int cur_row, x, y;
	float row_score;
	int max_row = angled_gradient.rows;
	int max_col = angled_gradient.cols;

	while( f(max_col, slope, cur_row) < max_row) {
		row_score = 0;
		struct HorizonLine cur_line;
		cur_line.start_index = cur_row;
		for (x = 0; x <= max_col; x++ ) {
			y = f(x, slope, cur_row);
			row_score += angled_gradient.at<float>(x,y);
		}
		cur_row ++;
	}

}

HorizontalHorizon::~HorizontalHorizon() {

}
