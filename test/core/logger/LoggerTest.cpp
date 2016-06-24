#include <gtest/gtest.h>

#include <zmq.hpp>

#include "comm/ZmqContextSingleton.h"
#include "logger/Logger.h"
#include "time/TimeUtils.h"
#include "StdoutRedirect.h"


class LoggerTest : public ::testing::Test {
public:

    static void testDebugMessageIntegrity(const std::string &expected, const std::string &received)
    {
        std::string debugFragment("[DEBUG] ");
        // add 2 to size of date string because logger wraps it in parentheses
        const auto numCharsInDateString = od::time::getCurrentTimeString().size() + 2;
        // add 1 to the messages start index to take the space into account
        const auto messageStartIndex = debugFragment.size() + numCharsInDateString + 1;

        EXPECT_GT(received.size(), expected.size());

        EXPECT_EQ(debugFragment, received.substr(0, debugFragment.size()));
        // Skip the time string
        EXPECT_EQ(expected, received.substr(messageStartIndex, expected.size()));
    }
};

TEST_F(LoggerTest, validateStdOut) {
    std::string logString = "How now brown cow.";
    std::stringstream buffer;

    {
        StdoutRedirect redirect(buffer.rdbuf());
        od::Logger::logDebug(logString);
    }

    std::string msg(buffer.str());
    // Add a newline because that's how we print to stdout
    testDebugMessageIntegrity(logString + "\n", msg);
}

TEST_F(LoggerTest, zmqSubscriber) {
    zmq::socket_t logSubscriber(ZmqContextSingleton::getContext(), ZMQ_SUB);
    logSubscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    logSubscriber.connect(od::Logger::IPC_ADDRESS);

    // This test will sleep for a total of max 0.1 second
    int numTriesRemaining = 100;
    zmq::message_t msg;

    std::string logString = "This is a debug message.";
    {
        StdoutRedirect redirect(nullptr);

        while (numTriesRemaining--) {
            od::Logger::logDebug(logString);
            if (!logSubscriber.recv(&msg, ZMQ_NOBLOCK)) {
                // sleep for 1 millisecond
                usleep(1000);
            }
            else {
                break;
            }
        }
    }

    std::string receivedMessage((char *) msg.data(), msg.size());
    testDebugMessageIntegrity(logString, receivedMessage);
}
