#include "controller.h"
#include "context.h"

const long Controller::ARMOR_RELEASE_DELAY = 1000;
const char *Controller::ARMOR_RELEASE_MESSAGE = "emergency catapult";

void Controller::releaseArmor() {
    if(armor && parent && armor != parent) {
        armorReleaseTimer = new Timer(ARMOR_RELEASE_DELAY);
        armorReleaseTimer->reset();
        armorReleaseMessageTrigger.enable();
    }
}

Controller::Controller() {
}

Controller::Controller(Ship *armor) {
    this->armor = armor;
}

Unit *Controller::getParent() {
    return parent;
}

void Controller::onHit(Context *context, int health) {}

void Controller::loop(Context *context, Event *event) {
    if(armorReleaseMessageTrigger.check()) {
        context->addEvent(parent, Context::EMERGENCY_MESSAGE, const_cast<char*>(ARMOR_RELEASE_MESSAGE));
    }

    if(armorReleaseTimer && armorReleaseTimer->count()) {
        if(armor && parent) {
            context->addEvent(parent, Context::REMOVE_CAPABILITY, this);
            context->addEvent(armor, Context::ADD_CAPABILITY, this);
            context->addEvent(parent, Context::SPAWN_UNIT, armor);
            armorReleaseTimer = nullptr;
        }
    }
}

void Controller::render(Renderer *renderer) {

}
