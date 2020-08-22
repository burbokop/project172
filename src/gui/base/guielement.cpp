#include "guielement.h"

int GUIElement::margin() const {
    return m_margin;
}

void GUIElement::setMargin(int margin) {
    m_margin = margin;
}

GUIElement::GUIElement() {}
