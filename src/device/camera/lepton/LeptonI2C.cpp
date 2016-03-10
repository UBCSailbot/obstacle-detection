//
// Created by paul on 10/05/15.
//

#include "LeptonI2C.h"

bool _connected;


LEP_CAMERA_PORT_DESC_T _port;
LEP_SYS_SHUTTER_POSITION_E _lep_sys_shutter_position_e;

int lepton_connect() {
    LEP_OpenPort(1, LEP_CCI_TWI, 400, &_port);
    _connected = true;
    return 0;
}

void lepton_perform_ffc() {
    if (!_connected) {
        lepton_connect();
    }
    LEP_RunSysFFCNormalization(&_port);
}


void lepton_openShutter() {
    LEP_SetSysShutterPosition(&_port, LEP_SYS_SHUTTER_POSITION_OPEN);
}

void lepton_closeShutter() {
    LEP_SetSysShutterPosition(&_port, LEP_SYS_SHUTTER_POSITION_CLOSED);
}
