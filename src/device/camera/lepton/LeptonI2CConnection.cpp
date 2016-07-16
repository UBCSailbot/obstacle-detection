#include "LeptonI2CConnection.h"

LeptonI2CConnection::LeptonI2CConnection() : LeptonI2CConnection(1) {

}

LeptonI2CConnection::LeptonI2CConnection(int i2cBusID) : _i2cBusID(i2cBusID) {
        init();
}


LeptonI2CConnection::~LeptonI2CConnection() {
        close();
}

void LeptonI2CConnection::performFFC() {
        if (!_connected) {
                    init();
                        }
            LEP_RunSysFFCNormalization(&_port);
}

void LeptonI2CConnection::openShutter() {
        LEP_SetSysShutterPosition(&_port, LEP_SYS_SHUTTER_POSITION_OPEN);
}

void LeptonI2CConnection::closeShutter() {
        LEP_SetSysShutterPosition(&_port, LEP_SYS_SHUTTER_POSITION_CLOSED);
}

void LeptonI2CConnection::init() {
        LEP_OpenPort((LEP_UINT16) _i2cBusID, LEP_CCI_TWI,
                                 (LEP_UINT16) _baudRateKHz, &_port);
            _connected = true;
}

void LeptonI2CConnection::close() {
        LEP_ClosePort(&_port);
            _connected = false;
}
