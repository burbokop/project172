#ifndef MATH_H
#define MATH_H

#include <map>


namespace e172 {

class Math {
private:
    static std::map<double, double> sinCache;
    static std::map<double, double> cosCache;

    static std::map<double, double> arccosCache;
    static std::map<double, double> sqrtCache;

    static const double ACOS_ROUND_LEVEL;
    static const double ACOS_INV_ROUND_LEVEL;

    static const double SQRT_ROUND_LEVEL;
    static const double SQRT_INV_ROUND_LEVEL;


public:
    template<typename A, typename B, typename C, typename D, typename E>
    static int map(const A &value, const B &inMin, const C &inMax, const D &outMin, const E &outMax) {
        return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    }

    static bool cmpf(float a, float b, float epsilon = 0.00005f);
    static bool cmpf(double a, double b, double epsilon = 0.00005);

    static double sin(double angle);
    static double cos(double angle);
    static double acos(double value);
    static double sqrt(double value);


    static double constrainAngle(double value);
};

}

#endif // MATH_H
