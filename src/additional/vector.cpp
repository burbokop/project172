#include <math.h>


#include "vector.h"
#include "math.h"


const unsigned Vector::QUARTER_RIGHT_DOWN = 0;
const unsigned Vector::QUARTER_LEFT_DOWN = 1;
const unsigned Vector::QUARTER_LEFT_UP = 2;
const unsigned Vector::QUARTER_RIGHT_UP = 3;


Vector::Vector() {
    this->x = 0;
    this->y = 0;
}

Vector::Vector(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector::Vector(long x, long y) {
    this->x = static_cast<double>(x);
    this->y = static_cast<double>(y);
}

Vector::Vector(int x, int y) {
    this->x = static_cast<double>(x);
    this->y = static_cast<double>(y);
}

Vector Vector::createByAngle(double module, double angle) {
    return Vector(module * Math::cos(angle), module * Math::sin(angle));
}

Vector Vector::createRandom(int max) {
    return Vector::createByAngle(static_cast<double>(rand() % (max * max)) / max, rand());
}

Vector Vector::operator+(Vector term) {
    return Vector(this->x + term.x, this->y + term.y);
}

void Vector::operator+=(Vector term) {
    this->x += term.x;
    this->y += term.y;
}

Vector Vector::operator-(Vector subtrahend) {
    return Vector(this->x - subtrahend.x, this->y - subtrahend.y);
}

void Vector::operator-=(Vector subtrahend) {
    this->x -= subtrahend.x;
    this->y -= subtrahend.y;
}

Vector Vector::operator*(double multiplier) {
    return Vector(this->x * multiplier, this->y * multiplier);
}

void Vector::operator*=(double multiplier) {
    this->x *= multiplier;
    this->y *= multiplier;
}

Vector Vector::operator/(double divider) {
    return Vector(this->x / divider, this->y / divider);
}

void Vector::operator/=(double divider) {
    this->x /= divider;
    this->y /= divider;
}

bool Vector::operator==(Vector vector) {
    return Math::cmpd(this->x, vector.x) && Math::cmpd(this->y, vector.y);
}

bool Vector::operator!=(Vector vector) {
    return !Math::cmpd(this->x, vector.x) || !Math::cmpd(this->y, vector.y);
}

double Vector::operator*(Vector multiplier) {
    return this->x * multiplier.x + this->y * multiplier.y;
}

double Vector::module() {
    return std::sqrt(this->x * this->x + this->y * this->y);
}

Vector Vector::normalized() {
    double module = this->module();
    if(!Math::cmpd(module, 0)) {
        return Vector(this->x / module, this->y / module);
    } else {
        return Vector();
    }
}

double Vector::angle() {
    double cos = this->normalized() * Vector(1, 0);
    if(this->y >= 0) return Math::acos(cos);
    else return -Math::acos(cos);
}



Vector Vector::relativisticAddition(Vector term, double c) {
    double termModule = term.module();
    if(!Math::cmpd(termModule, 0)) {
        c *= RELATIVISTIC_ADDITION_CONSTANT;
        Vector classicSum = *this + term;

        double thisModule = this->module();
        double classicSumModule = classicSum.module();

        double k = Math::sqrt((1 + thisModule * termModule / (c * c)));
        double u = classicSumModule / k;

        return Vector(u * classicSum.x / classicSumModule, u * classicSum.y / classicSumModule);
    }
    return *this;
}

double Vector::tg() {
    if(!Math::cmpd(this->y, 0)) return -(this->x / this->y);
    return 0.0;
}

unsigned Vector::quarter(unsigned offset) {
    if(this->y >= 0) {
        if(this->x >= 0) {
            return (0 + offset) % 4;
        }
        else {
            return (1 + offset) % 4;
        }
    }
    else {
        if(this->x >= 0) {
            return (3 + offset) % 4;
        }
        else {
            return (2 + offset) % 4;
        }
    }
}

double Vector::map(Vector *destination, double value) {
    double result = 0;
    double kd = destination->y - destination->x;
    double kt = this->y - this->x;

    if(Math::cmpd(kt, 0)) result = value * kd;
    else result = value * kd / kt;

    result += destination->x;

    return result;
}

Vector Vector::operator+(double term) {
    double module = this->module();
    if(module != 0.0) {
        double mul = 1 + term / module;
        return Vector(this->x * mul, this->y * mul);
    }
    return Vector();
}

Vector Vector::operator-(double subtrahend) {
    double module = this->module();
    if(module != 0.0) {
        double mul = 1 - subtrahend / module;
        return Vector(this->x * mul, this->y * mul);
    }
    return Vector();
}

int Vector::getIntX() {
    return static_cast<int>(this->x);
}

int Vector::getIntY() {
    return static_cast<int>(this->y);
}

long Vector::getLongX() {
    return static_cast<long>(this->x);
}

long Vector::getLongY() {
    return static_cast<long>(this->y);
}

double Vector::getDoubleX() {
    return this->x;
}

double Vector::getDoubleY() {
    return this->y;
}

#include <ostream>
std::ostream &operator<<(std::ostream &os, const Vector &dt) {
    os << "Vector(" << std::to_string(dt.x).c_str() << ", " << std::to_string(dt.y).c_str() << ")";
    return os;
}
