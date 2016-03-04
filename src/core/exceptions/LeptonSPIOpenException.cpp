//
// Created by Amy Khosa on 15-11-05.
//

#include "LeptonSPIOpenException.h"

const char *LeptonSPIOpenException::what() const noexcept {
    return errMessage_;
}
