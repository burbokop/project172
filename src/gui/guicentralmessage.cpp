#include "guicentralmessage.h"

const unsigned GUICentralMessage::DEFAULT_FLASHING_INTERVAL = 500;


GUICentralMessage::GUICentralMessage(Controller *player) : GUIMenuElement (player) {
}

GUICentralMessage::GUICentralMessage(Controller *player, std::string label) : GUIMenuElement (player, label) {
}

GUICentralMessage::GUICentralMessage(Controller *player, IInformative *informative) : GUIMenuElement (player, informative) {
}

void GUICentralMessage::start(int flashesRemains, unsigned interval) {
    this->flashesRemains = flashesRemains;
    this->flashingTimer = new Timer(interval);
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

    if(flashingTimer && flashingTimer->count()) {
        visible = !visible;
        if(flashesRemains <= 0) {
            flashingTimer = nullptr;
            visible = false;
        }
        flashesRemains--;
    }
}
