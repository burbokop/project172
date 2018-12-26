#ifndef VECTOR_H
#define VECTOR_H

#define RELATIVISTIC_ADDITION_CONSTANT 0.7

#include <object.h>

class Vector : public Object
{
private:
    double x;
    double y;
public:
    Vector();
    Vector(double x, double y);
    Vector(long x, long y);
    Vector(int x, int y);
    static Vector createByAngle(double module, double angle); //checkpoint

    Vector operator+(Vector term);
    void operator+=(Vector term);
    Vector operator-(Vector subtrahend);
    void operator-=(Vector subtrahend);
    Vector operator*(double multiplier);
    void operator*=(double multiplier);

    double operator*(Vector multiplier);

    double module(); //checkpoint
    Vector normalized();

    double angle(); //checkpoint

    Vector relativisticAddition(Vector term, double c);
    double tg();
    char quarter(char offset);
    double map(Vector *destination, double value);

    Vector operator+(double term);
    Vector operator-(double subtrahend);


    int getIntX();
    int getIntY();
    long getLongX();
    long getLongY();
    double getDoubleX();
    double getDoubleY();
};
#endif // VECTOR_H
