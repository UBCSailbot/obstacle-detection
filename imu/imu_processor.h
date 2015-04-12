#ifndef IMU_PROCESSOR_H
#define IMU_PROCESSOR_H

#include "imu_data.h" // TODO

typedef std::chrono::duration<std::chrono::steady_clock> TimeDuration;

// TODO: Finish header file
class ImuProcessor
{
public:

	ImuProcessor();

	float getRoll() const;
	float getPitch() const;

	void update(const ImuData& data);
	void resetGyro();

private:
	int getTimeStepInMilliseconds(const ImuData& data) const;
	void updateAccelAverage(const ImuData& data, int timeStepInMilliseconds);
	void updatePitchAndRoll(const ImuData& data, int timeStepInMilliseconds);

	float currentRoll;
	float currentPitch;

	float accelRoll;
	float accelPitch;

	int accelAverageWeight;

    bool hasLastTimestamp;
	TimePoint lastTimestamp;

};

#endif
