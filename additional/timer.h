#ifndef TIMER_H
#define TIMER_H

#include <sys/timeb.h>

class Timer
{
private:
    long interval;
    long duration;
public:
    Timer(long interval);
    bool count(bool condition = true);
    void reset();
    double ready();

    static long getMilliseconds();

};
#endif // TIMER_H
