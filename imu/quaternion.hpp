#ifndef QUATERNION_H
#define QUATERNION_H

class Quaternion
{
public:
    Quaternion(float q0, float q1, float q2, float q3);
    Quaternion(float pitch, float roll, float yaw);

    float getRoll() const;
	float getPitch() const;
	float getYaw() const;

	float q0() const;
	float q1() const;
	float q2() const;
	float q3() const;

private:
    float Q0;
	float Q1;
	float Q2;
	float Q3;
};

#endif
