//
// Created by denis on 09/06/16.
//

#ifndef OBSTACLE_DETECTION_COMPRESSOR_H
#define OBSTACLE_DETECTION_COMPRESSOR_H


class Compressor {
public:

    static std::vector<uchar> imgToBuff(cv::Mat img, int compressionLevel);

};


#endif //OBSTACLE_DETECTION_COMPRESSOR_H
