#ifndef VECTOR_H
#define VECTOR_H

#define RELATIVISTIC_ADDITION_CONSTANT 0.7

#include <sstream>


namespace e172 {

class Vector {
public:
    enum Quarter {
        QUARTER_RIGHT_DOWN = 0,
        QUARTER_LEFT_DOWN,
        QUARTER_LEFT_UP,
        QUARTER_RIGHT_UP
    };
private:
    double m_x;
    double m_y;
public:
    Vector();
    Vector(double x, double y);
    Vector(long x, long y);
    Vector(int x, int y);
    static Vector createByAngle(double module, double angle); //checkpoint
    static Vector createRandom(int max);

    Vector operator+(Vector term) const;
    void operator+=(Vector term);
    Vector operator-(Vector subtrahend) const;
    void operator-=(Vector subtrahend);
    Vector operator*(double multiplier) const;
    void operator*=(double multiplier);
    Vector operator/(double divider) const;
    void operator/=(double divider);


    bool operator==(Vector vector) const;
    bool operator!=(Vector vector) const;

    double operator*(Vector multiplier) const;

    double module() const; //checkpoint
    Vector normalized() const;

    double angle() const; //checkpoint

    Vector relativisticAddition(Vector term, double c) const;
    double tg() const;
    unsigned quarter(unsigned offset = 0) const;
    double map(Vector *destination, double value) const;

    Vector operator+(double term) const;
    Vector operator-(double subtrahend) const;


    int intX() const;
    int intY() const;
    double x() const;
    double y() const;


    friend std::ostream &operator<<(std::ostream &os, const e172::Vector &dt);
};

}
#endif // VECTOR_H
