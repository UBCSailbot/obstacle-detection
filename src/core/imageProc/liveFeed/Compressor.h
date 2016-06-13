//
// Created by denis on 09/06/16.
//

#ifndef OBSTACLE_DETECTION_COMPRESSOR_H
#define OBSTACLE_DETECTION_COMPRESSOR_H


class Compressor {
public:
    /*
     * Returns a png buffer from a cv:mat
     * @param img the image
     * @param compressionLevel on a scale from 1-9 the compression level
     */
    static std::vector<uchar> imgToBuff(cv::Mat img, int compressionLevel);

};


#endif //OBSTACLE_DETECTION_COMPRESSOR_H
