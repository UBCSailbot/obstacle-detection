#include <ctime>
#include <iomanip>
#include <chrono>

#include <comm/ZmqContextSingleton.h>
#include <logger/Logger.h>
#include <time/TimeUtils.h>

namespace od {

    const std::string Logger::IPC_ADDRESS = "ipc:///tmp/sailbot-od-logger";

    Logger &Logger::logger() {
        static Logger log;

        return log;
    }

    const std::string Logger::levelStrings[NUM_LEVELS] =
            {"DEBUG",
             "INFO",
             "WARN",
             "ERROR",
             "UNKNOWN"};

    Logger::Logger() :
            logSocket_(ZmqContextSingleton::getContext(), ZMQ_PUB) {
        logSocket_.bind(IPC_ADDRESS);
    }

    void Logger::log(Level level, const std::string &message, bool print) {
        const std::string &messageStr = constructLogMessage(level, message);
        if (print) {
            std::cout << messageStr << std::endl;
        }
        logger().publishViaZmq(messageStr);
    }

    std::string Logger::constructLogMessage(Level level,
                                            const std::string &message) {
        if (level > ERROR || level < DEBUG) {
            level = UNKNOWN;
        }

        std::ostringstream oss;
        // Log the level
        std::left(oss);
        oss << std::setw(6) << "[" + levelStrings[level] << "] ";

        // Log the time
        oss << "(" << od::time::getCurrentTimeString() << ") ";

        // ...and, of course, the message
        oss << message;

        return oss.str();
    }

    void Logger::logDebug(const std::string &message, bool print) {
        logger().log(DEBUG, message, print);
    }

    void Logger::logInfo(const std::string &message, bool print) {
        logger().log(INFO, message, print);
    }

    void Logger::logWarn(const std::string &message, bool print) {
        logger().log(WARN, message, print);
    }

    void Logger::logError(const std::string &message, bool print) {
        logger().log(ERROR, message, print);
    }

    void Logger::publishViaZmq(const std::string &message) {
        zmq::message_t msg(message.c_str(), message.size());
        logSocket_.send(msg);
    }

} // od













//
//          .--.
//        .'    ',
//      .'.*.*.*.*',
//     /            \
//    /              \
//   Y                Y
//   |.*.*.*.*.*.*.*.*|
//   |.*.*.*.*.*.*.*.*|
//   Y                Y
//    \              /
//     \            /
// tms  `.*.*.*.*..'
//        `..__..'
//
