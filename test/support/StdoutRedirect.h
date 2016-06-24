#ifndef OBSTACLE_DETECTION_STDOUTREDIRECT_H
#define OBSTACLE_DETECTION_STDOUTREDIRECT_H

#include <iostream>

class StdoutRedirect {

public:
    StdoutRedirect(std::streambuf *new_buffer)
            : old(std::cout.rdbuf(new_buffer))
    { }

    ~StdoutRedirect() {
        std::cout.rdbuf(old);
    }

private:
    std::streambuf *old;
};

#endif //OBSTACLE_DETECTION_STDOUTREDIRECT_H
