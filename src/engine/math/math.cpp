#include <math.h>


#include "math.h"

#define INV_PI 180 / M_PI
#define NOTINV_PI M_PI / 180


std::map<double, double> e172::Math::sinCache;
std::map<double, double> e172::Math::cosCache;

std::map<double, double> e172::Math::arccosCache;
std::map<double, double> e172::Math::sqrtCache;

const double e172::Math::ACOS_ROUND_LEVEL = 1000;
const double e172::Math::ACOS_INV_ROUND_LEVEL = 1 / ACOS_ROUND_LEVEL;

const double e172::Math::SQRT_ROUND_LEVEL = 1000;
const double e172::Math::SQRT_INV_ROUND_LEVEL = 1 / SQRT_ROUND_LEVEL;




bool e172::Math::cmpf(float a, float b, float epsilon) {
    return (fabsf(a - b) < epsilon);
}

bool e172::Math::cmpd(double a, double b, double epsilon) {
    return (fabs(a - b) < epsilon);
}

#include <iostream>
double e172::Math::sin(double angle) {
    //std::cout << "SQRT: " << sqrtCache.size() << " ACOS: " << arccosCache.size() << " SIN: " << sinCache.size() << " COS: " << cosCache.size() << "\n";

    if(sinCache.find(angle) == sinCache.end()) {
        const double result = std::sin(angle);
        sinCache[angle] = result;
        return result;
    } else {
        return sinCache[angle];
    }
}


double e172::Math::cos(double angle) {
    //std::cout << "SQRT: " << sqrtCache.size() << " ACOS: " << arccosCache.size() << " SIN: " << sinCache.size() << " COS: " << cosCache.size() << "\n";

    if(cosCache.find(angle) == cosCache.end()) {
        const double result = std::cos(angle);
        cosCache[angle] = result;
        return result;
    } else {
        return cosCache[angle];
    }
}

double e172::Math::acos(double value) {
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

double e172::Math::sqrt(double value) {
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

double e172::Math::constrainAngle(double value) {
    const double max = M_PI * 2;
    value = fmod(value, max);
    if (value < 0)
        value += max;
    return value;
}
