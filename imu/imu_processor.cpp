#include "imu_processor.h"

// TODO: Implement!

ImuProcessor::ImuProcessor() {
	// TODO
}

ImuProcessor::~ImuProcessor() {
	// TODO
}

float ImuProcessor::getRoll() {
	return cur_roll;
}

float ImuProcessor::getPitch() {
	return cur_pitch;
}

void ImuProcessor::update(ImuData data) {
	// TODO - update moving accelerometer average and compute updated roll and pitch angles
}

void ImuProcessor::resetGyro() {
	// TODO
}