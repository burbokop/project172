#include "player.h"
#include <src/units/ship.h>
#include <src/engine/objectregistry.h>
#include <src/capabilities/modules/weapon.h>

#include <src/engine/context.h>

const std::map<std::string, e172::Scancode> Player::scancode = {
    { "q", e172::ScancodeQ },
    { "w", e172::ScancodeW },
    { "e", e172::ScancodeE },
    { "r", e172::ScancodeR },
    { "t", e172::ScancodeT },
    { "y", e172::ScancodeY },
    { "u", e172::ScancodeU },
    { "i", e172::ScancodeI },
    { "o", e172::ScancodeO },
    { "p", e172::ScancodeP },
    { "[", e172::ScancodeKpLeftBrace },
    { "]", e172::ScancodeKpRightBrace },
    { "a", e172::ScancodeA },
    { "s", e172::ScancodeS },
    { "d", e172::ScancodeD },
    { "f", e172::ScancodeF },
    { "g", e172::ScancodeG },
    { "h", e172::ScancodeH },
    { "j", e172::ScancodeJ },
    { "k", e172::ScancodeK },
    { "l", e172::ScancodeL },

    { "space", e172::ScancodeSpace },
};



bool Player::getPersonalKey(e172::AbstractEventHandler *eventHandler, std::string id) {
    if(personalScancode.find(id) != personalScancode.end()) {
        return eventHandler->keyHolded(personalScancode[id]);
    }
    return false;
}

Player::Player() : Controller(), Loadable() {
    registerInitFunction([this]() {
        auto keymap = asset<e172::VariantMap>("keymap");
        for(auto it = keymap.begin(); it != keymap.end(); ++it) {
            if(Player::scancode.find(it->second.toString()) != Player::scancode.end()) {
                personalScancode[it->first] = Player::scancode.at(it->second.toString());
            }
        }
    });
}

void Player::setArmor(Ship *armor) {
    this->armor = armor;
}

void Player::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {


    if(getPersonalKey(eventHandler, "left")) {
        parentUnit()->rotateLeft(context);
    } else if(getPersonalKey(eventHandler, "right")) {
        parentUnit()->rotateRight(context);
    }

    Ship *ship = dynamic_cast<Ship*>(parentUnit());

    ModuleHandler *modules = parentUnit()->getModuleHandler();
    if(modules) {
        std::vector<Module*> *weapons = modules->getModulesByClass("Weapon");

        if(weapons) {
            for(Module *module : *weapons) {
                Weapon *weapon = dynamic_cast<Weapon*>(module);
                if(weapon) {
                    weapon->setFiring(getPersonalKey(eventHandler, "action"));
                }
            }
        }

        if(ship && getPersonalKey(eventHandler, "warp")) {
            if(!warpKeyPressed) {
                warpKeyPressed = true;
                if(!ship->warp()) {
                    if(!ship->prepareWarp()) {
                        if(!ship->abortWarp(context)) {
                        }
                    }
                }
            }
        } else {
            warpKeyPressed = false;
        }
    }

    if(ship && getPersonalKey(eventHandler, "forward")) {
        ship->accelerateForward();
    }

    if(getPersonalKey(eventHandler, "armor")) {
        releaseArmor();
    }

    this->Controller::proceed(context, eventHandler);
}

void Player::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}

void Player::onHit(e172::Context *context, int) {
    context->emitMessage(e172::Context::BACKGROUND_FLASHING, 8);
}
