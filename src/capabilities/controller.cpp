#include "controller.h"

#include <engine/context.h>

const long Controller::ARMOR_RELEASE_DELAY = 1000;
const char *Controller::ARMOR_RELEASE_MESSAGE = "emergency catapult";

void Controller::setSelected(Unit *value) {
    selected = value;
}

void Controller::releaseArmor() {
    if(armor && parentUnit() && armor != parentUnit()) {
        armorReleaseTimer = new e172::ElapsedTimer(ARMOR_RELEASE_DELAY);
        armorReleaseTimer->reset();
        armorReleaseMessageTrigger.enable();
    }
}

Controller::Controller() {
}

Controller::Controller(Ship *armor) {
    this->armor = armor;
}

void Controller::onHit(e172::Context *context, int health) {
    UNUSED(context);
    UNUSED(health);
}

void Controller::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    UNUSED(eventHandler);
    if(armorReleaseMessageTrigger.check()) {
        context->addEvent(parentUnit(), e172::Context::EMERGENCY_MESSAGE, const_cast<char*>(ARMOR_RELEASE_MESSAGE));
    }

    if(armorReleaseTimer && armorReleaseTimer->check()) {
        if(armor && parentUnit()) {
            context->addEvent(parentUnit(), e172::Context::REMOVE_CAPABILITY, this);
            context->addEvent(armor, e172::Context::ADD_CAPABILITY, this);
            context->addEvent(parentUnit(), e172::Context::SPAWN_UNIT, armor);
            armorReleaseTimer = nullptr;
        }
    }
}

void Controller::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}
