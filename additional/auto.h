#ifndef AUTO_H
#define AUTO_H

#include "vector.h"

class Auto : public Object {
private:
    void *pointer = nullptr;
    unsigned long long integerValue = 0;
    double doubleValue = 0.0;
    Vector vectorValue = Vector();

public:
    Auto();
    Auto(void *value);
    Auto(int value);
    Auto(unsigned long value);
    Auto(double value);
    Auto(Vector value);

    int toInt32();
    long toInt64();
    unsigned int toUint32();
    unsigned long toUint64();

    double toDouble();
    Vector toVector();
    void * toOthers();
};

#endif // AUTO_H
