//
// Created by paul on 30/01/16.
//

#ifndef OBSTACLE_DETECTION_VECTOR_H
#define OBSTACLE_DETECTION_VECTOR_H

#include <cmath>
#include <opencv2/core/core.hpp>

#include "geometry/Compare.h"

/**
 * Geometric class representing a two-dimensional vector.
 *
 * Useful e.g. for encapslating linear algebra used to locate objects relative
 *  to the horizon.
 */
class Vector2d {

public:
    Vector2d(double xComponent, double yComponent);

    /**
     * Return a scalar quantity that is the dot product between this
     *  vector and an input vector. Dot product is associative, so
     *  u dot v = v dot u.
     */
    double dotProduct(const Vector2d &otherVector) const;

    /**
     * Return the angle between this vector and an input vector
     *  in radians, in range [0, pi]. Note that the angle
     *  is always positive, therefore is direction-independent.
     */
    double angleBetween(const Vector2d &otherVector) const;

    /**
     * Returns whether this vector and the given vector are pointing
     *  in the same direction.
     */
    bool isParallelTo(const Vector2d &otherVector) const;

    /**
     * Return the magnitude of the vector, calculated as the square root
     *  of the sum of the squares of its components. Note that this is
     *  recomputed every time it is called.
     */
    double calculateMagnitude() const;

    /**
     * Return a new vector with components [ kx ; ky], where k is a given scalar.
     */
    Vector2d multiplyByScalar(double k) const;

    /**
     * Return the component of this vector in the direction of the given
     *  input vector.
     */
    double scalarProjectionOnto(const Vector2d &targetVector) const;

    /**
     * Return the vector in the direction of the given input vector, whose
     *  magnitude is equal to the scalar projection of this vector onto said
     *  input vector.
     */
    Vector2d vectorProjectionOnto(const Vector2d &targetVector) const;

    /**
     * Return a vector with unit length in the direction of this vector.
     *  Recomputed every time it is called.
     */
    Vector2d calculateUnitVector() const;

    /**
     * Returns a boolean indicating whether the x and y components of this
     *  vector are both zero.
     */
    bool isZeroVector() const;

    /**
     * Returns a boolean indicating whether this vector is equivalent to
     *  the given input vector.
     *
     * Two vectors are equivalent if their x and y components are the same,
     *  to within an acceptable degree of precision (specified internally).
     */
    bool operator==(const Vector2d &other) const;

    double x, y;

protected:
    double calculateSquareMagnitude() const;

};


#endif //OBSTACLE_DETECTION_VECTOR_H
