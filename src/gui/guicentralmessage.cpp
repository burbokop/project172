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
        int fontSize = renderer->resolution().intY() / 16;
        e172::Vector offset = renderer->getStringSize(string, fontSize) / 2;
        e172::Vector pos1 = center - offset;
        e172::Vector pos2 = center + offset;

        renderer->drawString(string, pos1, 0xFFBA73, fontSize);
        renderer->drawRect(pos1 - e172::Vector(16, 16), pos2 + e172::Vector(16, 24), 0xFFBA73);
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
