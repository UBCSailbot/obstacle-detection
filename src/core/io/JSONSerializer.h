#ifndef OBSTACLE_AVOIDANCE_JSONSERIALIZER_H
#define OBSTACLE_AVOIDANCE_JSONSERIALIZER_H


#include <vector>
#include <dlib/data_io.h>
#include <dlib/opencv.h>
#include <json/json.h>
#include <geometry/Horizon.h>

enum ImageType {
    IMAGE8BIT = 0, IMAGE16BIT = 1
};

class JSONSerializer {
public:

    /**
    * Converts information to JSON.
    * The format is:
    * {image:"image_blob",
    * boxes:[{x,y,w,h}]
    */
    static std::string makeJSON(const std::string &img, const std::vector<cv::Rect> &rectangles, const ImageType &imageType, const Horizon &horizon);

private:

    static constexpr auto kStartPoint = "startPoint";
    static constexpr auto kEndPoint = "endPoint";
    static constexpr auto kX = "x";
    static constexpr auto kY = "y";
    static constexpr auto kImage = "image";
    static constexpr auto kHorizon = "horizon";
    static constexpr auto kH = "h";
    static constexpr auto kW = "w";
    static constexpr auto kBoxes = "boxes";
    static constexpr auto kImageType = "imageType";

};

#endif //OBSTACLE_AVOIDANCE_JSONSERIALIZER_H
