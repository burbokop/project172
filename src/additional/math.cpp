#include <math.h>


#include "math.h"


int Math::map(int value, int inMin, int inMax, int outMin, int outMax) {
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

long Math::map(long value, long inMin, long inMax, long outMin, long outMax) {
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

double Math::map(double value, double inMin, double inMax, double outMin, double outMax) {
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

bool Math::cmpf(float a, float b, float epsilon) {
    return (fabsf(a - b) < epsilon);
}

bool Math::cmpd(double a, double b, double epsilon) {
    return (fabs(a - b) < epsilon);
}
