#ifndef GUIMAIN_H
#define GUIMAIN_H

#include "guistack.h"
#include "guicentralmessage.h"
#include "guifloatingmessage.h"
#include "guiblushingfloatingmessage.h"

class GUIMain : public GUIElement {
private:
    static const long FLOATING_LIFE_TIME;

    GUIStack *menu = nullptr;
    GUICentralMessage *centralMessage = nullptr;
    GUIFloatingMessage *floatingMessage = nullptr;
    Timer floatingMessageLifeTimer = Timer(FLOATING_LIFE_TIME);

public:
    GUIMain();
    GUIMain(Controller *player);
    void addFloatingMessage(Unit *unit, std::string message);
    void addBlushingFloatingMessage(Unit *unit, int value);

    // GUIElement interface
public:
    std::string getTitle();
    void update();
    void render(Renderer *renderer, Event *event);

    void setMenu(GUIStack *value);
    void setMessage(GUICentralMessage *value);
};

#endif // GUIMAIN_H
