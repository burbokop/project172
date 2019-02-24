#include "auto.h"


const uint8_t Auto::TYPE_INT32 = 0;
const uint8_t Auto::TYPE_INT64 = 1;
const uint8_t Auto::TYPE_UINT32 = 2;
const uint8_t Auto::TYPE_UINT64 = 3;
const uint8_t Auto::TYPE_DOUBLE = 4;

const uint8_t Auto::TYPE_VECTOR = 5;
const uint8_t Auto::TYPE_OBJECT = 6;


Auto::Auto() : Object() {

}

Auto::Auto(void *value) : Object() {
    pointer = reinterpret_cast<uintptr_t>(value);
    type = TYPE_OBJECT;
}

Auto::Auto(int value) : Object() {
    pointer = static_cast<uintptr_t>(value);
    type = TYPE_INT32;
}

Auto::Auto(long value) {
    pointer = static_cast<uintptr_t>(value);
    type = TYPE_INT64;
}

Auto::Auto(unsigned int value) {
    pointer = static_cast<uintptr_t>(value);
    type = TYPE_UINT32;
}

Auto::Auto(unsigned long value) {
    pointer = value;
    type = TYPE_UINT64;
}

Auto::Auto(double value) : Object() {
    pointer = verbatim_cast<double, uintptr_t>(value);
    type = TYPE_DOUBLE;
}

Auto::Auto(Vector value) : Object() {
    vectorValue = value;
    type = TYPE_VECTOR;
}

int Auto::toInt32() {
    if(type == TYPE_DOUBLE) {
        return static_cast<int>(toDouble());
    } else {
        return static_cast<int>(pointer);
    }
}

long Auto::toInt64() {
    if(type == TYPE_DOUBLE) {
        return static_cast<long>(toDouble());
    } else {
        return static_cast<long>(pointer);
    }
}

unsigned int Auto::toUint32() {
    if(type == TYPE_DOUBLE) {
        return static_cast<unsigned int>(toDouble());
    } else {
        return static_cast<unsigned int>(pointer);
    }
}

unsigned long Auto::toUint64() {
    if(type == TYPE_DOUBLE) {
        return static_cast<unsigned long>(toDouble());
    } else {
        return static_cast<unsigned long>(pointer);
    }
}

double Auto::toDouble() {
    return verbatim_cast<uintptr_t, double>(pointer);
}

Vector Auto::toVector() {
    return vectorValue;
}

void *Auto::toObject() {
    return reinterpret_cast<void*>(pointer);
}

bool Auto::isInt32() {
    return type == TYPE_INT32;
}

bool Auto::isInt64() {
    return type == TYPE_INT64;
}

bool Auto::isUint32() {
    return type == TYPE_UINT32;
}

bool Auto::isUint64() {
    return type == TYPE_UINT64;
}

bool Auto::isDouble() {
    return type == TYPE_DOUBLE;
}

bool Auto::isNumber() {
    return type <= TYPE_DOUBLE;
}

bool Auto::isVector() {
    return type == TYPE_VECTOR;
}

bool Auto::isObject() {
    return type == TYPE_OBJECT;
}

std::string Auto::getType() const {
    return "gogadoda";
}
