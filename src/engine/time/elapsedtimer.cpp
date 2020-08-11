#include "elapsedtimer.h"
#include <sys/timeb.h>

namespace e172 {

ElapsedTimer::time_t ElapsedTimer::interval() const {
    return m_interval;
}

ElapsedTimer::ElapsedTimer(time_t interval) {
    m_interval = interval;
    reset();
}

bool ElapsedTimer::check(bool condition) {
    if(m_interval > 0) {
        const auto milliseconds = ElapsedTimer::currentMilliseconds();
        if (milliseconds - m_checkPoint > m_interval && condition) {
            m_checkPoint = milliseconds;
            return true;
        }
        return false;
    }
    return true;
}

ElapsedTimer::time_t ElapsedTimer::elapsed() {
    return ElapsedTimer::currentMilliseconds() - m_startPoint;
}

void ElapsedTimer::reset() {
    m_startPoint = ElapsedTimer::currentMilliseconds();
    m_checkPoint = m_startPoint;
}

double ElapsedTimer::progress() {
    const double milliseconds = ElapsedTimer::currentMilliseconds();
    if(m_interval == 0)\
        return 0;
    return (milliseconds - m_checkPoint) / m_interval;
}

ElapsedTimer::time_t ElapsedTimer::currentMilliseconds(){
    timeb tb;
    ftime(&tb);
    unsigned nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}
}
