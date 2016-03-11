#include "LeptonRegistry.h"

Lepton &LeptonRegistry::getLepton0() {
    static Lepton lepton0(0, 1);

    return lepton0;
}

Lepton &LeptonRegistry::getLepton1() {
    static Lepton lepton1(1, 0);

    return lepton1;
}
