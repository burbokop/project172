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

    static const double Pi;

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


    static double constrainRadians(double value);
    static double constrainDegrees(double value);
    static bool radiansDirection(double dstAngle, double angle);
    static double radiansDistance(double dstAngle, double angle);
    static double radiansDifference(double angle1, double angle2);
    static double degreesDistance(double angle1, double angle2);
    static double degreesDifference(double angle1, double angle2);

    static double map(double value, double inMin, double inMax, double outMin, double outMax);

    struct null_float_t {};
    static constexpr null_float_t null = null_float_t();

    friend bool operator ==(double value, const null_float_t&) { return Math::cmpf(value, 0); }
    friend bool operator ==(const null_float_t&, double value) { return Math::cmpf(value, 0); }
    friend bool operator !=(double value, const null_float_t&) { return !Math::cmpf(value, 0); }
    friend bool operator !=(const null_float_t&, double value) { return !Math::cmpf(value, 0); }

};



}

#endif // MATH_H
