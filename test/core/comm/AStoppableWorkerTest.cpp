#include <gtest/gtest.h>
#include <thread>

#include "comm/AStoppableWorker.h"

class AStoppableWorkerTest : public ::testing::Test {

};

class MockStoppableWorker : public AStoppableWorker {

public:
    static const unsigned int LOOP_TIGHTNESS_MICROS = 100;

    MockStoppableWorker() {
        std::thread backgroundThread(&MockStoppableWorker::start, this);
        backgroundThread.detach();
    }

    void start() {
        _started = true;
        while (!_terminate) {
            usleep(LOOP_TIGHTNESS_MICROS);
        }

        _hasReceivedInterrupt = true;
    }

    bool hasStarted() {
        return _started;
    }

    bool hasReceivedInterrupt() {
        return _hasReceivedInterrupt;
    }

private:
    volatile bool _started = false;
    volatile bool _hasReceivedInterrupt = false;
};

TEST_F(AStoppableWorkerTest, doesItStop) {
    MockStoppableWorker w;

    while(!w.hasStarted()) {
        // wait for the thread to start
        usleep(100);
    }

    EXPECT_FALSE(w.hasReceivedInterrupt());
    w.stop();
    /*
     * This is super kludgy, but if the signal isn't
     *  consistentl received within 10 iterations of
     *  the worker thread loop, then this test deserves to fail.
     */
    usleep(MockStoppableWorker::LOOP_TIGHTNESS_MICROS * 10);
    EXPECT_TRUE(w.hasReceivedInterrupt());
}
