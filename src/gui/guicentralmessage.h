#ifndef GUICENTRALMESSAGE_H
#define GUICENTRALMESSAGE_H

#include <gui/base/guimenuelement.h>






class GUICentralMessage : public GUIMenuElement {
private:
    static const unsigned DEFAULT_FLASHING_INTERVAL;

    e172::ElapsedTimer *flashingTimer = nullptr;
    bool visible;
    int flashesRemains;

public:
    GUICentralMessage(std::string label);
    GUICentralMessage(IInformative *informative);

    void start(int flashesRemains, unsigned interval = DEFAULT_FLASHING_INTERVAL);

    // GUIElement interface
public:
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUICENTRALMESSAGE_H
