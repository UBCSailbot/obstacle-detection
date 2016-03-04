#ifndef OBSTACLE_AVOIDANCE_LEPTONI2C_H
#define OBSTACLE_AVOIDANCE_LEPTONI2C_H

#include "LEPTON_SDK.h"
#include "LEPTON_SYS.h"
#include "LEPTON_Types.h"

class LeptonI2CConnection {

public:

    /**
     * Default constructor attaches to i2c-1.
     */
    LeptonI2CConnection();

    LeptonI2CConnection(int i2cBusID);

    virtual ~LeptonI2CConnection();

    void performFFC();
    void openShutter();
    void closeShutter();

private:
    int _i2cBusID;

    int _baudRateKHz = 400;
    bool _connected = false;

    LEP_CAMERA_PORT_DESC_T _port;
    LEP_SYS_SHUTTER_POSITION_E _lep_sys_shutter_position_e;

    void init();
    void close();

};

#endif //OBSTACLE_AVOIDANCE_LEPTONI2C_H
