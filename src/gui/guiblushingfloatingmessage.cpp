#include "guiblushingfloatingmessage.h"

#include "time/time.h"

#include <src/engine/math/math.h>


GUIBlushingFloatingMessage::GUIBlushingFloatingMessage(Unit *parent) : GUIFloatingMessage (parent) {
}

GUIBlushingFloatingMessage::GUIBlushingFloatingMessage(Unit *parent, int value) : GUIFloatingMessage (parent, std::to_string(value)) {
    this->value = value;
}

GUIBlushingFloatingMessage::GUIBlushingFloatingMessage(Unit *parent, IInformative *informative) : GUIFloatingMessage(parent, informative) {
}


void GUIBlushingFloatingMessage::render(e172::AbstractRenderer *renderer) {
    Uint32 color
        = value < 0
        ? 0xff0000
        : 0xff0000 | static_cast<Uint32>(e172::Math::map(value, 0, 80, 0, 0xff) << 8);

    renderer->drawString(
                getTitle(),
                parent->getPosition() + renderer->offset() + e172::Vector(0.0, horisontalOffset),
                color,
                e172::TextFormat(e172::TextFormat::AlignDefault, DEFAULT_FONT_SIZE)
                );

    //tick/-/-/-/-/
    horisontalOffset -= Time::getDeltaTime() * DEFAULT_FLOATING_SPEED;
    //tick/-/-/-/-/
}
