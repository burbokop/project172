#include "guimain.h"


#include "gui/guiblushingfloatingmessage.h"



const unsigned GUIMain::FLOATING_LIFE_TIME = 1000;

void GUIMain::setMessage(GUICentralMessage *value) {
    centralMessage = value;
    addChildElement(value);
}

void GUIMain::setMenu(GUIStack *value) {
    menu = value;
    addChildElement(value);
}

void GUIMain::addFloatingMessage(Unit *unit, std::string message) {
    floatingMessage = new GUIFloatingMessage(unit, message);
    floatingMessageLifeTimer.reset();
}

void GUIMain::addBlushingFloatingMessage(Unit *unit, int value) {
    floatingMessage = new GUIBlushingFloatingMessage(unit, value);
    floatingMessageLifeTimer.reset();
}

void GUIMain::setMiniMap(GUIMiniMap *value) {
    miniMap = value;
    addChildElement(value);
}

void GUIMain::setDebugValueInfo(GUIDebugValueInfo *value) {
    debugValueInfo = value;
    addChildElement(value);
}

GUIMain::GUIMain() {}

void GUIMain::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if(floatingMessageLifeTimer.check()) {
        floatingMessage = nullptr;
    }

    if(menu) menu->proceed(context, eventHandler);
    if(centralMessage) centralMessage->proceed(context, eventHandler);
    if(floatingMessage) floatingMessage->proceed(context, eventHandler);
    if(miniMap) miniMap->proceed(context, eventHandler);
    if(debugValueInfo) debugValueInfo->proceed(context, eventHandler);
}

void GUIMain::render(e172::AbstractRenderer *renderer) {
    if(menu) menu->render(renderer);
    if(centralMessage) centralMessage->render(renderer);
    if(floatingMessage) floatingMessage->render(renderer);
    if(miniMap) miniMap->render(renderer);
    if(debugValueInfo) debugValueInfo->render(renderer);
}
