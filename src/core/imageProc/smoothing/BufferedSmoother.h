//
// Created by paul on 10/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_SMOOTHER_H
#define OBSTACLE_AVOIDANCE_SMOOTHER_H

/**
 * An interface for objects that smooth individual values
 *  based on their memory of previous values smoothed.
 */
class BufferedSmoother {

public:

    /**
     * PRE: This function has previously been called 0 or more times,
     *  giving this object some memory of the values it was asked to smooth.
     * POST: The current value is smoothed with respect to the previous
     *  values encountered by this object.
     */
    virtual int calculateSmoothedValue(int currentValue) = 0;

};

#endif //OBSTACLE_AVOIDANCE_SMOOTHER_H
