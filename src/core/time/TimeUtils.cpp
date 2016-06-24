#include "time/TimeUtils.h"

namespace od {

namespace time {

namespace {
    static const size_t maxTimeStringSize_ = 128;
    static char timeStringBuf_[maxTimeStringSize_];
} // anonymous namespace

std::string getCurrentTimeString() {
    // We do all these gymnastics to get tenths of a second.
    namespace chrono = std::chrono;
    using milliseconds = chrono::milliseconds;

    const auto now = chrono::system_clock::now();
    const auto nowMillis = chrono::duration_cast<milliseconds>(now.time_since_epoch());
    const auto nowSeconds = chrono::duration_cast<chrono::seconds>(nowMillis);
    const auto millis = nowMillis - chrono::duration_cast<milliseconds>(nowSeconds);

    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm* currentTm = localtime(&currentTime);

    std::strftime(timeStringBuf_, maxTimeStringSize_, "%Y-%m-%d %H:%M:%S", currentTm);

    std::ostringstream oss;

    oss << timeStringBuf_ << "." <<
    (millis.count() < 100 ? "0" : "") << millis.count() / 10;

    return oss.str();
}

} // time

} // od
