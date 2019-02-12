#include "guicentralmessage.h"

const long GUICentralMessage::DEFAULT_FLASHING_INTERVAL = 500;


GUICentralMessage::GUICentralMessage(Controller *player) : GUILabel (player) {
}

GUICentralMessage::GUICentralMessage(Controller *player, std::string label) : GUILabel (player, label) {
}

GUICentralMessage::GUICentralMessage(Controller *player, IInformative *informative) : GUILabel (player, informative) {
}

void GUICentralMessage::start(int flashesRemains, long interval) {
    this->flashesRemains = flashesRemains;
    this->flashingTimer = new Timer(interval);
    this->flashingTimer->reset();
    this->visible = true;
}

void GUICentralMessage::render(Renderer *renderer, Event *event) {
    UNUSED(event);
    if(visible) {
        Vector center = renderer->getResolution() / 2.0;
        std::string string = getTitle();
        int fontSize = renderer->getResolution().getIntY() / 16;
        Vector offset = renderer->getStringSize(string, fontSize) / 2;
        Vector pos1 = center - offset;
        Vector pos2 = center + offset;

        renderer->string(string, pos1, 0xFFBA73, fontSize);
        renderer->rect(pos1 - Vector(16, 16), pos2 + Vector(16, 24), 0xFFBA73);
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
