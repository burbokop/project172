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
