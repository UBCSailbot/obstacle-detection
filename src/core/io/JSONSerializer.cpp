#include "JSONSerializer.h"

const char *types[] = {"8Bit", "16Bit"};

std::string JSONSerializer::makeJSON(const std::string &img, const std::vector<cv::Rect> &rectangles, const ImageType &imageType,
                                     const Horizon &horizon) {
    Json::Value jsonObject;
    jsonObject[kImage] = Json::Value(img);

    jsonObject[kImageType] = Json::Value(types[imageType]);

    Json::Value jsonHorizon;
    jsonHorizon[kStartPoint][kX] = Json::Value(horizon.getStartPoint().x);;
    jsonHorizon[kStartPoint][kY] = Json::Value(horizon.getStartPoint().y);;

    jsonHorizon[kEndPoint][kX] = Json::Value(horizon.getEndPoint().x);
    jsonHorizon[kEndPoint][kY] = Json::Value(horizon.getEndPoint().y);;

    jsonObject[kHorizon] = jsonHorizon;

    Json::Value boxesArray = jsonObject[kBoxes];
    for (std::vector<int>::size_type i = 0; i != rectangles.size(); i++) {
        cv::Rect rectangle = rectangles[i];
        Json::Value box;
        box[kX] = Json::Value(rectangle.x);
        box[kY] = Json::Value(rectangle.y);
        box[kH] = Json::Value(rectangle.height);
        box[kW] = Json::Value(rectangle.width);
        boxesArray[static_cast<int>(i)] = box;
    }
    jsonObject[kBoxes] = boxesArray;

    std::ostringstream stream;
    stream << jsonObject;
    return stream.str();
}

std::string JSONSerializer::makeJSON(std::vector<std::string> images) {
    Json::Value jsonObject;

    Json::Value imagesArray = jsonObject[kImages];
    for (std::vector<int>::size_type i = 0; i != images.size(); i++) {
        std::string encodedImage = images[i];
        Json::Value image;
        image[kImage] = Json::Value(encodedImage);
        imagesArray[static_cast<int>(i)] = image;
    }
    jsonObject[kImages] = imagesArray;

    std::ostringstream stream;
    stream << jsonObject;
    return stream.str();
}


