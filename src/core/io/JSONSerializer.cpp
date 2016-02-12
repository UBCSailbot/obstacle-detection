#include "JSONSerializer.h"

std::string makeJSON(std::string img, std::vector<dlib::rectangle> boxes) {
    std::string temp = std::string("{") + "image:" + "\"" + img + "\", boxes:[";
    for (std::vector<int>::size_type i = 0; i != boxes.size(); i++) {
        dlib::rectangle a = boxes[i];
        temp = temp + "{" + "x:" + std::to_string(a.left()) + "," + "y:" +
               std::to_string(a.top()) + "," + "w:" + std::to_string(a.width()) + "," + "h:" +
               std::to_string(a.height()) + "}";
        if (i != boxes.size() - 1) {
            temp = temp + ",";
        }

    }

    temp = temp + "]}";
    return temp;
}
