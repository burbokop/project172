#include "guielement.h"

Controller *GUIElement::controller() const {
    return m_controller;
}

int GUIElement::margin() const {
    return m_margin;
}

void GUIElement::setMargin(int margin) {
    m_margin = margin;
}

GUIElement::GUIElement() {}

GUIElement::GUIElement(Controller *controller) {
    m_controller = controller;
}

GUIElement::~GUIElement() {
}
