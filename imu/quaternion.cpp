#include "quaternion.hpp"
#include <cmath>

Quaternion::Quaternion(float q0, float q1, float q2, float q3)
{
    Q0 = q0;
    Q1 = q1;
    Q2 = q2;
    Q3 = q3;
}

Quaternion::Quaternion(float pitch, float roll, float yaw)
{
    //TODO: Implement this
}

float Quaternion::getRoll() const
{
    return atan2( (Q2*Q3 + Q0*Q1),  0.5 - (Q1*Q1 + Q2*Q2) );
}

float Quaternion::getPitch() const
{
    return asin( -2 * (Q1*Q3 - Q0*Q2) );
}

float Quaternion::getYaw() const
{
    return atan2( (Q1*Q2 + Q0*Q3),  0.5 - (Q3*Q3 + Q2*Q2) );
}

float Quaternion::q0() const
{
    return Q0;
}

float Quaternion::q1() const
{
    return Q1;
}

float Quaternion::q2() const
{
    return Q2;
}

float Quaternion::q3() const
{
    return Q3;
}
