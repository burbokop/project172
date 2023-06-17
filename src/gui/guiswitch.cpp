#include "guiswitch.h"

namespace proj172::core {

void GUISwitch::enter(e172::Context *) {
    if (m_on != nullptr) {
        if (m_off != nullptr) {
            if (!m_enabled) {
                m_on();
                m_enabled = true;
            } else {
                m_off();
                m_enabled = false;
            }
        } else {
            m_on();
        }
    }
}

} // namespace proj172::core
