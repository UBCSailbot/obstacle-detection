#include <cmath>
#include "imu_processor.h"

ImuProcessor::ImuProcessor()
{
    hasLastTimestamp = false;
	lastTimestamp = std::chrono::steady_clock::now();
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
	updateAccelAverage(data, timestep);
	updatePitchAndRoll(data, timestep);
}

void ImuProcessor::updateAccelAverage(const ImuData& data, int timeStepInMilliseconds)
{
    const auto newAccelRoll = atan(data.getAccel().x / -data.getAccel().z);
    const auto newAccelPitch = atan(data.getAccel().y / -data.getAccel().z);

    accelRoll = (accelRoll*accelAverageWeight + newAccelRoll*timeStepInMilliseconds)
              / (accelAverageWeight + timeStepInMilliseconds);

    accelPitch = (accelPitch*accelAverageWeight + newAccelPitch*timeStepInMilliseconds)
              / (accelAverageWeight + timeStepInMilliseconds);

    accelAverageWeight += timeStepInMilliseconds;
}

void ImuProcessor::updatePitchAndRoll(const ImuData& data, int timeStepInMilliseconds)
{
    //TODO: set gyro scale factor - units: radians per millisecond
    const auto gyroScaleFactor = 1.0;

    //TODO: check axes - which is pitch/roll?
    currentRoll += data.getGyro().y * gyroScaleFactor;
    currentPitch += data.getGyro().x * gyroScaleFactor;
}

void ImuProcessor::resetGyro()
{
	currentRoll = accelRoll;
	currentPitch = accelPitch;
	hasLastTimestamp = false;
}

int ImuProcessor::getTimeStepInMilliseconds(const ImuData& data) const
{
    if(hasLastTimestamp) return std::chrono::duration_cast<std::chrono::milliseconds>
        (data.getTimestamp() - lastTimestamp).count();

    else return 0;
}
