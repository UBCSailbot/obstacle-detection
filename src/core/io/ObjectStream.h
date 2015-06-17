//
// Created by paul on 16/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_OBJECTSTREAM_H
#define OBSTACLE_AVOIDANCE_OBJECTSTREAM_H

template <class T>
class ObjectStream {

public:

    virtual void push(const T &updatedObject) = 0;

    virtual T next() = 0;

};


#endif //OBSTACLE_AVOIDANCE_OBJECTSTREAM_H
