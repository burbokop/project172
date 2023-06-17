#include "capability.h"

namespace proj172::core {

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

} // namespace proj172::core
