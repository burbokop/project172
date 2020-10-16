#include "controller.h"

#include <src/context.h>
#include <src/units/ship.h>

const long Controller::ARMOR_RELEASE_DELAY = 1000;
const std::string Controller::ARMOR_RELEASE_MESSAGE = "emergency catapult";

e172::ptr<Ship> Controller::armor() const {
    return m_armor;
}

void Controller::setArmor(const e172::ptr<Ship> &armor) {
    m_armor = armor;
}

void Controller::releaseArmor() {
    if(m_armor && parentUnit() && m_armor != parentUnit()) {
        armorReleaseTimer.reset();
        releaseState = true;
        armorReleaseMessageTrigger.enable();
    }
}

Controller::Controller() {
}

Controller::Controller(const e172::ptr<Ship> &armor) {
    m_armor = armor;
}

void Controller::onHit(e172::Context *context, int health) {
    UNUSED(context);
    UNUSED(health);
}

void Controller::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    UNUSED(eventHandler);
    if(armorReleaseMessageTrigger.check()) {
        context->emitMessage(e172::Context::EMERGENCY_MESSAGE, ARMOR_RELEASE_MESSAGE);
    }

    if(releaseState && armorReleaseTimer.check()) {
        if(m_armor && parentUnit()) {
            context->emitMessage(e172::Context::REMOVE_CAPABILITY, e172::VariantVector { parentUnit()->entityId(), entityId() });
            context->emitMessage(e172::Context::ADD_CAPABILITY, e172::VariantVector { m_armor->entityId(), entityId() });
            context->emitMessage(e172::Context::SPAWN_UNIT, e172::VariantVector { parentUnit()->entityId(), m_armor->entityId() });
            releaseState = false;
        }
    }
}

void Controller::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}
