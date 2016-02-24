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


/**
  * encodes binary data of in_len bytes into base64
**/
string base64_encode(unsigned char const *bytes_to_encode, unsigned int in_len);


/**
  * decodes base64 string into binary data of size bites
**/

vector <uchar> base64_decode(std::string const &encoded_string, int size);


#endif //OBSTACLE_AVOIDANCE_BASE64ENCDEC_H
