//
// Created by Amy Khosa on 15-10-29.
//

#ifndef OBSTACLE_AVOIDANCE_BASE64ENCDEC_H
#define OBSTACLE_AVOIDANCE_BASE64ENCDEC_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "types/Image8bit.h"




string base64_encode(unsigned char const*  bytes_to_encode, unsigned int in_len);
//string base64_encode(Image8bit img,vector<uchar> buffToStoreBinaryImg);
vector<uchar> base64_decode(std::string const& encoded_string, int size);


#endif //OBSTACLE_AVOIDANCE_BASE64ENCDEC_H
