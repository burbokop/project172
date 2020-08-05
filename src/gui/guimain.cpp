#include "guimain.h"


#include "gui/guiblushingfloatingmessage.h"



const unsigned GUIMain::FLOATING_LIFE_TIME = 1000;

void GUIMain::setMessage(GUICentralMessage *value) {
    centralMessage = value;
}

void GUIMain::setMenu(GUIStack *value) {
    menu = value;
}

void GUIMain::addFloatingMessage(Unit *unit, std::string message) {
    floatingMessage = new GUIFloatingMessage(unit, message);
    floatingMessageLifeTimer.reset();
}

void GUIMain::addBlushingFloatingMessage(Unit *unit, int value) {
    floatingMessage = new GUIBlushingFloatingMessage(unit, value);
    floatingMessageLifeTimer.reset();
}

void GUIMain::setMiniMap(GUIMiniMap *value)
{
    miniMap = value;
}

GUIMain::GUIMain() : GUIElement () {}

GUIMain::GUIMain(Controller *player) : GUIElement (player) {}

void GUIMain::tick(Context *context, Event *event) {
    if(floatingMessageLifeTimer.count()) {
        floatingMessage = nullptr;
    }

    if(menu) menu->tick(context, event);
    if(centralMessage) centralMessage->tick(context, event);
    if(floatingMessage) floatingMessage->tick(context, event);
    if(miniMap) miniMap->tick(context, event);
}

void GUIMain::render(e172::AbstractRenderer *renderer) {
    if(menu) menu->render(renderer);
    if(centralMessage) centralMessage->render(renderer);
    if(floatingMessage) floatingMessage->render(renderer);
    if(miniMap) miniMap->render(renderer);
}
