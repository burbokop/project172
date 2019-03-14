#ifndef TIME_H
#define TIME_H

#include <chrono>

class Time {
private:
    static std::chrono::high_resolution_clock::time_point lastTimePoint;

    static int64_t calculateDuration();

    static double deltaTime;
    static double globalTimeSpead;
public:
    static void update();

    static double getDeltaTime();
    static void setGlobalTimeSpead(double value);
};

#endif // TIME_H
