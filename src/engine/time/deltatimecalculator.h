#ifndef DELTATIMECALCULATOR_H
#define DELTATIMECALCULATOR_H


#include <chrono>
namespace e172 {


class DeltaTimeCalculator {
    typedef std::chrono::high_resolution_clock cl;
    cl::time_point lastTimePoint = cl::now();

    int64_t calculateDuration();

    double m_deltaTime = 0;
    double m_globalTimeSpead = 1;
public:
    DeltaTimeCalculator();
    void update();

    double deltaTime();
    void setGlobalTimeSpead(double value);
};

}
#endif // DELTATIMECALCULATOR_H
