#include "guibutton.h"


GUIButton::GUIButton(const std::string &title, const std::function<void (const e172::Variant &)> &clicked) : GUIMenuElement(title) {
    m_clicked = clicked;
}

bool GUIButton::isSelectable() {
    return true;
}

void GUIButton::enter() {
    m_clicked(modelData());
}
