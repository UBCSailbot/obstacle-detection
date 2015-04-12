#include <cmath>
#include "imu_processor.h"
#include <iostream>

#define IMU_GYRO_X_ERROR -0.68

ImuProcessor::ImuProcessor()
{
    hasLastTimestamp = false;
    timeSinceLastReset = 0;
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
    // std::cout << "timeStep: " << timestep << std::endl;
    // std::cout << "Imu gyro: x=" << data.getGyro().x;
    // std::cout << " y=" << data.getGyro().y << std::endl;
	updateAccelAverage(data, timestep);
	updatePitchAndRoll(data, timestep);
}

void ImuProcessor::updateAccelAverage(const ImuData& data, int timeStepInMilliseconds)
{
    const auto newAccelRoll = atan(data.getAccel().x / data.getAccel().z);
    const auto newAccelPitch = atan(data.getAccel().y / data.getAccel().z);

    //TODO - this is behaving badly, figure out why
    // TODO: handle cases where timestep is multiple seconds
    if(!timeSinceLastReset) 
    {
        accelRoll = 0;
        accelPitch = 0;
    }
    else 
    {
        accelRoll = (accelRoll*timeSinceLastReset + newAccelRoll*timeStepInMilliseconds)
                  / (timeSinceLastReset + timeStepInMilliseconds);

        accelPitch = (accelPitch*timeSinceLastReset + newAccelPitch*timeStepInMilliseconds)
                  / (timeSinceLastReset + timeStepInMilliseconds);
    }
    timeSinceLastReset += timeStepInMilliseconds;  

    // std::cout << "AccelPitch: " << accelPitch << std::endl;
    // std::cout << "AccelRoll: " << accelRoll << std::endl;
    
}

void ImuProcessor::updatePitchAndRoll(const ImuData& data, int timeStepInMilliseconds)
{
    //TODO: set gyro scale factor - units: radians per millisecond
    const auto gyroScaleFactor = 0.001;

    //TODO: check axes - which is pitch/roll?
    currentRoll += data.getGyro().y * gyroScaleFactor * timeStepInMilliseconds;
    currentPitch += (data.getGyro().x - IMU_GYRO_X_ERROR) * gyroScaleFactor * timeStepInMilliseconds;
}

void ImuProcessor::resetGyro()
{
	currentRoll = accelRoll;
	currentPitch = accelPitch;
	hasLastTimestamp = false;
    timeSinceLastReset = 0;
}

int ImuProcessor::getTimeStepInMilliseconds(const ImuData& data)
{
    if(hasLastTimestamp)
    {
        const auto timestep = 
            std::chrono::duration_cast<std::chrono::milliseconds>
                (data.getTimestamp() - lastTimestamp).count();
        lastTimestamp = data.getTimestamp();
        return timestep;
    }

    else
    {
        lastTimestamp = data.getTimestamp();
        hasLastTimestamp = true;
        return 0;
    }
}
