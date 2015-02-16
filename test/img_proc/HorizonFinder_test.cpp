#include <assert.h>
#include <iostream>

#include "img_proc/horizon_finder.h"
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

void test_horizon_finder(){

	std::cout << "Testing Horizon Finder." << std::endl;

	test_normalize_angle();

}
