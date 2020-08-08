#include "capability.h"

Unit *Capability::parent() const
{
    return m_parent;
}

bool Capability::setParent(Unit *parent) {
    if(this->m_parent == nullptr) {
        this->m_parent = parent;
        return true;
    }
    return false;
}

void Capability::unsetParent() {
    this->m_parent = nullptr;
}
