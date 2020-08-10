#include "player.h"
#include "units/ship.h"
#include "context.h"
#include "objectregistry.h"
#include "capabilities/modules/weapon.h"


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
    { "[", e172::ScancodeKP_LEFTBRACE },
    { "]", e172::ScancodeKP_RIGHTBRACE },
    { "a", e172::ScancodeA },
    { "s", e172::ScancodeS },
    { "d", e172::ScancodeD },
    { "f", e172::ScancodeF },
    { "g", e172::ScancodeG },
    { "h", e172::ScancodeH },
    { "j", e172::ScancodeJ },
    { "k", e172::ScancodeK },
    { "l", e172::ScancodeL },



    { "space", e172::ScancodeSPACE },
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

void Player::tick(Context *context, e172::AbstractEventHandler *eventHandler) {
    EXISTS(parent()) {

    } else {
        std::cout << "ERRROOOORR\n";
    }

    EXISTS(armor) {

    } else {
        std::cout << "ERRROOOORR\n";
    }


    if(getPersonalKey(eventHandler, "left")) {
        parent()->rotateLeft() ;
    } else if(getPersonalKey(eventHandler, "right")) {
        parent()->rotateRight();
    }

    Ship *ship = dynamic_cast<Ship*>(parent());

    ModuleHandler *modules = parent()->getModuleHandler();
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

    this->Controller::tick(context, eventHandler);
}

void Player::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}

void Player::onHit(Context *context, int health) {
    UNUSED(health);
    context->addEvent(parent(), Context::BACKGROUND_FLASHING, 8);
}
