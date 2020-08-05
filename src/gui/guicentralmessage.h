#ifndef GUICENTRALMESSAGE_H
#define GUICENTRALMESSAGE_H


#include "gui/guimenuelement.h"
#include "time/timer.h"


class GUICentralMessage : public GUIMenuElement {
private:
    static const unsigned DEFAULT_FLASHING_INTERVAL;

    Timer *flashingTimer = nullptr;
    bool visible;
    int flashesRemains;

public:
    GUICentralMessage(Controller *player);
    GUICentralMessage(Controller *player, std::string label);
    GUICentralMessage(Controller *player, IInformative *informative);

    void start(int flashesRemains, unsigned interval = DEFAULT_FLASHING_INTERVAL);

    // GUIElement interface
public:
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUICENTRALMESSAGE_H
