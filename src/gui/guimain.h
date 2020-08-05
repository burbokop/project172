#ifndef GUIMAIN_H
#define GUIMAIN_H


#include "gui/guistack.h"
#include "gui/guicentralmessage.h"
#include "gui/guifloatingmessage.h"
#include "gui/guiminimap.h"


class GUIMain : public GUIElement {
private:
    static const unsigned FLOATING_LIFE_TIME;

    GUIStack *menu = nullptr;
    GUICentralMessage *centralMessage = nullptr;
    GUIFloatingMessage *floatingMessage = nullptr;
    GUIMiniMap *miniMap = nullptr;
    Timer floatingMessageLifeTimer = Timer(FLOATING_LIFE_TIME);

public:
    GUIMain();
    GUIMain(Controller *player);


    void addFloatingMessage(Unit *unit, std::string message);
    void addBlushingFloatingMessage(Unit *unit, int value);

    void setMenu(GUIStack *value);
    void setMessage(GUICentralMessage *value);
    void setMiniMap(GUIMiniMap *value);

    // Worker interface
public:
    void tick(Context *context, Event *event);
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUIMAIN_H
