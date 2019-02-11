#ifndef GUIFLOATINGMESSAGE_H
#define GUIFLOATINGMESSAGE_H

#include "guilabel.h"

class GUIFloatingMessage : public GUILabel {
protected:
    static const Uint32 DEFAULT_COLOR;
    static const int DEFAULT_FONT_SIZE;


    Unit *parent;
    int horisontalOffset = 0;

public:
    GUIFloatingMessage(Unit *parent);
    GUIFloatingMessage(Unit *parent, std::string label);
    GUIFloatingMessage(Unit *parent, IInformative *informative);


    // GUIElement interface
public:
    void render(Renderer *renderer, Event *event);
};

#endif // GUIFLOATINGMESSAGE_H
