#include "object.h"

#include <cstdint>




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

e172::Object::~Object() {

}
