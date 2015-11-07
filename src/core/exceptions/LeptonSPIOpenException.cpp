//
// Created by Amy Khosa on 15-11-05.
//

#include "LeptonSPIOpenException.h"

const char* errMessage_;

const char* LeptonSPIOpenException::what(){
       return errMessage_;
 }

