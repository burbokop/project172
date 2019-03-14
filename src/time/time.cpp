#include "time.h"


std::chrono::high_resolution_clock::time_point Time::lastTimePoint = std::chrono::high_resolution_clock::now();

double Time::deltaTime = 0.0;
double Time::globalTimeSpead = 1.0;

int64_t Time::calculateDuration() {
    std::chrono::high_resolution_clock::time_point currentTimePoint = std::chrono::high_resolution_clock::now();
    int64_t microseconds = std::chrono::duration_cast<std::chrono::microseconds>(currentTimePoint - lastTimePoint).count();
    lastTimePoint = currentTimePoint;
    return microseconds;
}

void Time::setGlobalTimeSpead(double value) {
    globalTimeSpead = value;
}

double Time::getDeltaTime() {
    return deltaTime * globalTimeSpead;
}

void Time::update() {
    deltaTime = calculateDuration() * 0.000001;
}
