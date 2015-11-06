//
// Created by Amy Khosa on 15-11-05.
//

#ifndef OBSTACLE_AVOIDANCE_LEPTONDISCONNECTEDEXCEPTION_H
#define OBSTACLE_AVOIDANCE_LEPTONDISCONNECTEDEXCEPTION_H
#include <iostream>
#include <exception>

class LeptonSPIException : public std::exception {
private:
           const char* errMessage_;
public:
	LeptonSPIException(const char* errMessage) :
		errMessage_(errMessage)
	{};

	const char* what();
};

#endif //OBSTACLE_AVOIDANCE_LEPTONDISCONNECTEDEXCEPTION_H
