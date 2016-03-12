#include "LeptonException.h"

const char *LeptonException::what() const noexcept {
    return errMessage_;
}
