#ifndef IMU_PROCESSOR_H
#define IMU_PROCESSOR_H

#include "imu_data.h" // TODO

typedef std::chrono::duration<std::chrono::steady_clock> TimeDuration;

// TODO: Finish header file
class ImuProcessor
{
public:

	ImuProcessor(const ImuData& data);

	float getRoll() const;
	float getPitch() const;

	void update(const ImuData& data);
	void resetGyro(const ImuData& data);

private:
	int getTimeStepInMilliseconds(const ImuData& data);
	void updateAccelAverage(const ImuData& data, int timeStepInMilliseconds);
	void updatePitchAndRoll(const ImuData& data, int timeStepInMilliseconds);

	float getAccelRoll(const ImuData& data) const;
	float getAccelPitch(const ImuData& data) const;

	float currentRoll;
	float currentPitch;

	float accelRoll;
	float accelPitch;

	int timeSinceLastReset;
	int readingsSinceLastReset;

	TimePoint lastTimestamp;

};

#endif
