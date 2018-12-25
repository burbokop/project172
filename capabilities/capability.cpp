#include "capability.h"

bool Capability::setParent(Unit *parent) {
    if(this->parent == nullptr) {
        this->parent = parent;
        return true;
    }
    return false;
}

void Capability::unsetParent() {
    this->parent = nullptr;
}
