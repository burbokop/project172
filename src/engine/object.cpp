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

e172::Object::LifeInfo e172::Object::lifeInfo() const {
    LifeInfo lifeInfo;
    lifeInfo.m_data = m_lifeInfoData;
    return lifeInfo;
}

e172::Object::~Object() {
    *m_lifeInfoData = false;
}
