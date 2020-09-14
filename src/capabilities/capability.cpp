#include "capability.h"

Unit *Capability::parentUnit() const {
    return m_parentUnit;
}

bool Capability::setParentUnit(Unit *parent) {
    if(parent != nullptr) {
        if(m_parentUnit == nullptr) {
            m_parentUnit = parent;
            return true;
        }
    } else {
        m_parentUnit = nullptr;
        return true;
    }
    return false;
}
