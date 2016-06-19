#include "JSONSerializer.h"

const char *types[] = {"8Bit", "16Bit"};

std::string JSONSerializer::makeJSON(std::string img, std::vector<cv::Rect> rectangles, ImageType imageType) {
    Json::Value jsonObject;
    jsonObject["image"] = Json::Value(img);

    jsonObject["imageType"] = Json::Value (types[imageType]);

    Json::Value boxesArray = jsonObject["boxes"];
    for (std::vector<int>::size_type i = 0; i != rectangles.size(); i++) {
        cv::Rect rectangle = rectangles[i];
        Json::Value box;
        box["x"] = Json::Value((int) rectangle.x);
        box["y"] = Json::Value((int) rectangle.y);
        box["h"] = Json::Value((int) rectangle.height);
        box["w"] = Json::Value((int) rectangle.width);
        boxesArray[(int) i] = box;
    }
    jsonObject["boxes"] = boxesArray;

    std::ostringstream stream;
    stream << jsonObject;
    return stream.str();
}


