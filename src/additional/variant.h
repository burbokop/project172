#ifndef AUTO_H
#define AUTO_H

#include <cstdint>

#include "additional/vector.h"
#include "object.h"


class Variant : public Object {
private:
    static const unsigned TYPE_INT32;
    static const unsigned TYPE_INT64;
    static const unsigned TYPE_UINT32;
    static const unsigned TYPE_UINT64;
    static const unsigned TYPE_FLOAT32;
    static const unsigned TYPE_FLOAT64;

    static const unsigned TYPE_UNDEFINED;

    static const unsigned TYPE_VECTOR;
    static const unsigned TYPE_OBJECT;

    unsigned type;

    union VariantUnion {
        VariantUnion();
        double number;
        void *ptr;
        Vector vector;
    } data;

public:
    Variant();
    Variant(signed value);
    Variant(signed long value);
    Variant(signed long long value);
    Variant(unsigned value);
    Variant(unsigned long value);
    Variant(unsigned long long value);
    Variant(float value);
    Variant(double value);

    Variant(void *value);
    Variant(Vector value);

    signed int toInt32();
    signed long long toInt64();
    unsigned int toUint32();
    unsigned long long toUint64();

    float toFloat32();
    double toFloat64();
    Vector toVector();
    void *toObject();

    bool isInt32();
    bool isInt64();
    bool isUint32();
    bool isUint64();
    bool isFloat32();
    bool isFloat64();
    bool isNumber();

    bool isUndefined();
    bool isVector();
    bool isObject();
};

#endif // AUTO_H
