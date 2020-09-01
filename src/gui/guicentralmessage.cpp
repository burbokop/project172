#include "guicentralmessage.h"

#include <src/engine/graphics/abstractrenderer.h>

const unsigned GUICentralMessage::DEFAULT_FLASHING_INTERVAL = 500;



GUICentralMessage::GUICentralMessage(std::string label) : GUIMenuElement (label) {}

GUICentralMessage::GUICentralMessage(IInformative *informative) : GUIMenuElement (informative) {}

void GUICentralMessage::start(int flashesRemains, unsigned interval) {
    this->flashesRemains = flashesRemains;
    this->flashingTimer = new e172::ElapsedTimer(interval);
    this->flashingTimer->reset();
    this->visible = true;
}

void GUICentralMessage::render(e172::AbstractRenderer *renderer) {
    if(visible) {
        e172::Vector center = renderer->resolution() / 2.0;
        std::string string = getTitle();

        const auto half_size = renderer->drawString(string, center, 0xFFBA73, e172::TextFormat::AlignCenter) / 2;
        renderer->drawRect(center - half_size - e172::Vector(16, 16), center + half_size + e172::Vector(16, 24), 0xFFBA73);
    }

    if(flashingTimer && flashingTimer->check()) {
        visible = !visible;
        if(flashesRemains <= 0) {
            flashingTimer = nullptr;
            visible = false;
        }
        flashesRemains--;
    }
}
