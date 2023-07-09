#include "guifloatingmessagecontainer.h"

#include "../messagetype.h"
#include "../units/unit.h"
#include "guiblushingfloatingmessage.h"
#include <e172/context.h>

namespace proj172::core {

const unsigned GUIFloatingMessageContainer::FLOATING_LIFE_TIME = 1000;

void GUIFloatingMessageContainer::setMessage(GUICentralMessage *value) {
    m_centralMessage = value;
    addChildElement(value);
}

void GUIFloatingMessageContainer::addFloatingMessage(const e172::ptr<Unit> &unit, std::string message) {
    m_floatingMessage = e172::FactoryMeta::make<GUIFloatingMessage>(unit, message);
    m_floatingMessageLifeTimer.reset();
}

void GUIFloatingMessageContainer::addBlushingFloatingMessage(const e172::ptr<Unit> &unit, int value) {
    m_floatingMessage = e172::FactoryMeta::make<GUIBlushingFloatingMessage>(unit, value);
    m_floatingMessageLifeTimer.reset();
}

void GUIFloatingMessageContainer::addCommonFloatingMessage(e172::Context *context, const e172::Variant &value) {
    const auto list = value.toVector();
    if(list.size() > 1) {
        const auto entity = context->entityById(list[0].toNumber<Entity::Id>());
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

void GUIFloatingMessageContainer::proceed(e172::Context *context, e172::EventHandler *eventHandler)
{
    context->popMessage(~MessageType::FloatingMessage,
                        this,
                        &GUIFloatingMessageContainer::addCommonFloatingMessage);

    if (m_floatingMessageLifeTimer.check()) {
        m_floatingMessage = nullptr;
    }
}

} // namespace proj172::core
