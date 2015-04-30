#ifndef IMU_PROCESSOR_H
#define IMU_PROCESSOR_H

#include "imu_data.h"
#include "quaternion.hpp"
#define betaDef		0.1f

typedef std::chrono::duration<std::chrono::steady_clock> TimeDuration;


class ImuProcessor
{
public:
	ImuProcessor(const ImuData& data,
                 float initRoll=0, float initPitch=0, float initYaw=0);

	float getRoll() const;
	float getPitch() const;
	float getYaw() const;

	void update(const ImuData& data);

private:
	int getTimeStepInMilliseconds(const ImuData& data);

	Quaternion MadgwickAHRSupdate(float gx, float gy, float gz,
                                  float ax, float ay, float az,
                                  float mx, float my, float mz,
                                  int timeStep) const;

	Quaternion MadgwickAHRSupdateIMU(float gx, float gy, float gz,
                                     float ax, float ay, float az,
                                     int timeStep) const;
	float invSqrt(float x);

	Quaternion orientation;
	TimePoint lastTimestamp;

};

#endif
