#include "CameraSpecifications.h"

bool operator==(const CameraSpecifications &lhs, const CameraSpecifications &rhs) {
    return lhs.pixelHeight == rhs.pixelHeight &&
           lhs.pixelWidth == rhs.pixelWidth &&
           lhs.FOVDegreesHorizontal == rhs.FOVDegreesHorizontal &&
           lhs.FOVDegreesVertical == rhs.FOVDegreesVertical;
}
