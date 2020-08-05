#include "kuniversalqueue.h"

int KUniversalQueue::capacity() const {
    return m_capacity;
}

KUniversalQueue::KUniversalQueue(int capacity) {
    m_capacity = capacity;
}

KUniversalQueue::~KUniversalQueue() {
    for(auto b : buffers) {
        delete b.second;
    }
}
