#ifndef OBSTACLE_AVOIDANCE_JSONSERIALIZER_H
#define OBSTACLE_AVOIDANCE_JSONSERIALIZER_H


#include <vector>
#include <dlib/data_io.h>
#include <dlib/opencv.h>
#include <json/json.h>

enum ImageType {
    IMAGE8BIT = 0, IMAGE16BIT = 1
};

class JSONSerializer {
public:
/*
  Converts information to JSON.
  The format is:
  {image:"image_blob",
  boxes:[{x,y,w,h}]
  }
*/
    static std::string makeJSON(std::string img, std::vector<cv::Rect> rectangles, ImageType imageType);

};

#endif //OBSTACLE_AVOIDANCE_JSONSERIALIZER_H
