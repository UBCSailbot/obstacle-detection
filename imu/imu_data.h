#ifndef IMU_DATA_H
#define IMU_DATA_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <chrono>
#include <vector>

typedef std::chrono::time_point < std::chrono::steady_clock > TimePoint;

struct Sensor
{
    float x;
    float y;
    float z;
};

class ImuData {
public:
	ImuData(float gyro_data[3], float accel_data[3],
			float mag_data[3]);

	Sensor getAccel() const;
	Sensor getGyro() const;
	Sensor getMag() const;

	TimePoint getTimestamp() const;
	void setTimestamp(TimePoint newTimeStamp);

	int millisSince(const TimePoint& prev) const;

	std::string toRawString(const TimePoint& prev_reading);
	std::string toPrettyString(const TimePoint& prev_reading);

private:
	Sensor accel;
	Sensor gyro;
	Sensor magnetic;

	// timestamp is obtained from system clock after successful read.
	TimePoint timestamp;

	std::string dataAsRawString;
	std::string dataAsPrettyString;

	std::string generateRawString(const TimePoint& prevReading) const;
	std::string generatePrettyString(const TimePoint& prevReading) const;

};


#endif
