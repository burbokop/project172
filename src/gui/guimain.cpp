#include "guimain.h"


#include "gui/guiblushingfloatingmessage.h"



const long GUIMain::FLOATING_LIFE_TIME = 1000;

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

GUIMain::GUIMain() : GUIElement () {
}

GUIMain::GUIMain(Controller *player) : GUIElement (player) {
}

std::string GUIMain::getTitle() {
    return "";
}

void GUIMain::update() {
    if(menu) menu->update();
    if(centralMessage) centralMessage->update();
    if(miniMap) miniMap->update();
}

void GUIMain::render(Renderer *renderer, Event *event) {
    if(menu) menu->render(renderer, event);
    if(centralMessage) centralMessage->render(renderer, event);

    if(floatingMessage) floatingMessage->render(renderer, event);
    if(floatingMessageLifeTimer.count()) {
        floatingMessage = nullptr;
    }
    if(miniMap) miniMap->render(renderer, event);
}
