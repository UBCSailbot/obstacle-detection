#ifndef SUNIMG_H
#define SUNIMG_H

#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <limits>
#include <iostream>
#include <stack>

#include "geometry/Horizon.h"
#include "types/Rect2f.h"
#include "camera/lepton/LeptonCameraSpecifications.h"
#include "HorizonImage.h"

/**
 * Uses a simple heuristic to determine the parts of an image that are likely
 *  to contain sun glint.
 *
 * The heuristic works as follows:
 *      - First, we check if the sun is in the frame by searching for pixels
 *        above a given threshold value.
 *      - If the sun is found in the frame, then two lines perpendicular to
 *        the horizon in that frame are projected from either side of the sun,
 *        with a given margin.
 *      - If the sun is not found in the frame, then a second, lower threshold
 *        value is used to search for pixels below the horizon that might be
 *        reflections of the sun in the water. In similar fashion two lines
 *        are found perpendicular to the horizon that delimit a column in
 *        which higher-intensity pixels are likely to be sun glint.
 */
class SunImage: public HorizonImage {
  public:
    SunImage(const Horizon &horizon,
             const cv::Mat &frame,
             unsigned int minSunPixelValue = DEFAULT_MIN_SUN_PIXEL_VALUE,
             unsigned int minGlintPixelValue = DEFAULT_MIN_GLINT_PIXEL_VALUE,
             float glintColumnMargin = DEFAULT_MARGIN);
    ~SunImage();

    void findSunPosition();

    /**
     * RETURN: The bounding box around the sun in the image, if the sun is
     *  present. Otherwise, returns a rectangle whose upper left corner is
     *  the point (-1,-1) and whose dimensions are -1 x -1.
     */
    Rect2f getSunPosition() const;

    /**
     * RETURN: Whether or not the sun is visible within the frame.
     */
    bool containsSun() const;

    void findGlintColumn();

    /**
     * RETURN: The left margin of the column containing sun glint in
     *  the frame.
     */
    Line *getLeftGlintMargin() const;

    /**
     * RETURN: The right margin of the column containing sun glint in
     *  the frame.
     */
    Line *getRightGlintMargin() const;

    /**
     * RETURN: Whether this frame contains sun glint reflecting from the
     *  water.
     */
    bool containsGlint() const;

    void findMeanVariance();
    float getMean() const;
    float getVariance() const;

    /**
     * PRE: The position of the sun in the image, or its absence therefrom,
     *  has been ascertained.
     * PRE: A column perpendicular to the horizon has been found within which
     *  sun glint is likely to occur.
     *
     * RETURN: An 8-bit 3-channel color Mat with the following features
     *  rendered on it:
     *      - a red rectangle around the sun, if the sun is in the frame
     *      - a blue line where the horizon is
     *      - two parallel green lines forming a column perpendicular to the
     *        horizon, within which sun glint is thought to be located
     */
    cv::Mat render() const;

    static const unsigned int DEFAULT_MIN_SUN_PIXEL_VALUE = 10000;
    static const unsigned int DEFAULT_MIN_GLINT_PIXEL_VALUE = 8800;
    static constexpr float DEFAULT_MARGIN = 1.5;

  private:
    const Horizon _horizon;
    cv::Mat _frame;
    const unsigned int _minSunPixelValue;
    const unsigned int _minGlintPixelValue;
    const float _margin;

    Rect2f _sunPosition = Rect2f(-1.0f, -1.0f, -1.0f, -1.0f);

    float _mean = 0.0;
    float _variance = 0.0;

    Line *_leftMargin = new Line(cv::Point2f(-1.0f, -1.0f), cv::Point2f(-1.0f, -1.0f));
    Line *_rightMargin = new Line(cv::Point2f(-1.0f, -1.0f), cv::Point2f(-1.0f, -1.0f));

};

#endif
