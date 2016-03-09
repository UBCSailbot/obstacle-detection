#ifndef OBSTACLE_DETECTION_LEPTONREGISTRY_H
#define OBSTACLE_DETECTION_LEPTONREGISTRY_H


#include "Lepton.h"

class LeptonRegistry {

public:

    /**
     * Returns the Lepton connected to SPI chip select 0 and I2C bus 1.
     *  These are assigned to Lepton0 (the default) because these are the
     *  defaults for each connection. (SPI can easily be switched between spi0
     *  and spi1 by changing the pin on the Pi to which the Lepton is connected,
     *  but by default i2c0 is turned off on the Pi.)
     */
    static Lepton& getLepton0();

    /**
     * Returns the Lepton connected to SPI chip select 1 and I2C bus 0.
     */
    static Lepton& getLepton1();

    /**
     * Delete the copy constructor to make sure it doesn't inadvertently get used.
     */
    LeptonRegistry(LeptonRegistry const&) = delete;

    /**
     * Delete the assignment operator to make sure it doesn't inadvertently get used.
     */
    void operator=(LeptonRegistry const&) = delete;

private:

    /**
     * A private constructor makes sure that this class can only be instantiated
     *  by this class itself (e.g. as a singleton).
     */
    LeptonRegistry() {}

};


#endif //OBSTACLE_DETECTION_LEPTONREGISTRY_H
