#include "guimain.h"


#include "guiblushingfloatingmessage.h"

#include <src/context.h>
#include <src/units/unit.h>


const unsigned GUIMain::FLOATING_LIFE_TIME = 1000;

void GUIMain::setMessage(GUICentralMessage *value) {
    centralMessage = value;
    addChildElement(value);
}

void GUIMain::addFloatingMessage(const e172::ptr<Unit> &unit, std::string message) {
    floatingMessage = new GUIFloatingMessage(unit, message);
    floatingMessageLifeTimer.reset();
}

void GUIMain::addBlushingFloatingMessage(const e172::ptr<Unit> &unit, int value) {
    floatingMessage = new GUIBlushingFloatingMessage(unit, value);
    floatingMessageLifeTimer.reset();
}

void GUIMain::addBlushingFloatingMessage(e172::Context *context, const e172::Variant &value) {
    const auto list = value.toVector();
    if(list.size() > 1) {
        const auto entity = context->entityById(list[0].toNumber<Entity::id_t>());
        if(auto target = e172::smart_cast<Unit>(entity)) {
            bool ok = false;
            const auto i = list[1].toInt(&ok);
            if(ok) {
                addBlushingFloatingMessage(target, i);
            } else {
                const auto v = list[1].toString();
                addFloatingMessage(target, v);
            }
        }
    }
}

void GUIMain::addStack(GUIStack *value) {
    m_stacks.push_back(value);
    addChildElement(value);
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
    context->popMessage(e172::Context::FLOATING_MESSAGE, this, &GUIMain::addBlushingFloatingMessage);

    if(floatingMessageLifeTimer.check()) {
        floatingMessage = nullptr;
    }

    /*
    for(auto s : m_stacks) {
        s->proceed(context, eventHandler);
    }
    if(centralMessage) centralMessage->proceed(context, eventHandler);
    if(floatingMessage) floatingMessage->proceed(context, eventHandler);
    if(miniMap) miniMap->proceed(context, eventHandler);
    if(debugValueInfo) debugValueInfo->proceed(context, eventHandler);
    */
    for(const auto& c : children()) {
        c->proceed(context, eventHandler);
    }
}

void GUIMain::render(e172::AbstractRenderer *renderer) {
    for(const auto& c : children()) {
        c->render(renderer);
    }
    /*
    for(auto s : m_stacks) {
        s->render(renderer);
    }
    if(centralMessage) centralMessage->render(renderer);
    if(floatingMessage) floatingMessage->render(renderer);
    if(miniMap) miniMap->render(renderer);
    if(debugValueInfo) debugValueInfo->render(renderer);
    */
}
