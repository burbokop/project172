#ifndef GUIMAIN_H
#define GUIMAIN_H


#include "guicentralmessage.h"
#include "guifloatingmessage.h"
#include "guiminimap.h"

#include "guidebugvalueinfo.h"

#include <src/gui/base/guielement.h>
#include <src/gui/base/guistack.h>


class GUIMain : public GUIElement {
private:
    static const unsigned FLOATING_LIFE_TIME;

    std::vector<GUIStack*> m_stacks;

    GUICentralMessage *centralMessage = nullptr;
    GUIFloatingMessage *floatingMessage = nullptr;
    GUIDebugValueInfo *debugValueInfo = nullptr;
    GUIMiniMap *miniMap = nullptr;
    e172::ElapsedTimer floatingMessageLifeTimer = e172::ElapsedTimer(FLOATING_LIFE_TIME);

public:
    GUIMain();


    void addFloatingMessage(const e172::ptr<Unit> &unit, std::string message);
    void addBlushingFloatingMessage(const e172::ptr<Unit> &unit, int value);
    void addBlushingFloatingMessage(e172::Context *context, const e172::Variant &value);

    void addStack(GUIStack *value);
    void setMessage(GUICentralMessage *value);
    void setMiniMap(GUIMiniMap *value);
    void setDebugValueInfo(GUIDebugValueInfo *value);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUIMAIN_H
