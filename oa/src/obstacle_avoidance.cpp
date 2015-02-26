/*
 * obstacle_avoidance.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: paul
 */
#include <opencv2/opencv.hpp>

#include "sensors/lepton.hpp"
#include "sensors/imu.hpp"
#include "img_proc/horizon_finder.h"
#include "img_proc/HorizonFoundImg.h"
#include "detect_obstacles.h"


#define MAX_PITCH 45
#define MIN_PITCH -15
#define MAX_ROLL -90
#define MIN_ROLL 90

bool unreasonable_pitch(float pitch_angle) {
	return pitch_angle > MAX_PITCH ||  pitch_angle < MIN_PITCH;
}

bool keeling(float roll_angle) {
	return roll_angle < MIN_ROLL || roll_angle > MAX_ROLL;
}

void avoid_obstacles() {

	cv::Mat* frame = get_lepton_frame();
	float roll_angle = get_roll();
	float pitch_angle = get_pitch();

	if (unreasonable_pitch(pitch_angle) || keeling(roll_angle)) {
		return;
	}

	if (detect_obstacles(frame, roll_angle)) {
		// verify persistence of obstacle over multiple frames

		// if persistent: EVASIVE ACTION!!

	}

}
