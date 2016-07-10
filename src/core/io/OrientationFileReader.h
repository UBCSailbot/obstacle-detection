//
// Created by paul on 16/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_HORIZONFILEREADER_H
#define OBSTACLE_AVOIDANCE_HORIZONFILEREADER_H


#include <queue>
#include <iostream>
#include <fstream>
#include <geometry/Orientation.h>

#include "io/ObjectStream.h"
#include "exceptions/NoSuchElementException.h"


class OrientationFileReader : public ObjectStream<Orientation> {

public:
    OrientationFileReader(const std::string &imuLogFile,
                          bool invertRoll = false, bool invertPitch = false);

    /**
     * PRE: This object contained n Horizon objects.
     * POST: Horizon h is added to this object, at the
     *  end of the queue.
     */
    void push(const Orientation &o);

    /**
     * PRE: This object is populated with one or more Horizon objects.
     * POST: The Horizon object that was added least recently is removed
     *  from this object and returned.
     * RETURN: The Horizon object that was added least recently.
     * THROWS: NoSuchElementException if this object is empty.
     */
    Orientation next();

private:
    std::queue<Orientation> _orientations;
    bool _invertRoll;
    bool _invertPitch;

};


#endif //OBSTACLE_AVOIDANCE_HORIZONFILEREADER_H
