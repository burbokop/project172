#ifndef TIMER_H
#define TIMER_H

#include <sys/timeb.h>


class Timer {
private:
    unsigned interval;
    unsigned duration;
public:
    Timer(unsigned interval = 0);
    bool count(bool condition = true);
    unsigned elapsed();
    void reset();
    double ready();

    static unsigned getMilliseconds();
};
#endif // TIMER_H
