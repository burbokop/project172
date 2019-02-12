#ifndef MATH_H
#define MATH_H


class Math {
public:
    static int map(int value, int inMin, int inMax, int outMin, int outMax);
    static long map(long value, long inMin, long inMax, long outMin, long outMax);
    static double map(double value, double inMin, double inMax, double outMin, double outMax);
};

#endif // MATH_H
