#include "guibutton.h"


GUIButton::GUIButton(const std::string &title, const GUIButton::f0 &f) : GUIMenuElement(title) {
    m_f0 = f;
}

GUIButton::GUIButton(const std::string &title, const f1 &f) : GUIMenuElement(title) {
    m_f1 = f;
}

GUIButton::GUIButton(const std::string &title, const GUIButton::f2 &f) : GUIMenuElement(title) {
    m_f2 = f;
}


bool GUIButton::isSelectable() {
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
