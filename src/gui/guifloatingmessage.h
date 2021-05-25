#ifndef GUIFLOATINGMESSAGE_H
#define GUIFLOATINGMESSAGE_H

#include <src/gui/base/guimenuelement.h>

#include <src/utility/ptr.h>

class Unit;


class GUIFloatingMessage : public GUIMenuElement {
    double m_horisontalOffset = 0;
protected:
    static const uint32_t DEFAULT_COLOR;
    static const int DEFAULT_FONT_SIZE;
    static const double DEFAULT_FLOATING_SPEED;


    e172::ptr<Unit> m_parent;

public:
    GUIFloatingMessage(const e172::ptr<Unit> &parent);
    GUIFloatingMessage(const e172::ptr<Unit> &parent, std::string label);
    GUIFloatingMessage(const e172::ptr<Unit> &parent, IInformative *informative);


    // GUIElement interface
public:
    virtual void render(e172::AbstractRenderer *renderer) override;
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    double horisontalOffset() const;
};

#endif // GUIFLOATINGMESSAGE_H
