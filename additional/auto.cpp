#include "auto.h"


Auto::Auto() : Object() {

}

Auto::Auto(void *value) : Object() {
    pointer = reinterpret_cast<uintptr_t>(value);
}

Auto::Auto(int value) : Object() {
    pointer = static_cast<uintptr_t>(value);
}

Auto::Auto(unsigned long value) {
    pointer = value;
}

Auto::Auto(double value) : Object() {
    doubleValue = value;
}

Auto::Auto(Vector value) : Object() {
    vectorValue = value;
}

int Auto::toInt32() {
    return static_cast<int>(pointer);
}

long Auto::toInt64() {
    return static_cast<long>(pointer);
}

unsigned int Auto::toUint32() {
    return static_cast<unsigned int>(pointer);
}

unsigned long Auto::toUint64() {
    return pointer;
}

double Auto::toDouble() {
    return doubleValue;
}

Vector Auto::toVector() {
    return vectorValue;
}

void *Auto::toOthers() {
    return reinterpret_cast<void*>(pointer);
}
