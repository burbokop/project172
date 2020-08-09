#include "timer.h"

#include <SDL2/SDL.h>

Timer::Timer(unsigned interval)
{
    this->interval = interval;
    this->duration = 0;
}

bool Timer::count(bool condition) {
    if(interval > 0) {
        const unsigned milliseconds = Timer::getMilliseconds();
        if (milliseconds - this->duration > this->interval && condition) {
            this->duration = milliseconds;
            return true;
        }
        return false;
    }
    return true;
}

unsigned Timer::elapsed() {
    return Timer::getMilliseconds() - duration;
}

void Timer::reset() {
    this->duration = Timer::getMilliseconds();
}

double Timer::ready() {
    const double milliseconds = Timer::getMilliseconds();
    return (milliseconds - this->duration) / this->interval;
}

unsigned Timer::getMilliseconds(){
    timeb tb;
    ftime(&tb);
    unsigned nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}
