#include "guifloatingmessage.h"

const Uint32 GUIFloatingMessage::DEFAULT_COLOR = 0xFFEF40;
const int GUIFloatingMessage::DEFAULT_FONT_SIZE = 14;


GUIFloatingMessage::GUIFloatingMessage(Unit *parent) : GUILabel(nullptr) {
    this->parent = parent;
}

GUIFloatingMessage::GUIFloatingMessage(Unit *parent, std::string label) : GUILabel (nullptr, label) {
    this->parent = parent;
}

GUIFloatingMessage::GUIFloatingMessage(Unit *parent, IInformative *informative) : GUILabel (nullptr, informative) {
    this->parent = parent;
}

void GUIFloatingMessage::render(Renderer *renderer, Event *event) {
    UNUSED(event);
    renderer->stringCentered(getTitle(), parent->getPosition() + renderer->getOffset() + Vector(0, horisontalOffset), DEFAULT_COLOR, DEFAULT_FONT_SIZE);
    horisontalOffset--;
}
