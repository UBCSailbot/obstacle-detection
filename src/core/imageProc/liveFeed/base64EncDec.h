//
// Created by Amy Khosa on 15-10-29.
//

#ifndef OBSTACLE_AVOIDANCE_BASE64ENCDEC_H
#define OBSTACLE_AVOIDANCE_BASE64ENCDEC_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "types/Image8bit.h"

using namespace std;


//string base64_encode(unsigned char const*  bytes_to_encode, unsigned int in_len);
string base64_encode(Image8bit img);
string base64_decode(std::string const& encoded_string);


#endif //OBSTACLE_AVOIDANCE_BASE64ENCDEC_H
