#include "guibutton.h"


GUIButton::GUIButton(const std::string &title, const std::function<void(Controller *, const e172::Variant &)> &clicked) : GUIMenuElement(title) {
    m_clicked2 = clicked;
}

GUIButton::GUIButton(const std::string &title, const std::function<void (const e172::Variant &)> &clicked) : GUIMenuElement(title) {
    m_clicked = clicked;
}

bool GUIButton::isSelectable() {
    return true;
}

void GUIButton::enter() {
    if(m_clicked) {
        m_clicked(modelData());
    } else if(m_clicked2) {
        m_clicked2(controller(), modelData());
    }
}
