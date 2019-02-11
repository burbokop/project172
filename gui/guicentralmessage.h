#ifndef GUICENTRALMESSAGE_H
#define GUICENTRALMESSAGE_H

#include "guilabel.h"

class GUICentralMessage : public GUILabel {
private:
    static const long DEFAULT_FLASHING_INTERVAL;


    Timer *flashingTimer = nullptr;
    bool visible;
    int flashesRemains;

public:
    GUICentralMessage(Controller *player);
    GUICentralMessage(Controller *player, std::string label);
    GUICentralMessage(Controller *player, IInformative *informative);

    void start(int flashesRemains, long interval = DEFAULT_FLASHING_INTERVAL);

    // GUIElement interface
public:
    void render(Renderer *renderer, Event *event);
};

#endif // GUICENTRALMESSAGE_H
