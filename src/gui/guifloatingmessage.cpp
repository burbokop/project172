#include "guifloatingmessage.h"

#include "time/time.h"

const Uint32 GUIFloatingMessage::DEFAULT_COLOR = 0xFFEF40;
const int GUIFloatingMessage::DEFAULT_FONT_SIZE = 14;
const double GUIFloatingMessage::DEFAULT_FLOATING_SPEED = 30.0;


GUIFloatingMessage::GUIFloatingMessage(Unit *parent) : GUIMenuElement(nullptr) {
    this->parent = parent;
}

GUIFloatingMessage::GUIFloatingMessage(Unit *parent, std::string label) : GUIMenuElement (nullptr, label) {
    this->parent = parent;
}

GUIFloatingMessage::GUIFloatingMessage(Unit *parent, IInformative *informative) : GUIMenuElement (nullptr, informative) {
    this->parent = parent;
}

void GUIFloatingMessage::render(e172::AbstractRenderer *renderer) {
    renderer->drawString(getTitle(), parent->getPosition() + renderer->offset() + e172::Vector(0.0, horisontalOffset), DEFAULT_COLOR, e172::TextFormat(e172::TextFormat::AlignCenter, DEFAULT_FONT_SIZE));

    //tttt
    horisontalOffset -= Time::getDeltaTime() * DEFAULT_FLOATING_SPEED;
    //tttt
}
