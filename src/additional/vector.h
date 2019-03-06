#ifndef VECTOR_H
#define VECTOR_H

#define RELATIVISTIC_ADDITION_CONSTANT 0.7

#include <sstream>

class Vector {
public:
    static const unsigned QUARTER_RIGHT_DOWN;
    static const unsigned QUARTER_LEFT_DOWN;
    static const unsigned QUARTER_LEFT_UP;
    static const unsigned QUARTER_RIGHT_UP;

private:
    double x;
    double y;
public:
    Vector();
    Vector(double x, double y);
    Vector(long x, long y);
    Vector(int x, int y);
    static Vector createByAngle(double module, double angle); //checkpoint
    static Vector createRandom(int max);

    Vector operator+(Vector term);
    void operator+=(Vector term);
    Vector operator-(Vector subtrahend);
    void operator-=(Vector subtrahend);
    Vector operator*(double multiplier);
    void operator*=(double multiplier);
    Vector operator/(double divider);
    void operator/=(double divider);


    bool operator==(Vector vector);
    bool operator!=(Vector vector);

    double operator*(Vector multiplier);

    double module(); //checkpoint
    Vector normalized();

    double angle(); //checkpoint

    Vector relativisticAddition(Vector term, double c);
    double tg();
    unsigned quarter(unsigned offset = 0);
    double map(Vector *destination, double value);

    Vector operator+(double term);
    Vector operator-(double subtrahend);


    int getIntX();
    int getIntY();
    long getLongX();
    long getLongY();
    double getDoubleX();
    double getDoubleY();


    friend std::ostream &operator<<(std::ostream &os, const Vector &dt);
};
#endif // VECTOR_H
