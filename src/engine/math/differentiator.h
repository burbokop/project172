#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include <src/engine/time/deltatimecalculator.h>


class Differentiator {
    e172::DeltaTimeCalculator c;
    double last;
    bool hasLast = false;

    double derivative = 0;
public:
    Differentiator();
    double proceed(double value);
};

#endif // DIFFERENTIATOR_H
