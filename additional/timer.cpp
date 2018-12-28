#include "timer.h"


Timer::Timer(long interval)
{
    this->interval = interval;
    this->duration = 0;
}

bool Timer::count(bool condition) {
    const long milliseconds = Timer::getMilliseconds();
    if (milliseconds - this->duration > this->interval && condition) {
        this->duration = milliseconds;
        return true;
    }
    else return false;
}

void Timer::reset()
{
    this->duration = Timer::getMilliseconds();
}

double Timer::ready() {
    const double milliseconds = Timer::getMilliseconds();
    return (milliseconds - this->duration) / this->interval;
}

long Timer::getMilliseconds(){
    timeb tb;
    ftime(&tb);
    int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}
