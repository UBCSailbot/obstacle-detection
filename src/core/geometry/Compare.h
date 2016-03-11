//
// Created by paul on 31/01/16.
//

#ifndef OBSTACLE_DETECTION_SAILBOTMATH_H
#define OBSTACLE_DETECTION_SAILBOTMATH_H

#include <cmath>

/**
 * Contains functions used to compare the equality of various quantities,
 *  namely in the cases where those quantities are represented by floating-
 *  point numbers, and so a direct test for equality is inappropriate.
 */
class Compare {

  public:

    /**
     * Returns a boolean indicating whether two angles are equal,
     *  within the range of precision of interest for obstacle avoidance.
     */
    static bool areAnglesEqual(double angle1, double angle2);

    /**
     * Returns a boolean indicating whether two coordinates *in abstract
     *  coordinate space* (not GPS coordinates or anything like that) are
     *  "close enough" for the purposes of obstacle avoidance calculations.
     *  Usually we're interested in pixel space coordinates, which are
     *  integer coordinates anyway, though higher levels of precision are
     *  desirable for more elaborate calculations.
     */
    static bool areCoordinatesEqual(double coord1, double coord2);

    /**
     * Used to decide whether the magnitude of two vectors is the same, as far
     *  as obstacle avoidance is concerned.
     */
    static bool areMagnitudesEqual(double mag1, double mag2);

  private:

    /**
     * Defines the smallest difference between two angles that we care about in
     *  obstacle avoidance.
     * Set to 0.1 degrees, which is pi/1800 radians.
     */
    static constexpr double ANGLE_PRECISION_RAD = (double) M_PI / 1800;

    /**
     * Defines the smallest difference in terms of coordinates that we care about,
     *  where coordinates are usually in terms of pixels. Note that in pixel space,
     *  coordinates are for all intents and purposes integers; allowing for sub-integer
     *  pixel coordinates allows for greater precision in intermediate calculations.
     */
    static constexpr double COORDINATE_PRECISION = 0.00000001;

    /**
     * Defines the smallest difference of geometric magnitudes that we care about.
     *  This is useful, for example, in comparing the magnitudes of two vectors.
     * Note that this is 2 orders of magnitude less precise than COORDINATE_PRECISION,
     *  to account for accumulated floating point error in calculations.
     */
    static constexpr double MAGNITUDE_PRECISION = COORDINATE_PRECISION * 100;
};

#endif //OBSTACLE_DETECTION_SAILBOTMATH_H
