#include "guifloatingmessage.h"

#include <src/graphics/abstractrenderer.h>
#include <src/units/unit.h>
#include <src/context.h>

const uint32_t GUIFloatingMessage::DEFAULT_COLOR = 0xFFEF40;
const int GUIFloatingMessage::DEFAULT_FONT_SIZE = 14;
const double GUIFloatingMessage::DEFAULT_FLOATING_SPEED = 30.0;

double GUIFloatingMessage::horisontalOffset() const
{
    return m_horisontalOffset;
}

GUIFloatingMessage::GUIFloatingMessage(const e172::ptr<Unit> &parent) : GUIMenuElement(nullptr) {
    this->parent = parent;
}

GUIFloatingMessage::GUIFloatingMessage(const e172::ptr<Unit> &parent, std::string label) : GUIMenuElement (label) {
    this->parent = parent;
}

GUIFloatingMessage::GUIFloatingMessage(const e172::ptr<Unit> &parent, IInformative *informative) : GUIMenuElement (informative) {
    this->parent = parent;
}

void GUIFloatingMessage::render(e172::AbstractRenderer *renderer) {
    renderer->drawString(title(), parent->position() + renderer->offset() + e172::Vector(0.0, m_horisontalOffset), DEFAULT_COLOR, e172::TextFormat(e172::TextFormat::AlignCenter, DEFAULT_FONT_SIZE));
}

void GUIFloatingMessage::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    m_horisontalOffset -= context->deltaTime() * DEFAULT_FLOATING_SPEED;
    GUIMenuElement::proceed(context, eventHandler);
}
