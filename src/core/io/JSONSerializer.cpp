#include "JSONSerializer.h"

const char *types[] = {"8Bit", "16Bit"};

std::string makeJSON(std::string img, std::vector<dlib::rectangle> rectangles, ImageType imageType) {

    Json::Value jsonObject;
    jsonObject["image"] = Json::Value(img);

    jsonObject["imageType"] = Json::Value (types[imageType]);

    Json::Value boxesArray = jsonObject["boxes"];
    for (std::vector<int>::size_type i = 0; i != rectangles.size(); i++) {
        dlib::rectangle rectangle = rectangles[i];
        Json::Value box;
        box["x"] = Json::Value((int) rectangle.left());
        box["y"] = Json::Value((int) rectangle.top());
        box["h"] = Json::Value((int) rectangle.height());
        box["w"] = Json::Value((int) rectangle.width());
        boxesArray[(int) i] = box;
    }
    jsonObject["boxes"] = boxesArray;

    std::ostringstream stream;
    stream << jsonObject;
    return stream.str();
}
