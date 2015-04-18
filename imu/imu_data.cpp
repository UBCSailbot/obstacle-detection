#include "imu_data.h"

ImuData::ImuData(float accel_data[3], float gyro_data[3], float mag_data[3])
{
	timestamp = std::chrono::steady_clock::now();

	accel.x = accel_data[0];  accel.y = accel_data[1];  accel.z = accel_data[2];
	gyro.x = gyro_data[0];    gyro.y = gyro_data[1];    gyro.z = gyro_data[2];
	magnetic.x = mag_data[0]; magnetic.y = mag_data[1]; magnetic.z = mag_data[2];
}

Sensor ImuData::getAccel() const
{
	return accel;
}

Sensor ImuData::getGyro() const
{
	return gyro;
}

Sensor ImuData::getMag() const
{
	return magnetic;
}

TimePoint ImuData::getTimestamp() const
{
	return timestamp;
}

void ImuData::setTimestamp(TimePoint newTimeStamp) 
{
	timestamp = newTimeStamp;
}

int ImuData::millisSince(const TimePoint& prev) const
{
	int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp - prev).count();
	return elapsed;
}

std::string ImuData::toRawString(const TimePoint& prevReading)
{
	if (dataAsRawString.size() == 0)
    {
		dataAsRawString = generateRawString(prevReading);
	}
	return dataAsRawString;
}

std::string ImuData::generateRawString(const TimePoint& prevReading) const
{
    std::ostringstream raw;
    raw << millisSince(prevReading) << ", "
        << accel.x << ", " << accel.y << ", " << accel.z << ", "
        << gyro.x << ", " << gyro.y << ", " << gyro.z << ", "
        << magnetic.x << ", " << magnetic.y << ", " << magnetic.z << ", ";
    return raw.str();
}

std::string ImuData::toPrettyString(const TimePoint& prevReading)
{
	if (dataAsPrettyString.size() == 0)
    {
		dataAsPrettyString = generatePrettyString(prevReading);
	}
	return dataAsPrettyString;
}

std::string ImuData::generatePrettyString(const TimePoint& prevReading) const
{
    std::ostringstream pretty;
    pretty  << "dT: " << millisSince(prevReading)
            << " ACCEL: " << accel.x << " " << accel.y << " " << accel.z
            << " GYRO: " << gyro.x << " " << gyro.y << " " << gyro.z
            << " MAG: " << magnetic.x << " " << magnetic.y << " " << magnetic.z << "\n";
    return pretty.str();
}
