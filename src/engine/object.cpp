#include "object.h"

#include <cstdint>
#include "objectregistry.h"



bool e172::Object::liveInHeap() const {
    return m_liveInHeap;
}

int *heap_example = new int();


e172::Object::Object() {
    int stack_example;

    if(((void*)this < &stack_example) == ((void*)heap_example < (void*)&stack_example)) {
        m_liveInHeap = true;
    } else {
        m_liveInHeap = false;
    }
}

e172::Object::~Object() {}


bool e172::operator ==(e172::Object *object, const e172::alive_t &) {
    return ObjectRegistry::exists(object);
}

bool e172::operator ==(const e172::alive_t &, e172::Object *object) {
    return ObjectRegistry::exists(object);
}

bool e172::operator !=(e172::Object *object, const e172::alive_t &) {
    return ObjectRegistry::isDeleted(object);
}

bool e172::operator !=(const e172::alive_t &, e172::Object *object) {
    return ObjectRegistry::isDeleted(object);
}
