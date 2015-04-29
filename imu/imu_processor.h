#ifndef IMU_PROCESSOR_H
#define IMU_PROCESSOR_H

#include "imu_data.h" // TODO
#define betaDef		0.1f

typedef std::chrono::duration<std::chrono::steady_clock> TimeDuration;

typedef struct Quaternion {
	float q0;
	float q1;
	float q2;
	float q3;
} Quaternion;

// TODO: Finish header file
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
	void MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, int timeStep);
	void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az, int timeStep);
	float invSqrt(float x);

	float computeRoll(Quaternion quaternion);
	float computePitch(Quaternion quaternion);
	float computeYaw(Quaternion quaternion);

	float currentRoll;
	float currentPitch;
	float currentYaw;

	Quaternion quaternion;

	TimePoint lastTimestamp;

};

#endif
