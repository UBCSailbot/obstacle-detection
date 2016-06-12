#ifndef OBSTACLE_DETECTION_ASTOPPABLEWORKER_H
#define OBSTACLE_DETECTION_ASTOPPABLEWORKER_H

/**
 * An abstract class meant to encapsulate the functionality
 *  of a class that does some open-ended work (i.e. running
 *  an infinite loop), but that you might want to stop at
 *  some arbitrary point in the future.
 * Note that no actual threading functionality is included
 *  in this abstract class; it simply offers some simple
 *  primitives used for signalling to an object that the
 *  infinite loop that it may or may not be running should
 *  be interrupted.
 * Perhaps an overly complicated way of avoiding code
 *  duplication, but it also offers the basis for testing
 *  this particular functionality.
 */
class AStoppableWorker {
public:

    /**
     * Pure virtual destructor makes sure this class
     *  is abstract (i.e. can't be instantiated)
     */
    virtual ~AStoppableWorker() = 0;

    /**
     * Signals to this object that it should stop
     *  whatever it's doing.
     * Note that this makes no guarantees that
     *  the thread will stop. It is up to the implementing
     *  class to handle this very basic "signal" in
     *  whatever way it sees fit. This function
     *  is simply offered as a convenience to reduce
     *  code duplication in subclasses, and to provide
     *  a locus for unit testing.
     */
    void stop();

protected:
     volatile bool _terminate = false;

};

#endif //OBSTACLE_DETECTION_ASTOPPABLEWORKER_H
