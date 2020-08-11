#include "guimenuelement.h"



GUIMenuElement::GUIMenuElement(Controller *player) : GUIElement (player) {
}

GUIMenuElement::GUIMenuElement(Controller *player, std::string label) : GUIElement (player) {
    this->label = label;
}

GUIMenuElement::GUIMenuElement(Controller *player, IInformative *informative) : GUIElement (player) {
    this->informative = informative;
}

std::string GUIMenuElement::getTitle() {
    return informative ? informative->getInfo() : label;
}

bool GUIMenuElement::isSelectable() {
    return false;
}

bool GUIMenuElement::hasSubElements() {
    return false;
}

void GUIMenuElement::onEnter() {}

void GUIMenuElement::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    UNUSED(context);
    UNUSED(eventHandler);
}

void GUIMenuElement::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}
