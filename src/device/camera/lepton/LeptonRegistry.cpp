#include "LeptonRegistry.h"

LeptonRegistry &LeptonRegistry::instance() {
    static LeptonRegistry lepreg;

    return lepreg;
}

Lepton &LeptonRegistry::getLepton0() const {
    if (_lepton0 == nullptr) {
        *_lepton0 = Lepton(0, 1);
    }

    return *_lepton0;
}

Lepton &LeptonRegistry::getLepton1() const {
    if (_lepton1 == nullptr) {
        *_lepton1 = Lepton(0, 1);
    }

    return *_lepton1;
}

LeptonRegistry::LeptonRegistry() {

}
