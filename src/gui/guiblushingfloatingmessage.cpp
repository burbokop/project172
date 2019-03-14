#include "guiblushingfloatingmessage.h"

#include "additional/math.h"
#include "time/time.h"


GUIBlushingFloatingMessage::GUIBlushingFloatingMessage(Unit *parent) : GUIFloatingMessage (parent) {
}

GUIBlushingFloatingMessage::GUIBlushingFloatingMessage(Unit *parent, int value) : GUIFloatingMessage (parent, std::to_string(value)) {
    this->value = value;
}

GUIBlushingFloatingMessage::GUIBlushingFloatingMessage(Unit *parent, IInformative *informative) : GUIFloatingMessage(parent, informative) {
}


void GUIBlushingFloatingMessage::render(Renderer *renderer) {
    Uint32 color
        = value < 0
        ? 0xff0000
        : 0xff0000 | static_cast<Uint32>(Math::map(value, 0, 80, 0, 0xff) << 8);

    renderer->stringCentered(getTitle(), parent->getPosition() + renderer->getOffset() + Vector(0.0, horisontalOffset), color, DEFAULT_FONT_SIZE);

    //tick/-/-/-/-/
    horisontalOffset -= Time::getDeltaTime() * DEFAULT_FLOATING_SPEED;
    //tick/-/-/-/-/
}
