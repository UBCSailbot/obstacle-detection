//
// Created by paul on 15/01/16.
//

#ifndef OBSTACLE_DETECTION_COMMONOPERATIONS_H
#define OBSTACLE_DETECTION_COMMONOPERATIONS_H

#include <math.h>

static double projectAontoB(double Ax, double Ay, double Bx, double By)
{

    double dotProduct = Ax * Bx + Ay * By;
    double vectorMagnitude = pow((pow(Bx, 2) + pow(By, 2)), 0.5);

    if (vectorMagnitude == 0)
    {
        return 0;
    }

    return dotProduct / vectorMagnitude;
}


#endif //OBSTACLE_DETECTION_COMMONOPERATIONS_H
