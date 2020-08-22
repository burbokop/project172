#include "capability.h"

Unit *Capability::parentUnit() const
{
    return m_parentUnit;
}

bool Capability::setParentUnit(Unit *parent) {
    if(this->m_parentUnit == nullptr) {
        this->m_parentUnit = parent;
        return true;
    }
    return false;
}

void Capability::unsetParentUnit() {
    this->m_parentUnit = nullptr;
}
