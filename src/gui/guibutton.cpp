#include "guibutton.h"

namespace proj172::core {

bool GUIButton::isSelectable()
{
    return true;
}

void GUIButton::enter(e172::Context *context) {
    if(m_f0) {
        m_f0(modelData());
    } else if(m_f1) {
        m_f1(controller(), modelData());
    } else if(m_f2) {
        m_f2(context, controller(), modelData());
    }
}

} // namespace proj172::core
