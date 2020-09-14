#include "guimenuelement.h"



e172::Variant GUIMenuElement::modelData() const {
    return m_modelData;
}

void GUIMenuElement::setModelData(const e172::Variant &modelData) {
    m_modelData = modelData;
}

GUIMenuElement::GUIMenuElement() {}

GUIMenuElement::GUIMenuElement(std::string label) {
    this->label = label;
}

GUIMenuElement::GUIMenuElement(IInformative *informative) {
    m_informative = informative;
}

std::string GUIMenuElement::title() {
    return m_informative ? m_informative->info() : label;
}

bool GUIMenuElement::isSelectable() {
    return false;
}

bool GUIMenuElement::hasSubElements() {
    return false;
}

void GUIMenuElement::enter() {}

void GUIMenuElement::proceed(e172::Context *, e172::AbstractEventHandler *) {}
void GUIMenuElement::render(e172::AbstractRenderer *) {}
