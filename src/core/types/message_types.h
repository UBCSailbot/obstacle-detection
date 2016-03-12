#ifndef OBSTACLE_DETECTION_MESSAGE_TYPES_H
#define OBSTACLE_DETECTION_MESSAGE_TYPES_H

#include <cstdint>

typedef uint16_t msg_validation_code;

static msg_validation_code CAMERA_DATA_VECTOR_MSG_CODE = 28771; // "pc"
static msg_validation_code LEPTON_I2C_CONTROLLER_MSG_CODE = 11111; // completely arbitrary

#endif //OBSTACLE_DETECTION_MESSAGE_TYPES_H
