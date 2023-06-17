#include "guimenuelement.h"

namespace proj172::core {

e172::Variant GUIMenuElement::modelData() const {
    return m_modelData;
}

void GUIMenuElement::setModelData(const e172::Variant &modelData) {
    m_modelData = modelData;
}

e172::TextFormat GUIMenuElement::textFormat() const {
    return m_textFormat;
}

void GUIMenuElement::setTextFormat(const e172::TextFormat &textFormat) {
    m_textFormat = textFormat;
}

std::string GUIMenuElement::title() {
    return m_informative ? m_informative->info() : m_label;
}

void GUIMenuElement::enter(e172::Context *context) { (void)context; }

void GUIMenuElement::proceed(e172::Context *, e172::EventHandler *) {}
void GUIMenuElement::render(e172::AbstractRenderer *) {}

} // namespace proj172::core
