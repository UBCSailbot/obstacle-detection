#ifndef _OBSTACLEDETECTIONLOGGER_H
#define _OBSTACLEDETECTIONLOGGER_H

#include <iostream>
#include <sstream>

#include "zmq.hpp"

namespace od {

    class Logger {
    public:

        enum Level {
            DEBUG,
            INFO,
            WARN,
            ERROR,
            UNKNOWN,
            NUM_LEVELS
        };

        static const std::string IPC_ADDRESS;

        static void logDebug(const std::string &message, bool print = false);

        static void logInfo(const std::string &message, bool print = false);

        static void logWarn(const std::string &message, bool print = false);

        static void logError(const std::string &message, bool print = false);

        static void log(Level level, const std::string &message, bool print);

        // Delete other constructors and assignment operators
        Logger(const Logger &other) = delete;

        Logger(Logger &&other) = delete;

        Logger &operator=(const Logger &other) = delete;

        Logger &operator=(Logger &&other) = delete;

    private:
        Logger();

        zmq::socket_t logSocket_;

        static Logger &logger();

        static const std::string levelStrings[NUM_LEVELS];

        void publishViaZmq(const std::string &message);

        static std::string constructLogMessage(const Level level, const std::string &message);

    };

}

#endif /* _OBSTACLEDETECTIONLOGGER_H */