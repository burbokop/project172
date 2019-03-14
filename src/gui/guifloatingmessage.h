#ifndef GUIFLOATINGMESSAGE_H
#define GUIFLOATINGMESSAGE_H


#include "gui/guimenuelement.h"


class GUIFloatingMessage : public GUIMenuElement {
protected:
    static const Uint32 DEFAULT_COLOR;
    static const int DEFAULT_FONT_SIZE;
    static const double DEFAULT_FLOATING_SPEED;


    Unit *parent = nullptr;
    double horisontalOffset = 0;

public:
    GUIFloatingMessage(Unit *parent);
    GUIFloatingMessage(Unit *parent, std::string label);
    GUIFloatingMessage(Unit *parent, IInformative *informative);


    // GUIElement interface
public:
    void render(Renderer *renderer);
};

#endif // GUIFLOATINGMESSAGE_H
