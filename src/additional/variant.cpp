#include "variant.h"


const unsigned Variant::TYPE_INT32 = 0;
const unsigned Variant::TYPE_INT64 = 1;
const unsigned Variant::TYPE_UINT32 = 2;
const unsigned Variant::TYPE_UINT64 = 3;
const unsigned Variant::TYPE_FLOAT32 = 5;
const unsigned Variant::TYPE_FLOAT64 = 6;

const unsigned Variant::TYPE_UNDEFINED = 7;

const unsigned Variant::TYPE_VECTOR = 8;
const unsigned Variant::TYPE_OBJECT = 9;

Variant::VariantUnion::VariantUnion() {

}

Variant::Variant() : Object() {
    type = TYPE_UNDEFINED;
}

Variant::Variant(signed value) : Object() {
    data.number = value;
    type = TYPE_INT32;
}

Variant::Variant(signed long value) {
    data.number = value;
    type = TYPE_INT32;
}

Variant::Variant(signed long long value) {
    data.number = value;
    type = TYPE_INT64;
}

Variant::Variant(unsigned value) {
    data.number = value;
    type = TYPE_UINT32;
}

Variant::Variant(unsigned long value) {
    data.number = value;
    type = TYPE_UINT32;
}

Variant::Variant(unsigned long long value) {
    data.number = value;
    type = TYPE_UINT64;
}

Variant::Variant(float value) : Object() {
    data.number = static_cast<double>(value);
    type = TYPE_FLOAT32;
}

Variant::Variant(double value) : Object() {
    data.number = value;
    type = TYPE_FLOAT64;
}

Variant::Variant(void *value) : Object() {
    data.ptr = value;
    type = TYPE_OBJECT;
}

Variant::Variant(Vector value) : Object() {
    data.vector = value;
    type = TYPE_VECTOR;
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

Vector Variant::toVector() {
    return data.vector;
}

void *Variant::toObject() {
    return data.ptr;
}

bool Variant::isInt32() {
    return type == TYPE_INT32;
}

bool Variant::isInt64() {
    return type == TYPE_INT64;
}

bool Variant::isUint32() {
    return type == TYPE_UINT32;
}

bool Variant::isUint64() {
    return type == TYPE_UINT64;
}

bool Variant::isFloat32() {
    return type == TYPE_FLOAT32;
}

bool Variant::isFloat64() {
    return type == TYPE_FLOAT64;
}

bool Variant::isNumber() {
    return type < TYPE_UNDEFINED;
}

bool Variant::isUndefined() {
    return type == TYPE_UNDEFINED;
}

bool Variant::isVector() {
    return type == TYPE_VECTOR;
}

bool Variant::isObject() {
    return type == TYPE_OBJECT;
}
