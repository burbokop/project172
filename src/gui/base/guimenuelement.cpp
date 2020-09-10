#include "guimenuelement.h"



GUIMenuElement::GUIMenuElement() {}

GUIMenuElement::GUIMenuElement(std::string label) {
    this->label = label;
}

GUIMenuElement::GUIMenuElement(IInformative *informative) {
    this->informative = informative;
}

std::string GUIMenuElement::title() {
    return informative ? informative->info() : label;
}

bool GUIMenuElement::isSelectable() {
    return false;
}

bool GUIMenuElement::hasSubElements() {
    return false;
}

void GUIMenuElement::onEnter() {}

void GUIMenuElement::proceed(e172::Context *, e172::AbstractEventHandler *) {}
void GUIMenuElement::render(e172::AbstractRenderer *) {}
