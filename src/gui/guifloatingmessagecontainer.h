#ifndef GUIFLOATINGMESSAGECONTAINER_H
#define GUIFLOATINGMESSAGECONTAINER_H

#include "guicentralmessage.h"
#include "guifloatingmessage.h"
#include "guiminimap.h"
#include "guidebugvalueinfo.h"

#include <src/gui/base/guicontainer.h>

//DEPRECATED (use GUIContainer and create new Floating)
class GUIFloatingMessageContainer : public GUIElement {
private:
    static const unsigned FLOATING_LIFE_TIME;

    GUICentralMessage *centralMessage = nullptr;
    GUIFloatingMessage *floatingMessage = nullptr;

    e172::ElapsedTimer floatingMessageLifeTimer = e172::ElapsedTimer(FLOATING_LIFE_TIME);

public:
    GUIFloatingMessageContainer();

    void addFloatingMessage(const e172::ptr<Unit> &unit, std::string message);
    void addBlushingFloatingMessage(const e172::ptr<Unit> &unit, int value);
    void addCommonFloatingMessage(e172::Context *context, const e172::Variant &value);

    void setMessage(GUICentralMessage *value);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
};

#endif // GUIFLOATINGMESSAGECONTAINER_H
