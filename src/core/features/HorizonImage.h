//
// Created by paul on 25/01/16.
//

#ifndef OBSTACLE_DETECTION_HORIZONIMAGE_H
#define OBSTACLE_DETECTION_HORIZONIMAGE_H


#include <types/Image8bit.h>
#include <geometry/Horizon.h>
#include <features/HorizonImage.h>


/**
 * A simple container class that pairs an image with an object
 *  that represents the position of the horizon within that image.
 */
class HorizonImage {

  public:
    HorizonImage(const cv::Mat image, const Horizon &h);

    Horizon getHorizon() const;

    cv::Mat getImage() const;

    /**
     * The centerline of an image is defined as the line
     *  perpendicular to the horizon passing through the center
     *  of the image (i.e. the point (Px / 2, Py / 2), where Px
     *  is the width of the image in pixels and Py is the height).
     *
     * Note that this centerline is recomputed every time this function
     *  is called so as to keep this object stateless.
     */
    Line calculateCenterLine() const;

  protected:
    const cv::Mat _image;
    const Horizon _horizon;
};


#endif //OBSTACLE_DETECTION_HORIZONIMAGE_H
