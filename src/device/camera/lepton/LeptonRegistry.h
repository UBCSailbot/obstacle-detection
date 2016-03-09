//
// Created by paul on 08/03/16.
//

#ifndef OBSTACLE_DETECTION_LEPTONREGISTRY_H
#define OBSTACLE_DETECTION_LEPTONREGISTRY_H


#include "Lepton.h"

class LeptonRegistry {

public:
    static LeptonRegistry &instance();

    /**
     * Returns the Lepton connect to SPI chip select 0 and I2C bus 1
     */
    Lepton& getLepton0() const;

    /**
     * Returns the Lepton connect to SPI chip select 1 and I2C bus 0
     */
    Lepton& getLepton1() const;

private:

    LeptonRegistry();

    Lepton* _lepton0;
    Lepton* _lepton1;

};


#endif //OBSTACLE_DETECTION_LEPTONREGISTRY_H
