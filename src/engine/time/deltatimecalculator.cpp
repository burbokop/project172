#include "deltatimecalculator.h"

namespace e172 {

int64_t DeltaTimeCalculator::calculateDuration() {
    std::chrono::high_resolution_clock::time_point currentTimePoint = std::chrono::high_resolution_clock::now();
    int64_t microseconds = std::chrono::duration_cast<std::chrono::microseconds>(currentTimePoint - lastTimePoint).count();
    lastTimePoint = currentTimePoint;
    return microseconds;
}

DeltaTimeCalculator::DeltaTimeCalculator() {}

void DeltaTimeCalculator::setTimeSpead(double value) {
    m_timeSpead = value;
}

double DeltaTimeCalculator::deltaTime() {
    return m_deltaTime;
}

void DeltaTimeCalculator::update() {
    m_deltaTime = calculateDuration() * 0.000001 * m_timeSpead;
}

}
