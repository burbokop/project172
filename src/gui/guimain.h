#ifndef GUIMAIN_H
#define GUIMAIN_H


#include "gui/guistack.h"
#include "gui/guicentralmessage.h"
#include "gui/guifloatingmessage.h"
#include "gui/guiminimap.h"

#include "guidebugvalueinfo.h"


class GUIMain : public GUIElement {
private:
    static const unsigned FLOATING_LIFE_TIME;

    GUIStack *menu = nullptr;
    GUICentralMessage *centralMessage = nullptr;
    GUIFloatingMessage *floatingMessage = nullptr;
    GUIDebugValueInfo *debugValueInfo = nullptr;
    GUIMiniMap *miniMap = nullptr;
    e172::ElapsedTimer floatingMessageLifeTimer = e172::ElapsedTimer(FLOATING_LIFE_TIME);

public:
    GUIMain();
    GUIMain(Controller *player);


    void addFloatingMessage(Unit *unit, std::string message);
    void addBlushingFloatingMessage(Unit *unit, int value);

    void setMenu(GUIStack *value);
    void setMessage(GUICentralMessage *value);
    void setMiniMap(GUIMiniMap *value);
    void setDebugValueInfo(GUIDebugValueInfo *value);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUIMAIN_H
