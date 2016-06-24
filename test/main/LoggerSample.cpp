#include <logger/Logger.h>
#include <unistd.h>

int main() {
    od::Logger::logDebug("Hello! (Debug)");
    usleep(1000 * 40);
    od::Logger::logInfo("This Info message should be 0.04 seconds after the previous one.");
    usleep(1000 * 80);
    od::Logger::logWarn("This Warning message should be 0.08 seconds after the previous one.");
    usleep(1000 * 40);
    od::Logger::logError("This Error message should be 0.04 seconds after the previous one.");
    od::Logger::log(od::Logger::UNKNOWN, "(unknown log level) Make sure to compare "
            "timestamps on the log messages to your computer's actual time!");
}