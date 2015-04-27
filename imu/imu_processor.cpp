#include <cmath>
#include "imu_processor.h"
#include <iostream>

#define IMU_GYRO_X_ERROR -0.68

ImuProcessor::ImuProcessor(const ImuData& data)
{
    timeSinceLastReset = 0;

    accelRoll = getAccelRoll(data);
    accelPitch = getAccelPitch(data);
    readingsSinceLastReset = 1;

    currentRoll = accelRoll;
	currentPitch = accelPitch;

	lastTimestamp = data.getTimestamp();
}

float ImuProcessor::getRoll() const
{
	return currentRoll;
}

float ImuProcessor::getPitch() const
{
	return currentPitch;
}

void ImuProcessor::update(const ImuData& data)
{
	const auto timestep = getTimeStepInMilliseconds(data);
	// updateAccelAverage(data, timestep);
	// updatePitchAndRoll(data, timestep);
    // readingsSinceLastReset ++;
    currentPitch = getAccelPitch(data);
    currentRoll = getAccelRoll(data);
}

void ImuProcessor::updateAccelAverage(const ImuData& data, int timeStepInMilliseconds)
{
    const auto newAccelRoll = getAccelRoll(data);
    const auto newAccelPitch = getAccelPitch(data);

    // TODO: handle cases where timestep is multiple seconds
    accelRoll = (accelRoll*readingsSinceLastReset + newAccelRoll)
              / (readingsSinceLastReset + 1);

    accelPitch = (accelPitch*readingsSinceLastReset + newAccelPitch)
              / (readingsSinceLastReset + 1);

    timeSinceLastReset += timeStepInMilliseconds;
}

float ImuProcessor::getAccelRoll(const ImuData& data) const
{
    return atan(data.getAccel().x / data.getAccel().z);
}

float ImuProcessor::getAccelPitch(const ImuData& data) const
{
    return atan(data.getAccel().y / data.getAccel().z);
}

void ImuProcessor::updatePitchAndRoll(const ImuData& data, int timeStepInMilliseconds)
{
    //TODO: set gyro scale factor - units: radians per millisecond
    const auto gyroScaleFactor = 0.00001;

    currentRoll += data.getGyro().y * gyroScaleFactor * timeStepInMilliseconds;
    currentPitch += (data.getGyro().x - IMU_GYRO_X_ERROR) * gyroScaleFactor * timeStepInMilliseconds;
}

void ImuProcessor::resetGyro(const ImuData& data)
{
	currentRoll = accelRoll;
	currentPitch = accelPitch;
	lastTimestamp = data.getTimestamp();
    timeSinceLastReset = 0;
    readingsSinceLastReset = 1;
}

int ImuProcessor::getTimeStepInMilliseconds(const ImuData& data)
{
    const auto timestep =
        std::chrono::duration_cast<std::chrono::milliseconds>
            (data.getTimestamp() - lastTimestamp).count();
    lastTimestamp = data.getTimestamp();
    return timestep;
}
