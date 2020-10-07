#include "capability.h"

e172::ptr<Unit> Capability::parentUnit() const {
    return m_parentUnit;
}

bool Capability::setParentUnit(const e172::ptr<Unit> &parent) {
    if(parent) {
        if(!m_parentUnit) {
            m_parentUnit = parent;
            return true;
        }
    } else {
        m_parentUnit = nullptr;
        return true;
    }
    return false;
}
