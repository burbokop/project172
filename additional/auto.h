#ifndef AUTO_H
#define AUTO_H

#include <cstdint>

#include "vector.h"

class Auto : public Object {
private:
    static const uint8_t TYPE_INT32;
    static const uint8_t TYPE_INT64;
    static const uint8_t TYPE_UINT32;
    static const uint8_t TYPE_UINT64;
    static const uint8_t TYPE_DOUBLE;

    static const uint8_t TYPE_VECTOR;
    static const uint8_t TYPE_OBJECT;

    uint8_t type;

    uintptr_t pointer = 0;
    double doubleValue = 0.0;
    Vector vectorValue = Vector();

public:
    Auto();
    Auto(void *value);
    Auto(int value);
    Auto(long value);
    Auto(unsigned int value);
    Auto(unsigned long value);
    Auto(double value);
    Auto(Vector value);

    int toInt32();
    long toInt64();
    unsigned int toUint32();
    unsigned long toUint64();    

    double toDouble();
    Vector toVector();
    void * toObject();

    bool isInt32();
    bool isInt64();
    bool isUint32();
    bool isUint64();
    bool isDouble();
    bool isNumber();

    bool isVector();
    bool isObject();
};

#endif // AUTO_H
