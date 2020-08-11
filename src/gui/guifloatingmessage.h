#ifndef GUIFLOATINGMESSAGE_H
#define GUIFLOATINGMESSAGE_H


#include "gui/guimenuelement.h"


class GUIFloatingMessage : public GUIMenuElement {
    double m_horisontalOffset = 0;
protected:
    static const uint32_t DEFAULT_COLOR;
    static const int DEFAULT_FONT_SIZE;
    static const double DEFAULT_FLOATING_SPEED;


    Unit *parent = nullptr;

public:
    GUIFloatingMessage(Unit *parent);
    GUIFloatingMessage(Unit *parent, std::string label);
    GUIFloatingMessage(Unit *parent, IInformative *informative);


    // GUIElement interface
public:
    virtual void render(e172::AbstractRenderer *renderer) override;
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    double horisontalOffset() const;
};

#endif // GUIFLOATINGMESSAGE_H
