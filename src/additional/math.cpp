#include <math.h>


#include "math.h"

#define INV_PI 180 / M_PI
#define NOTINV_PI M_PI / 180


std::map<double, double> Math::sinCache;
std::map<double, double> Math::cosCache;

std::map<double, double> Math::arccosCache;
std::map<double, double> Math::sqrtCache;

const double Math::ACOS_ROUND_LEVEL = 1000;
const double Math::ACOS_INV_ROUND_LEVEL = 1 / ACOS_ROUND_LEVEL;

const double Math::SQRT_ROUND_LEVEL = 1000;
const double Math::SQRT_INV_ROUND_LEVEL = 1 / SQRT_ROUND_LEVEL;


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

#include <iostream>
double Math::sin(double angle) {
    //std::cout << "SQRT: " << sqrtCache.size() << " ACOS: " << arccosCache.size() << " SIN: " << sinCache.size() << " COS: " << cosCache.size() << "\n";

    if(sinCache.find(angle) == sinCache.end()) {
        const double result = std::sin(angle);
        sinCache[angle] = result;
        return result;
    } else {
        return sinCache[angle];
    }
}


double Math::cos(double angle) {
    //std::cout << "SQRT: " << sqrtCache.size() << " ACOS: " << arccosCache.size() << " SIN: " << sinCache.size() << " COS: " << cosCache.size() << "\n";

    if(cosCache.find(angle) == cosCache.end()) {
        const double result = std::cos(angle);
        cosCache[angle] = result;
        return result;
    } else {
        return cosCache[angle];
    }
}

double Math::acos(double value) {
    //std::cout << "SQRT: " << sqrtCache.size() << " ACOS: " << arccosCache.size() << " SIN: " << sinCache.size() << " COS: " << cosCache.size() << "\n";

    value = std::round(value * ACOS_ROUND_LEVEL) * ACOS_INV_ROUND_LEVEL;

    if(arccosCache.find(value) == arccosCache.end()) {
        const double result = std::acos(value);
        arccosCache[value] = result;
        return result;
    } else {
        return arccosCache[value];
    }
}

double Math::sqrt(double value) {
    //std::cout << "SQRT: " << sqrtCache.size() << " ACOS: " << arccosCache.size() << " SIN: " << sinCache.size() << " COS: " << cosCache.size() << "\n";

    value = std::round(value * SQRT_ROUND_LEVEL) * SQRT_INV_ROUND_LEVEL;

    if(sqrtCache.find(value) == sqrtCache.end()) {
        const double result = std::sqrt(value);
        sqrtCache[value] = result;
        return result;
    } else {
        return sqrtCache[value];
    }
}
