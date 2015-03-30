#ifndef IMU_PROCESSOR_H
#define IMU_PROCESSOR_H

#include "imu_data.h" // TODO

// TODO: Finish header file
class ImuProcessor {
public:

	ImuProcessor();
	~ImuProcessor();

	float getRoll();
	float getPitch();
	
	void update(ImuData data);
	void resetGyro();

};

private:
	float cur_roll;
	float cur_pitch;

#endif