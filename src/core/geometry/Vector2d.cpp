//
// Created by paul on 30/01/16.
//

#include "Vector2d.h"

Vector2d::Vector2d(double xComponent, double yComponent) :
        x(xComponent), y(yComponent)
{}

double Vector2d::dotProduct(const Vector2d &otherVector) const {
    return x * otherVector.x +
           y * otherVector.y;
}

double Vector2d::angleBetween(const Vector2d &otherVector) const {
    double productOfMagnitudes = calculateMagnitude() * otherVector.calculateMagnitude();
    if (Compare::areMagnitudesEqual(productOfMagnitudes, 0)) {
        throw std::invalid_argument("Angle between a vector and a zero vector is undefined.");
    }

    double quotient = dotProduct(otherVector) / productOfMagnitudes;

    if (fabs(quotient) > 1) {
        if (Compare::areAnglesEqual(quotient, 1)) {
            quotient = 1;
        }
        else if (Compare::areAnglesEqual(quotient, -1)) {
            quotient = -1;
        }
        else {
            // Entering this block means that the absolute value of the dot product
            //  is greater than the product of the magnitudes of the two vectors.
            // This should be a numerical impossibility.
            throw std::invalid_argument("Anomaly: dot product of two vectors exceeded "
                                                "the product of their magnitudes.");
        }
    }

    return acos(quotient);
}

double Vector2d::calculateMagnitude() const {
    return pow( calculateSquareMagnitude(), 0.5);
}

double Vector2d::scalarProjectionOnto(const Vector2d &targetVector) const {
    if (targetVector.isZeroVector()) {
        return 0;
    }
    return dotProduct(targetVector) / targetVector.calculateMagnitude();
}

Vector2d Vector2d::vectorProjectionOnto(const Vector2d &targetVector) const {
    if (targetVector.isZeroVector()) {
        return targetVector.multiplyByScalar(0);
    }
    double scalarFactor = dotProduct(targetVector) / targetVector.calculateSquareMagnitude();
    return targetVector.multiplyByScalar(scalarFactor);
}

Vector2d Vector2d::multiplyByScalar(double k) const {
    return Vector2d(x * k, y * k);
}


Vector2d Vector2d::calculateUnitVector() const {
    if (isZeroVector()) {
        throw std::invalid_argument("Unit vector is undefined for zero vector.");
    }
    return multiplyByScalar(1 / calculateMagnitude());
}

double Vector2d::calculateSquareMagnitude() const {
    return pow(x, 2) + pow(y, 2);
}

bool Vector2d::operator==(const Vector2d &other) const {
    return Compare::areCoordinatesEqual(x, other.x) &&
           Compare::areCoordinatesEqual(y, other.y);
}

bool Vector2d::isZeroVector() const {
    return Compare::areCoordinatesEqual(x, 0) &&
           Compare::areCoordinatesEqual(y, 0);
}
