#include "auto.h"


Auto::Auto() : Object() {

}

Auto::Auto(void *value) : Object() {
    pointer = value;
}

Auto::Auto(int value) : Object() {
    integerValue = value;
}

Auto::Auto(unsigned long value) {
    integerValue = value;
}

Auto::Auto(double value) : Object() {
    doubleValue = value;
}

Auto::Auto(Vector value) : Object() {
    vectorValue = value;
}

int Auto::toInt32() {
    return integerValue;
}

long Auto::toInt64() {
    return integerValue;
}

unsigned int Auto::toUint32() {
    return integerValue;
}

unsigned long Auto::toUint64() {
    return integerValue;
}

double Auto::toDouble() {
    return doubleValue;
}

Vector Auto::toVector() {
    return vectorValue;
}

void *Auto::toOthers() {
    return pointer;
}
