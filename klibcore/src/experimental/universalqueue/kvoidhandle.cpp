#include "kvoidhandle.h"


void *KVoidHandle::data() const {
    return m_data;
}

KVoidHandle::KVoidHandle(std::function<void *()> constructor, std::function<void (void *)> destructor) {
    m_data = constructor();
    this->destructor = destructor;
}

KVoidHandle::~KVoidHandle() {
    destructor(m_data);
}
