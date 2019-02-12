#include "guielement.h"

GUIElement::GUIElement() {}

GUIElement::GUIElement(Controller *player) {
    this->player = player;
}

GUIElement::~GUIElement() {
}
