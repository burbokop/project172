#ifndef GUIBLUSHINGFLOATINGMESSAGE_H
#define GUIBLUSHINGFLOATINGMESSAGE_H


#include "gui/guifloatingmessage.h"


class GUIBlushingFloatingMessage : public GUIFloatingMessage {
private:
    int value;

public:
    GUIBlushingFloatingMessage(Unit *parent);
    GUIBlushingFloatingMessage(Unit *parent, int value);
    GUIBlushingFloatingMessage(Unit *parent, IInformative *informative);


    // GUIElement interface
public:
    void render(Renderer *renderer);
};

#endif // GUIBLUSHINGFLOATINGMESSAGE_H
