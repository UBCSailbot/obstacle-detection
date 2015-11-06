//
// Created by Amy Khosa on 15-11-05.
//

#include "LeptonSPIException.h"

const char* errMessage_;

const char* LeptonSPIException::what(){
       return errMessage_;
 }

