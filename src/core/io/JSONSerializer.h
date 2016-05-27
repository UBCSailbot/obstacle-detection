#ifndef OBSTACLE_AVOIDANCE_JSONSERIALIZER_H
#define OBSTACLE_AVOIDANCE_JSONSERIALIZER_H


#include <vector>
#include <dlib/data_io.h>
#include <dlib/opencv.h>
#include <json/json.h>


/*
  Converts information to JSON.
  The format is:
  {image:"image_blob",
  boxes:[{x,y,w,h}]
  }
*/
std::string makeJSON(std::string img, std::vector <dlib::rectangle> rectangles);

#endif //OBSTACLE_AVOIDANCE_JSONSERIALIZER_H
