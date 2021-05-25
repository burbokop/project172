#include "guifloatingmessagecontainer.h"


#include "guiblushingfloatingmessage.h"

#include <src/context.h>
#include <src/units/unit.h>


const unsigned GUIFloatingMessageContainer::FLOATING_LIFE_TIME = 1000;

void GUIFloatingMessageContainer::setMessage(GUICentralMessage *value) {
    centralMessage = value;
    addChildElement(value);
}

void GUIFloatingMessageContainer::addFloatingMessage(const e172::ptr<Unit> &unit, std::string message) {
    floatingMessage = new GUIFloatingMessage(unit, message);
    floatingMessageLifeTimer.reset();
}

void GUIFloatingMessageContainer::addBlushingFloatingMessage(const e172::ptr<Unit> &unit, int value) {
    floatingMessage = new GUIBlushingFloatingMessage(unit, value);
    floatingMessageLifeTimer.reset();
}

void GUIFloatingMessageContainer::addCommonFloatingMessage(e172::Context *context, const e172::Variant &value) {
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

GUIFloatingMessageContainer::GUIFloatingMessageContainer() {}

void GUIFloatingMessageContainer::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    context->popMessage(e172::Context::FLOATING_MESSAGE, this, &GUIFloatingMessageContainer::addCommonFloatingMessage);

    if(floatingMessageLifeTimer.check()) {
        floatingMessage = nullptr;
    }
}
