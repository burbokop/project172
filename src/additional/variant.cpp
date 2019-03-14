#include "variant.h"





Variant::VariantUnion::VariantUnion() {}

Variant::Variant() : Object() {
    type = UNDEFINED;
}

Variant::Variant(signed value) : Object() {
    data.number = value;
    type = INT32;
}

Variant::Variant(signed long value) {
    data.number = value;
    type = INT32;
}

Variant::Variant(signed long long value) {
    data.number = value;
    type = INT64;
}

Variant::Variant(unsigned value) {
    data.number = value;
    type = UINT32;
}

Variant::Variant(unsigned long value) {
    data.number = value;
    type = UINT32;
}

Variant::Variant(unsigned long long value) {
    data.number = value;
    type = UINT64;
}

Variant::Variant(float value) : Object() {
    data.number = static_cast<double>(value);
    type = FLOAT32;
}

Variant::Variant(double value) : Object() {
    data.number = value;
    type = FLOAT64;
}

Variant::Variant(void *value) : Object() {
    data.ptr = value;
    type = OBJECT;
}

Variant::Variant(Unit *value) {
    data.unit = value;
    type = UNIT;
}

Variant::Variant(Vector value) : Object() {
    data.vector = value;
    type = VECTOR;
}

signed int Variant::toInt32() {
    return static_cast<signed int>(data.number);
}

signed long long Variant::toInt64() {
    return static_cast<signed long long>(data.number);
}

unsigned int Variant::toUint32() {
    return static_cast<unsigned int>(data.number);
}


unsigned long long Variant::toUint64() {
    return static_cast<unsigned long long>(data.number);
}

float Variant::toFloat32() {
    return static_cast<float>(data.number);
}

double Variant::toFloat64() {
    return data.number;
}

void *Variant::toObject() {
    return data.ptr;
}

Unit *Variant::toUnit() {
    return data.unit;
}

Vector Variant::toVector() {
    return data.vector;
}

bool Variant::isInt32() {
    return type == INT32;
}

bool Variant::isInt64() {
    return type == INT64;
}

bool Variant::isUint32() {
    return type == UINT32;
}

bool Variant::isUint64() {
    return type == UINT64;
}

bool Variant::isFloat32() {
    return type == FLOAT32;
}

bool Variant::isFloat64() {
    return type == FLOAT64;
}

bool Variant::isNumber() {
    return type < UNDEFINED;
}

bool Variant::isUndefined() {
    return type == UNDEFINED;
}

bool Variant::isObject() {
    return type == OBJECT;
}

bool Variant::isUnit() {
    return type == UNIT;
}

bool Variant::isVector() {
    return type == VECTOR;
}
