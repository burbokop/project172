#ifndef GUIBLUSHINGFLOATINGMESSAGE_H
#define GUIBLUSHINGFLOATINGMESSAGE_H

#include "guifloatingmessage.h"
#include "additional/math.h"

class GUIBlushingFloatingMessage : public GUIFloatingMessage {
int value;

public:
    GUIBlushingFloatingMessage(Unit *parent);
    GUIBlushingFloatingMessage(Unit *parent, int value);
    GUIBlushingFloatingMessage(Unit *parent, IInformative *informative);


    // GUIElement interface
public:
    void render(Renderer *renderer, Event *event);
};

#endif // GUIBLUSHINGFLOATINGMESSAGE_H
