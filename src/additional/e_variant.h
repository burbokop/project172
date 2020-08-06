#ifndef AUTO_H
#define AUTO_H

#include <cstdint>

#include <src/engine/math/vector.h>
#include "object.h"

class Unit;

class Variant : public Object {
private:
    enum Type {
        INT32,
        INT64,
        UINT32,
        UINT64,
        FLOAT32,
        FLOAT64,

        UNDEFINED,

        OBJECT,
        UNIT,
        Vector,
    } type = UNDEFINED;


    union VariantUnion {
        VariantUnion();
        double number;
        void *ptr;
        Unit *unit;
        e172::Vector vector;
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
    Variant(Unit *value);
    Variant(e172::Vector value);

    signed int toInt32();
    signed long long toInt64();
    unsigned int toUint32();
    unsigned long long toUint64();
    float toFloat32();
    double toFloat64();

    void *toObject();
    Unit *toUnit();
    e172::Vector toVector();


    bool isInt32();
    bool isInt64();
    bool isUint32();
    bool isUint64();
    bool isFloat32();
    bool isFloat64();
    bool isNumber();

    bool isUndefined();
    bool isObject();
    bool isUnit();
    bool isVector();
};

#endif // AUTO_H
