#include "guiblushingfloatingmessage.h"

#include <src/engine/math/math.h>

#include <src/engine/graphics/abstractrenderer.h>


GUIBlushingFloatingMessage::GUIBlushingFloatingMessage(Unit *parent) : GUIFloatingMessage (parent) {
}

GUIBlushingFloatingMessage::GUIBlushingFloatingMessage(Unit *parent, int value) : GUIFloatingMessage (parent, std::to_string(value)) {
    this->value = value;
}

GUIBlushingFloatingMessage::GUIBlushingFloatingMessage(Unit *parent, IInformative *informative) : GUIFloatingMessage(parent, informative) {
}


void GUIBlushingFloatingMessage::render(e172::AbstractRenderer *renderer) {
    uint32_t color
        = value < 0
        ? 0xff0000
        : 0xff0000 | static_cast<uint32_t>(e172::Math::map(value, 0, 80, 0, 0xff) << 8);

    renderer->drawString(
                getTitle(),
                parent->position() + renderer->offset() + e172::Vector(0.0, horisontalOffset()),
                color,
                e172::TextFormat(e172::TextFormat::AlignDefault, DEFAULT_FONT_SIZE)
                );
}
