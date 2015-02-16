#include <assert.h>
#include <iostream>
#include <typeinfo>

#include <opencv2/opencv.hpp>

#include "img_proc/horizon_finder.h"
#include "img_proc/HorizontalHorizon.h"
#include "img_proc/VerticalHorizon.h"

#include "HorizonFinder_test.h"


void test_normalize_angle(){

	assert(normalize_angle_ret(30.0) == 30);
	assert(normalize_angle_ret(-30.0) == -30);
	assert(normalize_angle_ret(45.0) == 45);
	assert(normalize_angle_ret(-45.0) == -45);
	assert(normalize_angle_ret(-181) == 179);
	assert(normalize_angle_ret(190) == -170);
	assert(normalize_angle_ret(-330) == 30);
	assert(normalize_angle_ret(330.0) == -30);

}

void test_make_horizontal() {

	std::string img_path = "out.png";
	cv::Mat img = cv::imread(img_path, -1);
	dynamic_cast<HorizontalHorizon*> (findHorizon(img, 30));
	dynamic_cast<VerticalHorizon*> (findHorizon(img, 30));

	std::cout << typeid(findHorizon(img, 30)).name() << std::endl;
	std::cout << typeid(findHorizon(img, 40)).name() << std::endl;

//	assert( typeid(findHorizon(img, 30)).name() == "HorizontalHorizon" );
//	assert( typeid(findHorizon(img, 40)).name() == "VerticalHorizon" );

}

void test_horizon_finder(){

	std::cout << "Testing Horizon Finder." << std::endl;

	test_normalize_angle();
	test_make_horizontal();

}
