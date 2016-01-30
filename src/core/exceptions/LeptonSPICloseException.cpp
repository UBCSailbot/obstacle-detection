//
// Created by Amy Khosa on 15-11-05.
//

#include "LeptonSPICloseException.h"

const char* closeErrMessage_;

const char* LeptonSPICloseException::what(){
       return closeErrMessage_;
 }

